/*Sarah Hewes and Alyssa Shapiro
Group 8 - Microcontrollers final project - Waste sensor

This program uses the circuit playgound light sensor to sound an alarm 
when a laser has been deflected by the rising waste level.

used Hello_speaker and Hello_LightSensor example programs*/

#include <Adafruit_CircuitPlayground.h>

int value;

void setup() {
  //initialize the serial output and start up the circuit playground
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {
  //detect the light every 10 seconds
  //if the liquid level has deflected the light, then sound the alarm

  //value is the light intensity detected
  value = CircuitPlayground.lightSensor();

  //serial output
  Serial.print("Light Sensor: ");
  Serial.println(value);

  //if the light intensity detected is less than 500, then the laser has been deflected
  if (value < 500) {
    //sound the alarm
      CircuitPlayground.playTone(500, 100);
  }
  //wait 10 seconds
  delay(10000);
}
