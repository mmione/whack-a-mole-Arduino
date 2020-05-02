#define mole_1 11
#define mole_2 12
#define mole_3 13

#define button_1 8
#define button_2 2
#define button_3 3

#define buzzer 6
#define green_LED 7

#include <PinChangeInterrupt.h>

int buttonPressed = 4;

int pinNum = 0;

int winNumber = 0;
int lives = 4;
 
void setup() {

  randomSeed(analogRead(0));
  
  // put your setup code here, to run once:
  pinMode(mole_1, OUTPUT);
  pinMode(mole_2, OUTPUT);
  pinMode(mole_3, OUTPUT);
  pinMode(green_LED, OUTPUT);
  
  attachPCINT(digitalPinToPCINT(button_1), ISR_1, RISING);  // Uses the imported package--we want 3 interrupts. Without the package we are only able to use 2. 
  attachInterrupt(digitalPinToInterrupt(button_2), ISR_2, RISING);
  attachInterrupt(digitalPinToInterrupt(button_3), ISR_3, RISING);
 
}

void ISR_1(){

//  LED_on(mole_1);
//  LED_off(mole_2);
//  LED_off(mole_3);

  buttonPressed = 1;

  if(buttonPressed == pinNum - 10) {  // Meaning they HIT the mole
    
    LED_off(mole_1);
      
  } 

  
}

void ISR_2(){

//  LED_off(mole_1);
//  LED_on(mole_2);
//  LED_off(mole_3);

  buttonPressed = 2;
  
  if(buttonPressed == pinNum - 10) {  // Meaning they HIT the mole
    
    LED_off(mole_2);
    
    
  } 
}

void ISR_3(){

//  LED_off(mole_1);
//  LED_off(mole_2);
//  LED_on(mole_3);

  buttonPressed = 3;

  if(buttonPressed == pinNum - 10) {  // Meaning they HIT the mole
    
    LED_off(mole_3);
    
  } 

  
}


void loop() {

  if(lives == 0) {

    
    LED_on(mole_1);
    LED_on(mole_2);
    LED_on(mole_3);

    tone(buzzer, 100, 1000/4);
    delay(1300/4);
    tone(buzzer, 800, 1000/4);
    delay(1300/4);
    tone(buzzer, 1500, 1000/4);
    delay(1300/4);
    
    LED_off(mole_1);
    LED_off(mole_2);
    LED_off(mole_3);
    delay(100);
    
  } else if(winNumber == 10){

    LED_on(green_LED);
    LED_on(mole_1);
    LED_on(mole_2);
    LED_on(mole_3);
    
  } else {
  
    
    buttonPressed = 4; 
    
    // choose a number (mole number) and light up that LED...
    LED_off(mole_1);
    LED_off(mole_2);
    LED_off(mole_3);
    
    pinNum = random(11,14); // Random from 11-13. 
  
    LED_on(pinNum);
    delay(2000 - winNumber*190);
    LED_off(pinNum);
    
    if(buttonPressed != pinNum - 10) {  // Meaning they MISSED the mole
  
      lives--;
      
      tone(buzzer, 31, 175); 
      delay(250);
      tone(buzzer, 80, 175); 
  
      
    } else { 
  
      winNumber++;
      
      LED_off(mole_1);
      LED_off(mole_2);
      LED_off(mole_3);
      
      LED_on(green_LED);
      delay(20);
      LED_off(green_LED);
      delay(20);
      LED_on(green_LED);
      delay(20);
      LED_off(green_LED);
      delay(20);
      LED_on(green_LED);
      delay(20);
      LED_off(green_LED);
      delay(50);
    }

  }
}

void LED_on(int pinNum){

  digitalWrite(pinNum, HIGH);
  
}


void LED_off(int pinNum){

  digitalWrite(pinNum, LOW);
  
}
