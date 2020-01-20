# ESP32_NTPClock

A simple, no-frills clock that I built around an Adafruit [HUZZAH32 breakout](https://www.adafruit.com/product/4172) and a [7-Segment Display w/ I2C Backpack](https://www.adafruit.com/product/878). 

I'll add more notes later, including a Fritzing thing and maybe a snapshot of my build. For now... the backpack runs from power on GND & 3V pins on the breakout. SCL and SDA come from pins 22 & 23 respectively on the breakout.

For now, we grab the time from the NTP source during setup() and then drop off the network. I expect this will result in clock drift. I'll fix that later with a periodic refresh of some description.

lib includes the Adafruit Arduino libraries needed for the 7-segment display, as captured from GitHub on 2020-01-19. 