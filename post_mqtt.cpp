#include "Arduino.h"

// hardware and internet configuration parameters
#include "config.h"
// private credentials for network, MQTT, weather provider
#include "secrets.h"

#include "aq_network.h"
extern AQ_Network aq_network;

// Shared helper function
extern void debugMessage(String messageText);

// Status variables shared across various functions
extern bool internetAvailable;

#ifdef MQTT
  // MQTT setup
  #include <Adafruit_MQTT.h>
  #include <Adafruit_MQTT_Client.h>
  extern Adafruit_MQTT_Client aq_mqtt;
  extern Adafruit_MQTT_Subscribe statusLightSub;


  void mqttConnect()
  // Connects and reconnects to MQTT broker, call as needed to maintain connection
  {
    int8_t mqttErr;
    int8_t tries;
  
    // exit if already connected
    if (aq_mqtt.connected())
    {
      debugMessage(String("Already connected to MQTT broker ") + MQTT_BROKER);
      return;
    }
    for(tries =1; tries <= CONNECT_ATTEMPT_LIMIT; tries++)
    {
      debugMessage(String(MQTT_BROKER) + " connect attempt " + tries + " of " + CONNECT_ATTEMPT_LIMIT + " happens in " + (CONNECT_ATTEMPT_INTERVAL) + " seconds");
      if ((mqttErr = aq_mqtt.connect()) == 0)
      {
        debugMessage(String("Connected to MQTT broker ") + MQTT_BROKER);
        return;
      }
      else
      {
        // generic MQTT error
        debugMessage(aq_mqtt.connectErrorString(mqttErr));
  
        // Adafruit IO connect errors
        // switch (mqttErr)
        // {
        //   case 1: debugMessage("Adafruit MQTT: Wrong protocol"); break;
        //   case 2: debugMessage("Adafruit MQTT: ID rejected"); break;
        //   case 3: debugMessage("Adafruit MQTT: Server unavailable"); break;
        //   case 4: debugMessage("Adafruit MQTT: Incorrect user or password"); break;
        //   case 5: debugMessage("Adafruit MQTT: Not authorized"); break;
        //   case 6: debugMessage("Adafruit MQTT: Failed to subscribe"); break;
        //   default: debugMessage("Adafruit MQTT: GENERIC - Connection failed"); break;
        // }
        aq_mqtt.disconnect();
        delay(CONNECT_ATTEMPT_INTERVAL*1000);
      }
    }
    debugMessage(String("Connection failed to MQTT broker: ") + MQTT_BROKER);
  }

  int mqttDeviceWiFiUpdate(int rssi)
  {
    int result = 0;
    if (internetAvailable)
    {
      // Adafruit_MQTT_Publish rssiLevelPub = Adafruit_MQTT_Publish(&aq_mqtt, MQTT_PUB_TOPIC6, MQTT_QOS_1); // if problematic, remove QOS parameter
      Adafruit_MQTT_Publish rssiLevelPub = Adafruit_MQTT_Publish(&aq_mqtt, MQTT_PUB_TOPIC6);
      mqttConnect();

      if (rssiLevelPub.publish(rssi))
      {
        debugMessage("MQTT publish: WiFi RSSI succeeded");
        result = 1;
      }
      else
      {
        debugMessage("MQTT publish: WiFi RSSI failed");
      }
      aq_mqtt.disconnect();
    }
    return(result);
  }

  void mqttStatusLightCheck()
  {
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = aq_mqtt.readSubscription(5000))) 
    {
      if (subscription == &statusLightSub)
      {
        debugMessage(String("Received: ") + ((char *)statusLightSub.lastread) + " from: " + MQTT_SUB_TOPIC); 
        if (atol((char *)statusLightSub.lastread) > THRESHOLD_VALUE)
        {
          debugMessage("turning light on");
          digitalWrite(relayTriggerPIN, HIGH);
        }
        else
        {
          debugMessage("turning light off");
          digitalWrite(relayTriggerPIN, LOW);
        }
      }
    }
  }
#endif