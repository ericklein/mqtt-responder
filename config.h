/*
  Project Name:   status light
  Developer:      Eric Klein Jr. (temp2@ericklein.com)
  Description:    Status light triggered by changes on MQTT broker
  
  See readme.md for target information, revision history, feature requests, etc.
*/

// Conditional compile flags
// #define DEBUG	// Output to the serial port
//#define RJ45	// use Ethernet to send data to cloud services
#define WIFI 	// use WiFi to send data to cloud services
#define MQTT 	// always on, used for compatibility with library

// relay featherwing
#define relayTriggerPIN 12

// Sleep time if hardware error occurs in seconds
#define HARDWARE_ERROR_INTERVAL 1

#define CONNECT_ATTEMPT_LIMIT	3 // max connection attempts to internet services
#define CONNECT_ATTEMPT_INTERVAL 10 // seconds between internet service connect attempts

// set client ID; used by mqtt and wifi
#define CLIENT_ID "status-light"

// select time zone, used by NTPClient
// const int timeZone = 0;  	// UTC
//const int timeZone = 1; // Ireland
//const int timeZone = -5;  // USA EST
//const int timeZone = -4;  // USA EDT
//const int timeZone = -7;  // USA PDT
const int timeZone = -8;  // USA PST

 // used in aq_network.cpp
const String weekDays[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

//set MQTT parameters
#ifdef MQTT
	#define MQTT_KEEP_ALIVE 300	// in seconds

	// structure: site/room/device/data	
	#define MQTT_SUB_TOPIC 		"home/demo/rco2/co2"
	#define MQTT_PUB_TOPIC6		"7828/demo/sl/rssi"
#endif