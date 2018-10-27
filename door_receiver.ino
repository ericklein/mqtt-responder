/*
  Project Name:   door receiver
  Developer:      Eric Klein Jr. (temp2@ericklein.com)
  Description:    Reads door open/close state from Adafruit IO (cloud) and displays state as visual output
  
  See README.md for target information, revision history, feature requests, etc.
*/

/************************** Configuration ***********************************/

// setup information for Adafruit IO and physical network device
#include "config.h"

// Pin connections
#define DOOR 13
#define LED_PIN 0

// deep sleep length before checking door state in seconds
#define SLEEP_LENGTH 18e7

// set up the 'digital' feed
AdafruitIO_Feed *door = io.feed("door");

void setup() {

   // set led pin as a digital output
  pinMode(LED_PIN, OUTPUT);
 
  // start the serial connection
  Serial.begin(115200);
 
  // wait for serial monitor to open
  while(! Serial);
 
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
 
  // set up a message handler for the 'door' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
door->onMessage(handleMessage);
 
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {

 // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
 
  Serial.print("received <- ");
 
  if(data->toPinLevel() == HIGH)
   { // door is open
    Serial.println("Door is open");}
    else
    {Serial.println("Door closed");}
  // write the current state to the led
  digitalWrite(LED_PIN, data->toPinLevel());

//  // we are done here. go back to sleep.
//  Serial.println("I'm going into deep sleep mode");
// ESP.deepSleep(SLEEP_LENGTH);
}
