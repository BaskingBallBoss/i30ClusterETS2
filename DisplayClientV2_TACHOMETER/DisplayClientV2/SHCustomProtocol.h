#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>
#include <Servo.h>

class SHCustomProtocol {
private:

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


/* swapped left 11 witht tract 8 */


Servo tach;
int pos = 0;  

long map3( long x, long in_min, long in_max, long out_min, long out_max )
{
 long out_range;
 long in_range;

 out_range = out_max - out_min;
 if ( out_range > 0 )
   ++out_range;
 else if ( out_range < 0 )
   --out_range;
 else
   return( 0 );

 in_range = in_max - in_min;
 if ( in_range > 0 )
   ++in_range;
 else if ( in_range < 0 )
   --in_range;
 else
   // Is actually infinity but long has no such thing.  The least negative long is another choice.
   return( 0 );

 return (x - in_min) * (out_range) / (in_range) + out_min;
}

  // Called when starting the arduino (setup method in main sketch)
  void setup() {
    tach.attach(9);
  }

  // Called when new data is coming from computer
  void read() {
    int rpm = FlowSerialReadStringUntil('\n').toInt();
 pos = map3(rpm,0,4560,178,0); //I calibrated my servo to the cluster with this
 FlowSerialDebugPrintLn("RPM : " + String(rpm));

 


  

  
  

  


//if(ABS == 0)
// {
// digitalWrite(ABS_LIGHT, LOW);
//} else {
//digitalWrite(ABS_LIGHT, LOW);
//}




  
  

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
    tach.write(pos);
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


