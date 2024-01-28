/*
  Project Name:   status light
  Developer:      Eric Klein Jr. (temp2@ericklein.com)
  Description:    Status light triggered by changes on MQTT broker
  
  See readme.md for target information, revision history, feature requests, etc.
*/

// hardware and internet configuration parameters
#include "config.h"
// private credentials for network, MQTT
#include "secrets.h"

// Generalized network handling
#include "aq_network.h"
AQ_Network aq_network;

// Gloval variables
unsigned long previousMQTTPingTime = 0;
bool internetAvailable = false;

#ifdef MQTT
  #include <Adafruit_MQTT.h>
  #include <Adafruit_MQTT_Client.h>
  extern Adafruit_MQTT_Client aq_mqtt;
  extern Adafruit_MQTT_Subscribe statusLightSub;
  extern void mqttConnect();
  extern int mqttDeviceWiFiUpdate(int rssi);
  extern void mqttStatusLightCheck();
#endif

void setup() 
{
  #ifdef DEBUG
    Serial.begin(115200);
    while (!Serial) ;
  #endif
  debugMessage("Status Light started");
  debugMessage("Client ID: " + String(CLIENT_ID));

  pinMode(relayTriggerPIN, OUTPUT);

  // Setup network connection specified in config.h
  internetAvailable = aq_network.networkBegin();
  if (!internetAvailable)
  {
    deadBug(1);
  }
  aq_mqtt.subscribe(&statusLightSub);
}

void loop()
{
  mqttConnect();
  mqttStatusLightCheck();
  // Since we are subscribing only, we are required to ping the MQTT broker regularly
  if((millis() - previousMQTTPingTime) > MQTT_KEEP_ALIVE * 1000)
  {
    previousMQTTPingTime = millis();   
    if(!aq_mqtt.ping())
    {
      debugMessage("disconnected from broker because ping says no connection");
      aq_mqtt.disconnect();
    }
    debugMessage("MQTT broker pinged to maintain connection");
  }
}

void debugMessage(String messageText)
// wraps Serial.println as #define conditional
{
#ifdef DEBUG
  Serial.println(messageText);
  Serial.flush();  // Make sure the message gets output (before any sleeping...)
#endif
}

void deadBug(int interval)
// flash the status light endlessly to indicate connectivity has been lost
{
  while (1)
  {
    // endless loop communicating fatal error
    digitalWrite(relayTriggerPIN, HIGH);
    delay(interval * 1000);
    digitalWrite(relayTriggerPIN, LOW);
    delay(interval * 1000);
  }
}