# i30ClusterETS2
SimHub i30 cluster project
Video of cluster working (more can be found on the channel): https://www.youtube.com/watch?v=-w4zYxY_Mm8&t=65s

This is my i30 Cluster project which has quite a few bits and pieces and requires messing around with 12v power source. MAKE THIS PROJECT AT YOUR OWN RISK!!!! not saying that 12v will blow you up but idk!!

The entire length it took me to make this was a over 5 months as I had a period of just leaving it alone for awhile.
List of components:
- **2009 Hyundai i30 Cluster** NOTE: I think you can use any from the first gen i30 which should be 2007-2011 model years. Some clusters may vary with different regions (some might even have more icons/features on it, mine doesnt even have DTE bruh)
- **Arduino UNO** - I have this one purely to drive the servo motor/tachometer since the original tachometer motor within the cluster is run off CANBUS (if you got enough info you can probably use those CANBUS shields)
- **Arduino MEGA** - This runs the speedometer and ALL the lights 
- **Servo motor** - Tachometer
- **12v power source**
- **Jumper wires/breadboard**
- **8 relay module** - This is for most of the icons/lights on the cluster. Some do not needs this such as ABS, HANDBRAKE, and FOG LIGHTS. The reason I added this was the 12v power source needed to power on the cluster seems to have issues with the Arduino's 5v inputs where some of these icons/lights would remain slightly ON even if its getting a LOW input from the code.

The tachometer code is taken from this guy: https://github.com/Bacon8tor/5inTach
Apparently SimHub used to support servo motors but they removed it for being too noisy or something. I tried to implement this code with SimHub's main code but had compatability issues with the Tone.h library which led me to using a separate arduino. If you're smart enough you can probably make it work and thus remove the extra arduino.

- **NOTE**: The code I post here is quite rather disgusting and very messy but im too lazy to make it beautiful. maybe throw it into chatgpt to make it easier to read for yourself.
