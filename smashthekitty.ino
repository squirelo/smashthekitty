#include <Wire.h>
#include <ADXL345.h>


ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int output_pin = 5;
int pin_led = 13;
bool punch = false;

int state = 0;

void setup(){
pinMode(output_pin, OUTPUT);
pinMode(pin_led, OUTPUT);
Serial.begin(9600);
adxl.powerOn();



//set activity/ inactivity thresholds (0-255)
adxl.setActivityThreshold(128); //62.5mg per increment
adxl.setInactivityThreshold(128); //62.5mg per increment
adxl.setTimeInactivity(2); // how many seconds of no activity is inactive?

//look of activity movement on this axes - 1 == on; 0 == off
adxl.setActivityX(1);
adxl.setActivityY(1);
adxl.setActivityZ(1);

//look of inactivity movement on this axes - 1 == on; 0 == off
adxl.setInactivityX(1);
adxl.setInactivityY(1);
adxl.setInactivityZ(1);


//set values for what is considered freefall (0-255)
adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
adxl.setFreeFallDuration(10); //(20 - 70) recommended - 5ms per increment

//setting all interrupts to take place on int pin 1
//I had issues with int pin 2, was unable to reset it
adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT, ADXL345_INT1_PIN );
adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN );
adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN );

//register interrupt actions - 1 == on; 0 == off
adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT, 1);
adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT, 1);
adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);

digitalWrite(pin_led , HIGH);
digitalWrite(output_pin , HIGH);
byte interrupts = adxl.getInterruptSource();
Serial.println("init done");
}

void loop(){
//getInterruptSource clears all triggered actions after returning value
//so do not call again until you need to recheck for triggered actions
byte interrupts = adxl.getInterruptSource();

/*
// freefall
if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
Serial.println("freefall");
//add code here to do when freefall is sensed
}

//inactivity
if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
Serial.println("inactivity");
//add code here to do when inactivity is sensed
}
*/

//activity
if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
Serial.println("activity");
digitalWrite(pin_led , LOW);
digitalWrite(output_pin , LOW);
delay(100);
digitalWrite(pin_led , HIGH);
digitalWrite(output_pin , HIGH);
adxl.getInterruptSource();
delay(3000);
adxl.getInterruptSource();

//add code here to do when activity is sensed
}
}
