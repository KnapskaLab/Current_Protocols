#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
 
TMRpcm tmrpcm;   // create an object for use in this sketch
 
void setup(){
 
  tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc
  pinMode(7, OUTPUT); //shocker
  pinMode(2, OUTPUT); //diode
  pinMode(8, OUTPUT); //TTL sound signal

  Serial.begin(9600);
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  Serial.println("SD fail");
  return;  // don't do anything more if not
  }
  else{
  Serial.println("SD ok"); 
    }
 tmrpcm.volume(1);
}
 
void loop(){ 

digitalWrite(7, HIGH);
if (Serial.available() > 0) { //the simple, contionous tone version
    // get incoming byte:
    char serialIn = Serial.read();
    
    if (serialIn == 'a') {
     digitalWrite(2, HIGH);
     tmrpcm.play("2000.wav");
     delay(19000);
     digitalWrite(7, LOW);
     delay(1000);
     digitalWrite(7, HIGH);
     digitalWrite(2, LOW);
     tmrpcm.disable();
    }

    else if (serialIn == 'b') {
     digitalWrite(2, HIGH);
     digitalWrite(7, LOW);
     delay(1000);
     digitalWrite(7, HIGH);
     digitalWrite(2, LOW);
    }
     
    else if (serialIn == 'c') { //the version with with 5ms pips (for ephys)
     int pips = 0;
     while(pips < 19){ // repeat the brief sound pip 19 times
     digitalWrite(2, HIGH); //shine the diode on continously
     digitalWrite(8, HIGH); //and each time mark it with TTL
     tmrpcm.play("205.wav"); //5-ms long sound, 2kHz
     delay(50);
     digitalWrite(8, LOW); //turn the TTL off together with the sound
     delay(950);
     pips++;
      }
     
     digitalWrite(8, HIGH);
     digitalWrite(7, LOW); //just with the last pip, start also the shock
     tmrpcm.play("205.wav");
     delay(50);
     tmrpcm.disable();
     digitalWrite(8, LOW);
     delay(950);
     digitalWrite(7, HIGH);
     digitalWrite(2, LOW);
      }
}
}
