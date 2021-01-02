# Status light

## Purpose 
Status light triggered by changes in MQTT feed

### Contributors

### Software Dependencies not in Arduino Library Manager 

### BOM
- 1x: Adafruit Feather Huzzah 8266 https://www.adafruit.com/product/2471
- 1x: Adafruit Non-Latching Relay Featherwing https://www.adafruit.com/product/2895
- 1x: AC powered (traffic) light

### Pinouts

### Information Sources
- Adafruit Huzzah pinout - https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/pinouts
- Relay setup - http://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/
- ESP8266 Arduino from: https://github.com/esp8266/Arduino
- MQTT
	- https://learn.adafruit.com/adafruit-io/mqtt-api
	- https://learn.adafruit.com/mqtt-adafruit-io-and-you

### Learnings

### Issues
- [P3]101620: MQTT broker log file shows status-light reconnecting although it has a connection, so the broker kills the old session?
- [P2]102420: Move local MQTT server to named entry instead of IP address so DNS can resolve it if entry changes

### Feature Requests
- [P3]100720; MQTT QoS 1
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
	- [FR]100120 [P3]; validate Ethernet code -> code aligned with functioning status_light Ethernet code
	- [FR]111020 [P3]: combine MQTT publish code blocks for AdafruitIO MQTT and generic MQTT -> complete
- 123120
	- [I]102420 [P1]; Need an error indicator for for non-DEBUG, while(1) errors, MQTT connection errors -> while(1) error handling improved and now blinks status light in unique pattern to indicate fatal error