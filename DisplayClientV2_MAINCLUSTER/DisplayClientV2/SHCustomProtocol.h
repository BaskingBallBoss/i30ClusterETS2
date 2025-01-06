#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>

class SHCustomProtocol {
private:
long oilLightStartTime = 0; // Track when the OIL_LIGHT was turned on
bool oilLightActive = false; // Flag to indicate if the OIL_LIGHT is active
const int OIL_LIGHT_DELAY = 2000; // Delay in milliseconds (5 seconds)
public:

  /*
  CUSTOM PROTOCOL CLASS
  SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

  GENERAL RULES :
    - ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
    - Read data AS FAST AS POSSIBLE in the read function
    - NEVER block the arduino (using delay for instance)
    - Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
    - Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
    - If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
      It is the only interrupt safe place

  COMMON FUNCTIONS :
    - FlowSerialReadStringUntil('\n')
      Read the incoming data up to the end (\n) won't be included
    - FlowSerialReadStringUntil(';')
      Read the incoming data up to the separator (;) separator won't be included
    - FlowSerialDebugPrintLn(string)
      Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)

  */

int left;
int right;
int ABS;
int waterSeparator;
int engineStart;
int HighBeam;
int cruise;
int HandBrake;
int engineIgnition;
int fog;
int Oil;
int Parking;
int brakeValue;
int brakeLight;
/* swapped left 11 witht tract 8 */
int leftPin = 11;
int rightPin = 9;
int ABS_LIGHT = 12;
int FOG_LIGHT = 3;
int ENGINE_IGNITION = 52;
int ENGINE_START = 38;
int HIGH_BEAM = 8;
int cruiseCTRL = 10;
int HAND_BRAKE = 4;
int AUX_LIGHTS = 54;
int WATER_SEPARATOR = 2;
int OIL_LIGHT = 50;
int PARKING = 48;

  // Called when starting the arduino (setup method in main sketch)
  void setup() {
pinMode(leftPin,OUTPUT);
pinMode(rightPin,OUTPUT);
pinMode(ABS_LIGHT, OUTPUT);
pinMode(FOG_LIGHT, OUTPUT);
pinMode(ENGINE_START, OUTPUT);
pinMode(HIGH_BEAM, OUTPUT);
pinMode(cruiseCTRL, OUTPUT);
pinMode(HAND_BRAKE, OUTPUT);
pinMode(ENGINE_IGNITION, OUTPUT);
pinMode(WATER_SEPARATOR, OUTPUT);
pinMode(OIL_LIGHT, OUTPUT);
pinMode(PARKING, OUTPUT);



digitalWrite(leftPin,HIGH);
digitalWrite(rightPin,HIGH);
digitalWrite(ABS_LIGHT, HIGH);
digitalWrite(FOG_LIGHT, HIGH);
digitalWrite(ENGINE_START, HIGH);
digitalWrite(HIGH_BEAM, HIGH);
digitalWrite(cruiseCTRL, HIGH);
digitalWrite(HAND_BRAKE, HIGH);
digitalWrite(ENGINE_IGNITION, HIGH);
digitalWrite(WATER_SEPARATOR, HIGH);
digitalWrite(OIL_LIGHT, HIGH);
digitalWrite(PARKING, HIGH);
  }

