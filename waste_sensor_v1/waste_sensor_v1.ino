/* Waste sensor
 *  Monitors the liquid level in a tissue culture waste flask and responds
 *  to the flask being filled past a threshold and emptied. 
 *  
 *  Laser attaches to GND (black) and pin #9 (red)
 *  
 *  by Alyssa Shapiro and Sarah Hewes
 */
 
#include <Adafruit_CircuitPlayground.h>

// initialize values
int value;
int escalation = 0;
boolean flaskfull = false;
float X;
int count;
int timecount;

void setup() {
  //start the serial output
  Serial.begin(9600);
  //start the circuit plaground
  CircuitPlayground.begin();
  //change the mode of pin #9 to output
  pinMode(9, OUTPUT);
}

void loop() {
  
  //turn laser on and check light level
  digitalWrite(9, HIGH);
  value = CircuitPlayground.lightSensor();
  digitalWrite(9,LOW);

  //print out value for debugging
  Serial.print("Light Sensor: ");
  Serial.println(value);

  //double check 
  //if the light intensity is below a threshold, the laser has been deflected, then sound the alarm
  if (value < 400) {
    //wait 15 min and test again00
    delay(90000); //15 min power saving mode
    
      //turn laser on and check light level
      digitalWrite(9, HIGH);
      value = CircuitPlayground.lightSensor();
      delay(500);
      digitalWrite(9,LOW);
    
    if (value < 400) {    
            //beep an alert for one minute
            for (int i=0; i <= 60; i++) {
            CircuitPlayground.playTone(500, 100);            
            delay(50);
            }
            
            //enter while loop
            flaskfull = true;
            while (flaskfull) {
              //turn off laser
                digitalWrite(9,HIGH);
                      
              //increments escalation level
                escalation++;

                //for 24 hours flash constantly and check for accelerometer inversion
                while (escalation > 0) {

                    //once time has passed increment the escalation level at 24 and 48 hours
                    if (timecount == 86400) {
                      escalation++;
                    }
                    if (timecount == 172800) {
                      escalation++;
                    }

                    //turns on red LEDs
                    for (int x=0; x <= 9; x++) {
                       CircuitPlayground.setPixelColor(x, 255,   0,   0);
                    }
                    
                    //print escalation level to serial
                    if (escalation == 1) {
                      //emails you nicely
                      Serial.println("kitten");
                    }
                    else if (escalation == 2) {
                      //emails you grumpily
                      Serial.println("cat");
                    }
                    else if (escalation >=3) {
                      //emails your PI
                      Serial.println("tiger");
                    }
                   
                    //listens for accelerometer change
                      X = CircuitPlayground.motionX();
                    //if accelerometer detects inversion, then reset everything
                           Serial.println(X);
                    //if the flask has been inverted
                    if (X > 1) {
                      Serial.println("5 second check");
                      count = 0;
                      for (int j=0; j<=10; j++){
                        X = CircuitPlayground.motionX();
                        if (X > 1){
                          count++;
                          CircuitPlayground.setPixelColor(j, 0,   255,   0);
                          }
                        delay(500);                        
                      }
                     //if the flask has been inverted for 5 seconds then the flask has been emptied
                      if (count >= 10){
                        escalation = 0;
                        flaskfull = false;
                        timecount = 0;
                        //blue light
                         for (int x=0; x <= 9; x++) {
                       CircuitPlayground.setPixelColor(x, 0,   0,   255);
                        }     
                       //while x is positive (flask not inverted) keep listening
                       while (X > 1){
                        delay(1000);
                        X = CircuitPlayground.motionX();
                       }
                       //turns off LEDs as the sensor is reset
                      CircuitPlayground.clearPixels();            
                      }
                    }
                                        
                    delay(500); 
                    //turns off LEDs (for flashing)
                    CircuitPlayground.clearPixels();
                    delay(1000); 
                    //keeps track of the amount of time the device has been in an alarm state
                    timecount++;
                }
            }                   
    }
  }
  delay(90000); //15 min pause
}
