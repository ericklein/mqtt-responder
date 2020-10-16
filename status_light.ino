/*
  Project Name:   status light
  Developer:      Eric Klein Jr. (temp2@ericklein.com)
  Description:    Status light triggered by changes in cloud-based data source
  
  See readme.md for target information, revision history, feature requests, etc.
*/

// Conditional compile flags
#define DEBUG     // Output to the serial port
//#define RJ45    // use Ethernet to send data to cloud services
#define WIFI      // use WiFi to send data to cloud services
//#define ADAFRUITIO

// relay featherwing support
#define relayTriggerPIN 12

// Adafruit IO and network device setup
#include "secrets.h"

#ifdef WIFI
  #if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
    #include <WiFiNINA.h>
  #elif defined(ARDUINO_SAMD_MKR1000)
    #include <WiFi101.h>
  #elif defined(ARDUINO_ESP8266_ESP12)
    #include <ESP8266WiFi.h>
  #endif

  WiFiClient client;

  //use WiFiClientSecure for SSL
  //WiFiClientSecure client;
#endif

#ifdef RJ45
  // Set MAC address. If unknown, be careful for duplicate addresses across projects.
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  #include <SPI.h>
  #include <Ethernet.h>
  //#include <EthernetClient.h>  // Adafruit says required, not so in my experience?
  EthernetClient client;
#endif

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
Adafruit_MQTT_Client mqtt(&client, MQTT_BROKER, MQTT_PORT, MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS);
#ifdef ADAFRUITIO
  Adafruit_MQTT_Subscribe statusLightSub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USER "/feeds/status-light");
#else
  Adafruit_MQTT_Subscribe statusLightSub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_SUB_TOPIC);
#endif

void setup() 
{
  #ifdef DEBUG
    Serial.begin(115200);
    while (!Serial)
    {
      // wait for serial port
    }
    Serial.println("Status Light started");
  #endif

  pinMode(relayTriggerPIN, OUTPUT);

  #ifdef WIFI
    // Connect to WiFi access point.
    #ifdef DEBUG
      Serial.print("connecting to ");
      Serial.println(WIFI_SSID);
    #endif

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) 
    {
      #ifdef DEBUG
        Serial.print(".");
      #endif
      delay(500);
    }

    #ifdef DEBUG
      Serial.println();  // finishes the status dots print
      Serial.print("WiFi connected, IP address: ");
      Serial.println(WiFi.localIP());
    #endif
  #endif

  #ifdef RJ45
    // Configure Ethernet CS pin, not needed if using default D10
    //Ethernet.init(10);  // Most Arduino shields
    //Ethernet.init(5);   // MKR ETH shield
    //Ethernet.init(0);   // Teensy 2.0
    //Ethernet.init(20);  // Teensy++ 2.0
    //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
    //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

    // Initialize Ethernet and UDP
    if (Ethernet.begin(mac) == 0)
    {
      #ifdef DEBUG
        Serial.println("Failed to configure Ethernet using DHCP");
      #endif
      // Check for Ethernet hardware present
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
        #ifdef DEBUG
          Serial.println("Ethernet hardware not found");
        #endif
      } 
      else if (Ethernet.linkStatus() == LinkOFF) 
      {
        #ifdef DEBUG
          Serial.println("Ethernet cable is not connected.");
        #endif
      }
      while (1);
    }
    #ifdef DEBUG
      Serial.print("IP number assigned by DHCP is ");
      Serial.println(Ethernet.localIP());
    #endif
  #endif

  mqtt.subscribe(&statusLightSub);
}

void loop()
{
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) 
  {
    if (subscription == &statusLightSub)
    {
      #ifdef DEBUG
        Serial.print("Received: ");
        Serial.print((char *)statusLightSub.lastread);
        Serial.print(" from: ");
        Serial.println(MQTT_SUB_TOPIC);
      #endif
      if (strcmp((char *)statusLightSub.lastread, "On") == 0)
      {
        #ifdef DEBUG
          Serial.println("turning light on");
        #endif
        digitalWrite(relayTriggerPIN, HIGH);
      }
      if (strcmp((char *)statusLightSub.lastread, "Off") == 0) 
      {
        #ifdef DEBUG
          Serial.println("turning light off");
        #endif
        digitalWrite(relayTriggerPIN, LOW); 
      }
    }
  }
  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) 
  {
    mqtt.disconnect();
  }
}

void MQTT_connect()
// Connects and reconnects to MQTT broker, call from loop() to maintain connection
{
  // Stop if already connected
  if (mqtt.connected()) 
  {
    return;
  }
  #ifdef DEBUG
    Serial.print("connecting to MQTT broker: ");
    Serial.println(MQTT_BROKER);
  #endif

  uint8_t ret;
  uint8_t retries = 3;
  while (mqtt.connect() != 0)
  {
    #ifdef DEBUG
      Serial.println(mqtt.connectErrorString(ret));
      Serial.println("retrying MQTT connection in 3 seconds");
    #endif
    mqtt.disconnect();
    delay(3000);
    retries--;
    if (retries == 0) 
    {
      while (1);
    }
  }
  #ifdef DEBUG
    Serial.println("connected to MQTT broker");
  #endif
}