/*
  Project Name:   door receiver
  Developer:      Eric Klein Jr. (temp2@ericklein.com)
  Description:    Reads door open/close state from Adafruit IO (cloud) and displays state as visual output
  
  See README.md for target information, revision history, feature requests, etc.
*/

// setup information for Adafruit IO and physical network device
#include "config.h"

// Pin connections
#define relay_trigger_PIN 12

// deep sleep length before checking door state in seconds
// #define SLEEP_LENGTH 18e7

// set up the 'digital' feed
AdafruitIO_Feed *door = io.feed(AIO_door_feed);

void setup() {
  pinMode(relay_trigger_PIN, OUTPUT);
  // start the serial connection for debug messages
  Serial.begin(115200);
  // connect to io.adafruit.com
  io.connect();
 
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  // message handler for the 'door' feed ,will be called whenever a message is received from adafruit io
  door->onMessage(handleMessage);
}

void loop() {
 // io.run() keeps the client connected to io.adafruit.com and processes any incoming data
  io.run();
}

// handles Adafruit IO feed message that was instantiated in setup()
void handleMessage(AdafruitIO_Data *data) { 
  if(data->toPinLevel() == HIGH)
   { // door is open
    Serial.println("Door is open");
    digitalWrite(relay_trigger_PIN, LOW);
    }
    else
    {Serial.println("Door is closed");
     digitalWrite(relay_trigger_PIN, HIGH);
    }

//  deep sleep the ESP8266 for specified time frame
//  Serial.println("I'm going into deep sleep mode");
//  ESP.deepSleep(SLEEP_LENGTH);
}
