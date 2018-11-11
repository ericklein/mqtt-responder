# door_receiver

Description: device that tracks door open/close status in Adafruit IO (cloud)

Sources
  - ESP8266 Arduino from: https://github.com/esp8266/Arduino

Target
  - Adafruit Feather Huzzah 8266 https://www.adafruit.com/product/2471
  - Adafruit Non-Latching Relay Featherwing https://www.adafruit.com/product/2895

Revisions
	10/21/18 - First version, branched from Adafruit IO read example
	10/26/18 - opsec issues fixed
	11/11/18
		- 10/21/18 - move IO feed name from code to config.h
		- relay trigger code added
    
Feature Requests
	11/11/18 - Handle error condition where connection to Adafruit IO does not happen
	11/11/18 - Add initial read to door state, it currently waits for a subsequent message

Information Sources
	Adafruit Huzzah pinout - https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/pinouts
	Relay setup - http://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/