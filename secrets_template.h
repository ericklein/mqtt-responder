/*
  Project:		status light 110v
  Description:	private configuration data template that needs to be saved as secrets.h after github cloning the project
*

// Configuration Step 1: Set WiFi credentials
// set the WiFi SSID and password to connect to network (data endpoints)
//#if defined(MQTT) || defined(INFLUX) || defined(HASSIO_MQTT) || defined(DWEET)
// 	#define WIFI_SSID       "key_value"
// 	#define WIFI_PASS       "key_value"
// #endif

// Configuration Step 2: If using MQTT, set MQTT broker login parameters
// #ifdef MQTT
//  #define MQTT BROKER    "mqtt.hostname.local or IP address"
// 	#define MQTT_PORT  		port_number	// use 8883 for SSL
// 	#define MQTT_USER		"key_value"
//  #define MQTT_PASSWORD	"key_value"
// #endif

// Configuration Step 3: Set key device and installation configuration parameters.  These are used
// widely throughout the code to properly identify the device and generate important
// operating elements like MQTT topics, InfluxDB data tags (metadata).  Should be
// customized to match the target installation. Values here are examples.
// #define DEVICE           "key_value"	// e.g. name of device, "realtime_co2"
// #define DEVICE_SITE      "key_value"	// e.g. physical address of the device, "1234 Main Street"
// #define DEVICE_LOCATION  "key_value"	// e.g. general location of device at physical address, "indoor"
// #define DEVICE_ROOM      "key_value"	// e.g. specific location of device within location, "kitchen"
// #define DEVICE_ID        "key_value"	// e.g. unique ID for the device, "007"

// This line is required until a bug fix is completed. Copy values from config step 3.
#define MQTT_SUB_TOPIC    "DEVICE_SITE/DEVICE_LOCATION/DEVICE_ROOM/DEVICE/light"