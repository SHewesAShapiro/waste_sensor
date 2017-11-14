#include <Adafruit_CircuitPlayground.h>

int value;
int escalation;
boolean flaskfull;
float X, Y, Z;
int count;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  escalation = 0;
  flaskfull = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //turn laser on and check light level
  value = CircuitPlayground.lightSensor();
  
  Serial.print("Light Sensor: ");
  Serial.println(value);

  //double check 
  //if the light intensity is below a threshold, the laser has been deflected, then sound the alarm
  if (value < 100) {
    //wait 15 min and test again
    delay(1000); //15 min power saving mode
    
    //turn laser on and check light level
    value = CircuitPlayground.lightSensor();
    
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
                      for (int j=0; j<=5; j++){
                        X = CircuitPlayground.motionX();
                        if (X > 1){
                          count++;
                          }
                        delay(1000);                        
                      }
                      if (count >= 5){
                        escalation = 0;
                        flaskfull = false;
                        //green light
                         for (int x=0; x <= 9; x++) {
                       CircuitPlayground.setPixelColor(x, 0,   255,   0);
                           
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
