#include <IRremote.h>
#include <EEPROM.h>
const int RECV_PIN=A0;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define pwm_pin 5 // PWM Pin Out

#define led1 8  // LED1 Pin Out
#define led2 9  // LED2 Pin Out
#define led3 10 // LED3 Pin Out
#define led4 11 // LED4 Pin Out
#define led5 12 // LED5 Pin Out

int duty_cycle;
int mode;

void setup(){
  Serial.begin(9600);

  pinMode(pwm_pin, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);

mode = EEPROM.read(1);
duty_cycle = EEPROM.read(2);
}

void loop() {
  
if(irrecv.decode(&results)){
   Serial.println(results.value,HEX);
  
     if(results.value==0xFFA25D){ mode = mode+1;
if(mode>1){mode=0;}
EEPROM.write(1, mode);     
}
     
else if(results.value==0xFF30CF){ duty_cycle=140;
EEPROM.write(2, duty_cycle); 
}

else if(results.value==0xFF18E7){ duty_cycle=180;
EEPROM.write(2, duty_cycle); 
}

else if(results.value==0xFF7A85){ duty_cycle=220;
EEPROM.write(2, duty_cycle); 
}

else if(results.value==0xFF10EF){ duty_cycle=240;
EEPROM.write(2, duty_cycle); 
}

else if(results.value==0xFF38C7){ duty_cycle=255;
EEPROM.write(2, duty_cycle); 
}
    
 irrecv.resume(); // Receive the next value
 delay(100);
 }

if(mode==1){
  
if(duty_cycle==140){
digitalWrite(led1, HIGH); 
digitalWrite(led2, LOW); 
digitalWrite(led3, LOW); 
digitalWrite(led4, LOW); 
digitalWrite(led5, LOW);   
}

if(duty_cycle==180){
digitalWrite(led1, HIGH); 
digitalWrite(led2, HIGH); 
digitalWrite(led3, LOW); 
digitalWrite(led4, LOW); 
digitalWrite(led5, LOW);   
}

if(duty_cycle==220){
digitalWrite(led1, HIGH); 
digitalWrite(led2, HIGH); 
digitalWrite(led3, HIGH); 
digitalWrite(led4, LOW); 
digitalWrite(led5, LOW);   
}

if(duty_cycle==240){
digitalWrite(led1, HIGH); 
digitalWrite(led2, HIGH); 
digitalWrite(led3, HIGH); 
digitalWrite(led4, HIGH); 
digitalWrite(led5, LOW);   
}

if(duty_cycle==255){
digitalWrite(led1, HIGH); 
digitalWrite(led2, HIGH); 
digitalWrite(led3, HIGH); 
digitalWrite(led4, HIGH); 
digitalWrite(led5, HIGH);   
} 

analogWrite(pwm_pin, duty_cycle);  
}else{
digitalWrite(pwm_pin, LOW);
  
digitalWrite(led1, LOW); 
digitalWrite(led2, LOW); 
digitalWrite(led3, LOW); 
digitalWrite(led4, LOW); 
digitalWrite(led5, LOW); 
}
  
delay(10);  
}
