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
  
  Serial.print("Light Sensor: ");
  Serial.println(value);

  //double check 
  //if the light intensity is below a threshold, the laser has been deflected, then sound the alarm
  if (value < 100) {
    //wait 15 min and test again
    delay(1000); //15 min power saving mode
    
      //turn laser on and check light level
      digitalWrite(9, HIGH);
      value = CircuitPlayground.lightSensor();
      digitalWrite(9,LOW);
    
    if (value < 100) {    
            //beep a lot
            for (int i=0; i <= 5; i++) { //change i to 50 in final
            CircuitPlayground.playTone(500, 100);
            delay(200);
            }
            
            //enter while loop
            flaskfull = true;
            while (flaskfull) {
              //send email according to escalation level

              //increments escalation level
                escalation++;

                //for 24 hours flash constantly and check for accelerometer inversion
                while (escalation > 0) {
                    //turns on red LEDs
                    for (int x=0; x <= 9; x++) {
                       CircuitPlayground.setPixelColor(x, 255,   0,   0);
                    }
                    
                    //listens for accelerometer change
                      X = CircuitPlayground.motionX();
                    //if accelerometer detects inversion, then reset everything
                           Serial.print(X);

                    if (X > 1) {
                      Serial.print("5 second check");
                      count = 0;
                      for (int j=0; j<=10; j++){
                        X = CircuitPlayground.motionX();
                        if (X > 1){
                          count++;
                          CircuitPlayground.setPixelColor(j, 0,   255,   0);
                          }
                        delay(500);                        
                      }
                      if (count >= 10){
                        escalation = 0;
                        flaskfull = false;
                        //blue light
                         for (int x=0; x <= 9; x++) {
                       CircuitPlayground.setPixelColor(x, 0,   0,   255);
                           
                       }     
                       //while x is positive (flask inverted) wait
                       while (X > 1){
                        delay(1000);
                        X = CircuitPlayground.motionX();
                       }
                       //turns off LEDs
                      CircuitPlayground.clearPixels();            
                      }
                    }
                    
                    //if inversion (flask emptying) is not detected after 24 hours, then escalates to the next email level  
                    
                    delay(500); 
                    //turns off LEDs
                    CircuitPlayground.clearPixels();
                    delay(1000); 
                }
            }                   
    }
  }
  delay(1000); //15 min power saving mode
}
