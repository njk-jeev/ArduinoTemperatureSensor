#include "SevSeg.h" // Included the library for the 7 segment display
SevSeg sevseg;  // Created an object

const int sensor_pin = A0; // initialized A0 for LM35 sensor
float tempc;  //variable to store temperature in degree Celsius
float sensor_out;  // variable to store the output

unsigned long interval=1000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.

void setup(){
  pinMode(sensor_pin, INPUT);  // Declared the sensor pin as Input
 
  byte numDigits = 3;     // We are showing 3 digits so set it to 3.
  byte digitPins[] = {10, 11, 12,13};  // Arduino Pins where we have connected the ground pins of 7 segment displays
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};  // Arduino pins where we have connected the segment pins of displays

  bool resistorsOnSegments = true;
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE;   // Type of display we are using
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);   // Initialized the display
  sevseg.setBrightness(100);  // Sets the brigtness of the displays. This can be from 0 to 100
}

void loop(){
  sensor_out = analogRead(sensor_pin); // Gets the output from LM35
  tempc = (sensor_out*500)/1023;  // Calculated the temperature in C
  delay_function(); //  function to add 1 second delay
  sevseg.refreshDisplay(); // This function is required to continue displaying
}

void delay_function() {
unsigned long currentMillis = millis(); // grab current time

 // check if "interval" time has passed (1000 milliseconds)
 if ((unsigned long)(currentMillis - previousMillis) >= interval) {
  sevseg.setNumber(tempc, 1);   // Sets temperature on display
  previousMillis = millis();
  }
}
