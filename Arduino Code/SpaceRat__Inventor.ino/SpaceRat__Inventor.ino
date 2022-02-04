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
  int hall = A0;
  int rot;
  int rotMap;
  int mpuArray[2];
 
 void setup() {
   
   pinMode(button, INPUT_PULLUP);
   pinMode(hall, INPUT);
   attachInterrupt(4, pressed, RISING);
   Serial.begin(9600);
   //while (!Serial) ;
   Wire.begin();
   byte status = mpu.begin();
   while (status != 0) {
    delay(1000);
    Serial.println("fail");
    status = mpu.begin();
    } 
   delay(1000);
   mpu.calcOffsets(); 
   Mouse.begin();      
   Keyboard.begin(); 
 }

 
 void loop() {
  
  mpu.update();
       
  if ((millis() - timer) > 50) { 

    //Reading the MPU data
    refreshMPU();

    //Reading the Hall sensor data
    rot = analogRead(hall);
    
    //Logic for the Mouse and Keyboard movements
   if (buttonState == 0)  {
        if  (mpuArray[0] != 0 ||mpuArray[1] != 0 ) {  
        Keyboard.press(KEY_LEFT_SHIFT);
        delay(2);
        Mouse.press(MOUSE_MIDDLE);
        Mouse.move(mpuArray[1], mpuArray[0], 0); 
        done=1;
        }

      
      else if ( rot < 500) {  
        rotMap = map(rot, 500, 320, 0, 10 );
        Mouse.move(0, 0,  -rotMap/15); 
        done=1;
      }
      else if ( rot > 600){  
        rotMap = map(rot, 600, 730, 0, 10 );
        Mouse.move(0, 0, rotMap/15); 
        done=1;
      }  
      else  {   
        Keyboard.release(KEY_LEFT_SHIFT);
        Mouse.release(MOUSE_MIDDLE);
        if(done==1){
            Keyboard.write(KEY_ESC);
            done=0;
        }
      }
      
      
      
    }
    else if (buttonState == 1)   {
      if  (mpuArray[0] != 0 ||mpuArray[1] != 0 ) {  
        Mouse.press(MOUSE_MIDDLE);
        Mouse.move(mpuArray[1], mpuArray[0], 0); 
        done=1;
      }

      
      else if ( rot < 500) {  
        rotMap = map(rot, 500, 320, 0, 10 );
        Mouse.move(0, 0,  -rotMap/15); 
        done=1;
      }
      else if ( rot > 600){  
        rotMap = map(rot, 600, 730, 0, 10 );
        Mouse.move(0, 0, rotMap/15); 
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
    void refreshMPU(){
    Xang=mpu.getAngleX();
    Yang=mpu.getAngleY();
    Zang=mpu.getAngleZ();

    if(Xang > 6){
      mpuArray[0] = map(Xang, 6, 10, 1, 10);
    }
    else if(Xang < -6){
      mpuArray[0] = map(Xang, -6, -10, -1, -10);
    }
    else{
      mpuArray[0] = 0;
    }

    if(Yang > 6){
      mpuArray[1] = map(Yang, 6, 10, 1, 10);
    }
    else if(Yang < -6){
      mpuArray[1] = map(Yang, -6, -10, -1, -10);
    }
    else{
      mpuArray[1] = 0;
    }
    
    }
    
    void pressed () {
    buttonState = !buttonState;
    }
 
