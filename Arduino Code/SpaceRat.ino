/* SpaceRat Arduino code by Kiki Hobby Repair - Still under development!!! 
 MPU6050_light library license: MIT
 */

 
 #include <Wire.h>
 #include <MPU6050_light.h>
 #include <Mouse.h>
 #include <Keyboard.h>
        

  MPU6050 mpu(Wire);
  unsigned long timer = 0;
  int Xang, Yang, Zang;
  int done = 0;
  int buttonState = 0;
  int button = 7;
  int hall = 9;
  int rot;
  int rotMap;
 
 void setup() {
   
   pinMode(button, INPUT);
   pinMode(hall, INPUT);
   attachInterrupt(4, pressed, RISING);
   //Serial.begin(9600);
   //while (!Serial) ;
   Wire.begin();
   byte status = mpu.begin();
   while (status != 0) { } 
   delay(1000);
   mpu.calcOffsets(); 
   Mouse.begin();      
   Keyboard.begin(); 
 }


 
 void loop() {
  
  mpu.update();
       
  if ((millis() - timer) > 50) { 

    //Reading the MPU data
    Xang=mpu.getAngleX();
    Yang=mpu.getAngleY();
    Zang=mpu.getAngleZ();

    //Reading the Hall sensor data
    rot = analogRead(hall);
    
    //Logic for the Mouse and Keyboard movements
  if (buttonState == 0)  {
      if  (Yang > 6) {  
        Mouse.press(MOUSE_RIGHT);
        Mouse.move(map(Yang, 6, 10, 1, 10), 0 , 0); 
        done=1;
      }

      else if (Yang < -6) {
        Mouse.press(MOUSE_RIGHT);
        Mouse.move(map(Yang, -10, -6, -10, -1), 0 , 0); 
        done=1;
      }
      
    
      else if  (Xang > 6) {  
        Mouse.press(MOUSE_RIGHT);
        Mouse.move(0, map(Xang, 6, 10, 1, 10) , 0); 
        done=1;
      }

      else if (Xang < -6) {
        Mouse.press(MOUSE_RIGHT);
        Mouse.move(0, map(Xang, -10, -6, -10, -1) , 0); 
        done=1;
      }
      else if ( rot < 500) {  
        rotMap = map(rot, 500, 320, 0, 10 );
        Mouse.move(0, 0,  -rotMap/10); 
        done=1;
      }
      else if ( rot > 600){  
        rotMap = map(rot, 600, 730, 0, 10 );
        Mouse.move(0, 0, rotMap/10); 
        done=1;
      }

      else  {   
          Mouse.release(MOUSE_RIGHT);
          if(done==1){
            Keyboard.write(KEY_ESC);
            done=0;
          }
      }
  
  }

  else if (buttonState == 1)   {
      if  (Yang > 6) {  
        Mouse.press(MOUSE_MIDDLE);
        Mouse.move(map(Yang, 6, 10, 1, 10), 0 , 0); 
        done=1;
      }

      else if (Yang < -6) {
        Mouse.press(MOUSE_MIDDLE);
        Mouse.move(map(Yang, -10, -6, -10, -1), 0 , 0); 
        done=1;
      }
      
    
      else if  (Xang > 6) {  
        Mouse.press(MOUSE_MIDDLE);
        Mouse.move(0, map(Xang, 6, 10, 1, 10) , 0); 
        done=1;
      }

      else if (Xang < -6) {
        Mouse.press(MOUSE_MIDDLE);
        Mouse.move(0, map(Xang, -10, -6, -10, -1) , 0); 
        done=1;
      }
      else if ( rot < 500) {  
        rotMap = map(rot, 500, 320, 0, 10 );
        Mouse.move(0, 0,  -rotMap/10); 
        done=1;
      }
      else if ( rot > 600){  
        rotMap = map(rot, 600, 730, 0, 10 );
        Mouse.move(0, 0, rotMap/10); 
        done=1;
      }
      else  {   
          Mouse.release(MOUSE_MIDDLE);
          Mouse.release(MOUSE_RIGHT);
          if(done==1){
            Keyboard.write(KEY_ESC);
            done=0;
          }
      }
  }
    
    timer = millis();
}
           
   }
   
 
 void pressed () {
    buttonState = !buttonState;
    }
 
