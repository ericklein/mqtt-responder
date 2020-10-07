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

// relay featherwing support
#define relayTriggerPIN 12

// Adafruit IO and network device setup
#include "secrets.h"

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// GENERIC #include <ArduinoMqttClient.h>

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

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, MQTT_PORT, AIO_USERNAME, AIO_KEY);

// GENERIC
// #include <ArduinoMqttClient.h>
// MqttClient mqttClient(client);

// GENERIC MQTT client and topic names
// char statusLightTopic[] = "status-light";

Adafruit_MQTT_Subscribe statusLight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/status-light");

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

  // Connect to WiFi access point.
  #ifdef DEBUG
    Serial.print("Connecting to ");
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
    Serial.println("WiFi connected, IP address: ");
    Serial.println(WiFi.localIP());
  #endif

  // try to connect to the MQTT broker once you're connected to WiFi:
  // while (!connectToBroker())
  // {
  //   Serial.println("attempting to connect to broker");
  //   delay(1000);
  // }
  // Serial.println("connected to broker");

  // set the credentials for the MQTT client:
  // GENERIC mqtt.setId(clientID);
  // GENERIC mqttClient.setUsernamePassword(SECRET_MQTT_USER, SECRET_MQTT_PASS);
  mqtt.subscribe(&statusLight);
}

void loop()
{
  // Keep connection to MQTT broker open
  // GENERIC
  // mqttClient.poll();

  //   if (!mqttClient.connected()) {
  //   Serial.println("reconnecting");
  //   connectToBroker();
  // }

  // // if a message comes in, read it:
  // if (mqttClient.parseMessage() > 0) {
  //   Serial.print("Got a message on topic: ");
  //   Serial.println(mqttClient.messageTopic());
  //   // read the message:
  //   while (mqttClient.available()) {
  //     // convert numeric string to an int:
  //     int message = mqttClient.parseInt();
  //     Serial.println(message);

  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) 
  {
    if (subscription == &statusLight)
    {
      if (strcmp((char *)statusLight.lastread, "On") == 0)
      {
        #ifdef DEBUG
          Serial.println("turning light on");
        #endif
        digitalWrite(relayTriggerPIN, HIGH);
      }
      if (strcmp((char *)statusLight.lastread, "Off") == 0) 
      {
        #ifdef DEBUG
          Serial.println("turning light off");
        #endif
        digitalWrite(relayTriggerPIN, LOW); 
      }
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() 
{
  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }
  #ifdef DEBUGF
    Serial.println("Connecting to MQTT");
  #endif

  uint8_t retries = 3;
  while (mqtt.connect() != 0)
  //while ((ret = mqtt.connect()) != 0)
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) 
    {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

// Generic
// boolean connectToBroker()
// {
//   // if the MQTT client is not connected:
//   if (!mqttClient.connect(broker, port))
//   {
//     // print out the error message:
//     #ifdef DEBUG
//       Serial.print("MOTT connection failed. Error no: ");
//       Serial.println(mqttClient.connectError());
//     #endif
//     // return that you're not connected:
//     return false;
//   }
//   return true;
// }