  // Called when new data is coming from computer
  void read() {

int left = FlowSerialReadStringUntil(';').toInt();
  int right = FlowSerialReadStringUntil(';').toInt();
  
  int ABS = FlowSerialReadStringUntil(';').toInt();
  int engineStart = FlowSerialReadStringUntil(';').toInt();
  int HighBeam = FlowSerialReadStringUntil(';').toInt();
  int cruise = FlowSerialReadStringUntil(';').toInt();
  int HandBrake = FlowSerialReadStringUntil(';').toInt();
  int engineIgnition = FlowSerialReadStringUntil(';').toInt();
  int Parking = FlowSerialReadStringUntil(';').toInt();
  int brakeValue = FlowSerialReadStringUntil(';').toInt();
  int brakeLight = FlowSerialReadStringUntil(';').toInt();
 
 


  

  if (engineStart == 1) {
    digitalWrite(ENGINE_START, LOW);  // Set pin 2 LOW to activate LED (ground it)
  } else {
    digitalWrite(ENGINE_START, HIGH);  // Set pin 2 HIGH to turn off LED
  }


  if (HighBeam == 1) {
    digitalWrite(HIGH_BEAM, LOW);  // Set pin 2 LOW to activate LED (ground it)
  } else {
    digitalWrite(HIGH_BEAM, HIGH);  // Set pin 2 HIGH to turn off LED
  }

  

  

  if (cruise == 1) {
    digitalWrite(cruiseCTRL, LOW);  // Set pin 2 LOW to activate LED (ground it)
  } else {
    digitalWrite(cruiseCTRL, HIGH);  // Set pin 2 HIGH to turn off LED
  }

  if (HandBrake == 0) {
    digitalWrite(HAND_BRAKE, LOW);  // Set pin 2 LOW to activate LED (ground it)
  } else {
    digitalWrite(HAND_BRAKE, HIGH);  // Set pin 2 HIGH to turn off LED
  }

  if (Parking == 1) {
    digitalWrite(PARKING, LOW);  // Set pin 2 LOW to activate LED (ground it)
  } else {
    digitalWrite(PARKING, HIGH);  // Set pin 2 HIGH to turn off LED
  }

//if(ABS == 0)
// {
// digitalWrite(ABS_LIGHT, LOW);
//} else {
//digitalWrite(ABS_LIGHT, LOW);
//}

if (brakeValue == 1 && brakeLight == 0 && left == 0 && right == 0) //autobrake lights
  {
      digitalWrite(HAND_BRAKE, HIGH);
}
 







  if(left == 1 && right == 0)
  {
   digitalWrite(leftPin,LOW);
   digitalWrite(rightPin,HIGH);
  }

  else if(left == 0 && right == 1)
  {
   digitalWrite(leftPin,HIGH);
   digitalWrite(rightPin,LOW);
  }
  
else if(left == 1&& right == 1)
  {
   digitalWrite(leftPin,LOW);
   digitalWrite(rightPin,LOW);

  }
else

  {
    digitalWrite(leftPin,HIGH);
    digitalWrite(rightPin,HIGH);
  }

  

 // if (engineIgnition == 1 && engineStart == 1) {
 //   digitalWrite(ENGINE_IGNITION, LOW);  // Set pin 2 LOW to activate LED (ground it)
 //   digitalWrite(FOG_LIGHT, HIGH);
 //   digitalWrite(WATER_SEPARATOR, HIGH);
 //   digitalWrite(ABS_LIGHT, HIGH);
    
   
 // } else {
 //   digitalWrite(ENGINE_IGNITION, HIGH);  // Set pin 2 HIGH to turn off LED
 //   digitalWrite(ABS_LIGHT, LOW);
   
 //   digitalWrite(FOG_LIGHT, LOW);
  //  digitalWrite(WATER_SEPARATOR, LOW);   }

if (engineIgnition == 1 && engineStart == 1) {
    // Turn on all lights, including OIL_LIGHT
    digitalWrite(ENGINE_IGNITION, LOW);
    digitalWrite(FOG_LIGHT, HIGH);
    digitalWrite(WATER_SEPARATOR, HIGH);
    digitalWrite(ABS_LIGHT, HIGH);

    if (!oilLightActive) {
        digitalWrite(OIL_LIGHT, LOW);
        oilLightStartTime = millis(); // Record the time when OIL_LIGHT is turned on
        oilLightActive = true;
    }
} else {
    // Turn off other lights immediately
    digitalWrite(ENGINE_IGNITION, HIGH);
    digitalWrite(FOG_LIGHT, LOW);
    digitalWrite(WATER_SEPARATOR, LOW);
    digitalWrite(ABS_LIGHT, LOW);
}

// Handle the OIL_LIGHT separately
if (oilLightActive && (millis() - oilLightStartTime >= OIL_LIGHT_DELAY)) {
    digitalWrite(OIL_LIGHT, HIGH); // Turn off OIL_LIGHT after the delay
    oilLightActive = false;       // Reset the flag
}







  

/*if(lights == 0)
 {
 digitalWrite(lowbeam, LOW);
} else {
digitalWrite(lowbeam, HIGH);
}
*



 




  
    // EXAMPLE 1 - read the whole message and sent it back to simhub as debug message
    // Protocol formula can be set in simhub to anything, it will just echo it
    // -------------------------------------------------------
    String message = FlowSerialReadStringUntil('\n');
    FlowSerialDebugPrintLn("Message received : " + message);

   int rpm = FlowSerialReadStringUntil('\n').toInt();
    FlowSerialDebugPrintLn("RPM : " + String(rpm));
    /*
    // -------------------------------------------------------
    // EXAMPLE 2 - reads speed and gear from the message
    // Protocol formula must be set in simhub to
    // format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
    // -------------------------------------------------------

    int speed = FlowSerialReadStringUntil(';').toInt();
    String gear = FlowSerialReadStringUntil('\n');

    FlowSerialDebugPrintLn("Speed : " + String(speed));
    FlowSerialDebugPrintLn("Gear : " + gear);
    */

    
  }

  // Called once per arduino loop, timing can't be predicted, 
  // but it's called between each command sent to the arduino
  void loop() {
  }

  // Called once between each byte read on arduino,
  // THIS IS A CRITICAL PATH :
  // AVOID ANY TIME CONSUMING ROUTINES !!!
  // PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
  // AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
  void idle() {
  }




 
};

#endif


