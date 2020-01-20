# ESP32_NTPClock

A simple, no-frills clock that I built around an Adafruit [HUZZAH32 breakout](https://www.adafruit.com/product/4172) and a [7-Segment Display w/ I2C Backpack](https://www.adafruit.com/product/878). 

This is an exceedingly simple circuit, only utilizing 2 GPIO pins on the ESP32 breakout for I2C to the display. A Fritzing circuit diagram is included; here's a snapshot of that:

![ESP32_NTPClock](https://i.imgur.com/K8mV0kQ.png "ESP32_NTPClock Fritzing diagram")

The backpack runs from power on the 3V pin on the breakout. SCL and SDA come from pins 22 & 23 respectively on the breakout.

For now, we grab the time from the NTP source during setup() and then drop off the network. I expect this will result in clock drift. I'll fix that later with a periodic refresh of some description.

lib includes the Adafruit Arduino libraries needed for the 7-segment display, as captured from GitHub on 2020-01-19. 

Here's a gratuitous action shot of the current breadboard prototype:

![ESP32_NTPClock](https://i.imgur.com/4gol5dW.jpg "ESP32_NTPClock action shot")

