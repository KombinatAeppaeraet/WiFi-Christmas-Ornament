# WiFi-Christmas-Ornament

## Color changing christmas ornament (via http)

## Hardware
* Wemos D1 mini ESP8266
* WS2812 RGB shield
* Ping pong ball

Connect the RGB shield to the Wemos D1 mini (probably you have to solder connetors first).
Then affix the ping pong ball to the RGB LED. I cut a hole into the ball and snapped it over the LED, which works perfectly for me. The ping pong ball diffuses the light, looking very nice.

## Firmware
The firmware implements a basic http server which checks for the GET parameters *r*, *g* and *b* an sets the RGB colors accordingly.
Add your local WiFi network(s) SSIDs and credentials to the source code. After compile/upload the *Ornament* should join your WiFi network. Find out the IP address either via the serial console or with some WiFi monitor.

## Shell script
Add the IP address to your shell script *christmas.sh* and start the script. The color should change randomly every two seconds.


