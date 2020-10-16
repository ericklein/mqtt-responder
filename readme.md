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
101220[P1]; light is turning on/off at seemingly random intervals but I'm not sure messages are driving it

### Feature Requests
- 100120[P3]; validate Ethernet code
- 100720[P2]; MQTT QoS 1

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