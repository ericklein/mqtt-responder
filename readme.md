# status light 110v

## Purpose 
Monitor MQTT feed and activate status-light when appropriate

### Target Configuration
- See config.h for parameter configuration
- WiFi SSID and password are contained in a `secrets.h` file that is not included in this repo.  Instead you'll find the file `secrets_template.h`, which should be copied to `secrets.h` and then edited to supply the right access credentials and configuration values to match your deployment environment.
- common wire from light to COM on relay
- hot wire from light to NO on relay
- connect both 2 wire JST connectors

### External Software Dependencies
- Adafruit_MQTT

### Bill of Materials (BOM)
- MCU/WiFi
    - Adafruit Feather Huzzah 8266 https://www.adafruit.com/product/2471
- Relay
	- Adafruit Non-Latching Relay Featherwing https://www.adafruit.com/product/2895
- Light
	- 1x: AC powered (traffic) light

### Information Sources
- MQTT services
    - https://hackaday.com/2017/10/31/review-iot-data-logging-services-with-mqtt/
	- https://learn.adafruit.com/adafruit-io/mqtt-api
	- https://learn.adafruit.com/mqtt-adafruit-io-and-you
- Relay setup
	- http://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/

### Status messages
- During initialization, setup()), will:
	- blink on and off 3 times for 2 seconds to indicate a failure to connect to WiFi. The device will then reset and try again.
	- blink on and off 3 times for 1 second to indicate that WiFi connected and the light works as well.

### Issues and Feature Requests
- See GitHub Issues for project

### .plan (big ticket items)
- publish WiFi RSSI