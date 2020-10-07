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

### Feature Requests
- 111118: [P2]; Handle error condition where connection to Adafruit IO does not happen
- 100120: [P1]; support MQTT brokers
- 100720: [P3]; try and integrate two MQTT code paths?
- 100720: [P2]; implement MQTT QoS and Will

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
	- untested code for MQTT brokers