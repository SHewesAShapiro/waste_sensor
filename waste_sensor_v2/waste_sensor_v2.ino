#include <Adafruit_CircuitPlayground.h>

int value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() { 
  // put your main code here, to run repeatedly:
  value = CircuitPlayground.lightSensor();
  
  Serial.print("Light Sensor: ");
  Serial.println(value);

  //if the light intensity is below a threshold, the laser has been deflected
  //sound the alarm
  if (value < 100) {
    //beep
      CircuitPlayground.playTone(500, 100);
  }
  delay(1000);
}
