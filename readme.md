# Status light

## Purpose 
Traffic light triggered by changes in cloud-based data source

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

### Learnings

### Issues

### Feature Requests
- 111118: Handle error condition where connection to Adafruit IO does not happen
- 111118: Add initial read to door state, it currently waits for a subsequent message
- 120219: Fritzing diagram

### Revisions
- 102118: First version, branched from Adafruit IO read example
- 102618: opsec issues fixed
- 111118
	- [fr]10/21/18: move IO feed name from code to config.h
	- relay trigger code added
- 092920
	- updated to secrets.h for credential data only
	- conditional compile for networks, debug, and sleep
	- added Ethernet support (not tested though ported from working code)
