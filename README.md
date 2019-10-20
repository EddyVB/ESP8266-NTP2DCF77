# NTP2DCF77 using ESP8266
DCF77 is a German transmitter broadcasting on 77.5KHz. This signal can be received in most of Europe. It sends date and time info generated from an atomic clock. ‘DCF’ compatible Clocks are sold in Europe, digital and analog ones. They have a 77.5KHz receiver and decoder build in to set their time automatically. 
See https://en.wikipedia.org/wiki/DCF77
This program is useful when you want to use a DCF clock outside the transmitter range, or in places with poor reception. Other time zones can be set in the settings.h file, so no restriction to the CET.

The ESP8266 connects to your wifi and receives the time from a Network Time Server. A 77.5KHz signal is generated, and also a modulation signal according to the DCF77 standard. These 2 signals (gpio pins) must be connected with 2 resistors to create a 77.5KHz modulated signal.

## Getting Started
The files NTP2DCF77.ino and settings.h + libraries are needed to compile this program. Links to libraries are commented in source code.
Also 2 resistors and an antenna is needed. A ferrite antenna, or even a simple open wire can be sufficient.

### Prerequisites
  WARNING: Check if it is allowed in your country to generate this (very low level) RF signal. Keep this signal as low as possible, in the cm range from your clock.

### Installing
- Get the required libraries, if not already on your system. 
- Timezone and WT/ST config can be changed in settings.h (Most clocks are needing a reset when already sync'ed to another time)
- Compile and upload code with the Arduino GUI to a ESP8266.
- Tested on a Wemos (Lolin) D1 mini
- Add the 'hardware'
  D8 (GPIO15) and D2 (GPIO4) must be connected together with 2 resistors to get a 85% modulation. I use these values (maybe you have to change values when connecting a ferrite antenna, or add a transistor):
```
  D8 ---- 620 ohm -----+----- 68 ohm ---- D2
                       |--------------------------------- Antenna (or open wire)
```
  See Andreas YT-channel for experimenting with antenna's on a RP https://www.youtube.com/watch?v=6SHGAEhnsYk, but a single turn of wire around/close to the receiving antenna can be sufficient.

- From https://github.com/tzapu/WiFiManager:
  When your ESP starts up, it sets it up in Station mode and tries to connect to a previously saved Access Point
  If this is unsuccessful (or no previous network saved) it moves the ESP into Access Point mode and spins up a DNS and WebServer (default ip 192.168.4.1)
  Using any wifi enabled device with a browser (computer, phone, tablet) connect to the newly created Access Point
  Because of the Captive Portal and the DNS server you will either get a 'Join to network' type of popup or get any domain you try to access redirected to the configuration portal
  Choose one of the access points scanned, enter password, click save
  ESP will try to connect. If successful, it relinquishes control back to your app. If not, reconnect to AP and reconfigure.
  
- D8 (GPIO15): I2S Clock is 'misused' as a stable 77.5KHz carrier (fixed pin) Max 12mA drive
  D2 (GPIO04): Is used as modulation pin Max 20mA sink
  D4: I2S uses this pin for the WS signal, not used here, but on the Wemos it is connected to the led, so it will glow. Did not test if writing to this ledport kills the I2S clk function.

 ### Improvements
  It would be nice to have a PDM 77,5KHz, 100% and 15%) signal out of I2S data port. Sinus is better than square wave, and no need for the modulation port. Only a low pass filter. 
 
## Acknowledgements
Thanks to:
- NTP time with > 100ms precision, thanks ddrown https://github.com/ddrown/Arduino_NTPClient
- OverTheAir programming (optional)
- WifiManager, thanks to tzapu https://github.com/tzapu/WiFiManager
- DCF77 pulse generation inspired by Raspberry Pi version from hzeller https://github.com/hzeller/txtempus
- Excellent info on how to add an antenna to the raspberry,can be used for the ESP8266 https://www.youtube.com/watch?v=6SHGAEhnsYk
- And many more ….
