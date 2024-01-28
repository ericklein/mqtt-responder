# MQTT Responder

## Purpose 
Monitor MQTT feed(s) and respond to changes in the feed(s)

### Configuring targets
- Set parameters in secrets.h (see config.h for list of required parameters)
- Set parameters in config.h
- common wire from light to COM on relay
- hot wire from light to NO on relay

### External Software Dependencies
- ESP8266WiFi, WiFiUDP, ESP8266HTTPClient
- Adafruit_MQTT
- NTPClient
- aq_network

### known, working BOM
- MCU
    - Adafruit Feather Huzzah 8266 https://www.adafruit.com/product/2471
- Ethernet
    - Particle Ethernet Featherwing: https://www.adafruit.com/product/4003
    - Silicognition PoE Featherwing: https://www.crowdsupply.com/silicognition/poe-featherwing
- WiFi
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

### Issues
- See GitHub Issues for project

### Feature Requests
- See GitHub Issues for project

### Issues
- [P3]101620: MQTT broker log file shows status-light reconnecting although it has a connection, so the broker kills the old session?

### Feature Requests
- [P2]112920: audio alert

### Revisions
- 102118: First version, branched from Adafruit IO read example
- 102618: infosec issue fixed
- 111118
	- [FR]102118: move IO feed name from code to config.h
	- relay trigger code added
- 092920
	- updated to secrets.h for credential data only
	- conditional compile for networks, debug, and sleep
	- added Ethernet support (not tested though ported from working code)
	- [FR]111118, Add initial read to door state, it currently waits for a subsequent message -> added get() in setup() to fix this
- 100720
	- removed SLEEP support
	- removed Adafruit IO API support
	- [FR]100120: [P1]; Support Adafruit IO MQTT
	- [FR]111118: [P2]; Handle error condition where connection to Adafruit IO does not happen
	- untested code for MQTT brokers
	- untested Ethernet code
- 101220
	- [FR]100120[P1]; support MQTT brokers -> implemented
	- [FR]100720[P3]; try to integrate two MQTT code paths? -> completed using Adafruit MQTT library for Adafruit IO and MQTT brokers
- 101520
	- MQTT code improvements
- 101620
	- [P1]101620: Example ping code fires every loop() but docs say to ping infrequently within the keepalive window to avoid packet collision -> add timer loop to ping at MQTT_KEEP_ALIVE
	- [P1]101220: light is turning on at seemingly random intervals. The new session is either publishing a new value or reading an older value at connection? -> think is was a retained value on the broker side causing the random activation event.
- 122120
	- [FR]111020 [P3]: combine MQTT publish code blocks for AdafruitIO MQTT and generic MQTT -> complete
- 123120
	- [I]102420 [P1]; Need an error indicator for for non-DEBUG, while(1) errors, MQTT connection errors -> while(1) error handling improved and now blinks status light in unique pattern to indicate fatal error