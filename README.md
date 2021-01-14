# ArduinoTurnTable
Platform.io version of https://docs.platformio.org/page/projectconf.html

**This is not my work, I am only porting the code to VScode with PlatformIo.**


## Notes on the LiquidCrystal library
The version is using the LiquidCrystal library from
[Drone Mesh - DIY Wireless Youtube Subscriber Counter 2018 // ESP8266 Subscriber Counter](https://www.youtube.com/watch?v=yfDWCga7iP4).
This lib is included in the `lib/` folder and I had to fix the path in the `I2CIO.cpp` file to the used `Wire` lib. This lib was added directly to the project, since it was difficult to find the correct one, working with the Display which has the I2C attached to it.
