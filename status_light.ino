/*
  Project Name:   status light
  Developer:      Eric Klein Jr. (temp2@ericklein.com)
  Description:    Traffic light triggered by changes in cloud-based data source
  
  See readme.md for target information, revision history, feature requests, etc.
*/

// Conditional compile flags
#define DEBUG     // Output to the serial port
//#define RJ45    // use Ethernet to send data to cloud services
#define WIFI      // use WiFi to send data to cloud services
//#define SLEEP   // sleeps ESP8266 for extended periods between cloud service updates

// Adafruit IO and network device setup
#include "secrets.h"

#ifdef WIFI
  #include "AdafruitIO_WiFi.h"

  #if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
    // Configure the pins used for the ESP32 connection
    #if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
    // Don't change the names of these #define's! they match the variant ones
      #define SPIWIFI SPI
      #define SPIWIFI_SS 10 // Chip select pin
      #define NINA_ACK 9    // a.k.a BUSY or READY pin
      #define NINA_RESETN 6 // Reset pin
      #define NINA_GPIO0 -1 // Not connected
    #endif
    AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
  #else
    AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, WIFI_SSID, WIFI_PASS);  // defined in secrets.h
  #endif
#endif

#ifdef RJ45
  #include "AdafruitIO_Ethernet.h"
  AdafruitIO_Ethernet io(AIO_USERNAME, AIO_KEY); // defined in secrets.h
#endif

// Adafruit IO feeds
AdafruitIO_Feed *statusLight = io.feed("status-light");

// relay featherwing support
#define relayTriggerPIN 12

#ifdef SLEEP
  // deep sleep length before checking door state in seconds
  #define SLEEP_LENGTH 18e7
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

  // message handler for the status-light feed ,called whenever a message is received from adafruit io
  statusLight->onMessage(handleMessage);

  io.connect();
  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    #ifdef DEBUG
      Serial.println(io.statusText());
      Serial.print(".");
    #endif
    delay(500);
  }
  // we are connected
  #ifdef DEBUG
    Serial.println();
    Serial.println(io.statusText());
  #endif

  statusLight->get();
}

void loop()
{
  // Keep connection to Adafruit IO open
  io.run();
}

// handles Adafruit IO feed message instantiated in setup()
void handleMessage(AdafruitIO_Data *data) 
{ 
  if(data->toPinLevel() == LOW)
  { 
    #ifdef DEBUG
      Serial.println("turning light off");
    #endif
    digitalWrite(relayTriggerPIN, LOW);
  }
  else
  {
    #ifdef DEBUG
      Serial.println("turning light on");
    #endif
    digitalWrite(relayTriggerPIN, HIGH);
  }

  #ifdef SLEEP
    //  deep sleep the ESP8266 for specified time frame
    #ifdef DEBUG
      Serial.println("Going into deep sleep mode");
    #endif
    ESP.deepSleep(SLEEP_LENGTH);
  #endif
}