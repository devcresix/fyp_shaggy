#include <Arduino.h>
#line 1 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
#define dirPinX 2
#define stepPinX 3
#define dirPinY 4
#define stepPinY 5
#define drivePin 6
#define reversePin 7


#define FIRST_LOWER 2000
#define FIRST_UPPER 2500
#define SECOND_LOWER 2500
#define SECOND_UPPER 3000
#define THIRD_LOWER 3500
#define THIRD_UPPER 4000
#define FOURTH_LOWER 4500
#define FOURTH_UPPER 5000

#define HALF_L 10
#define FULL_L 20

const int stepsPerRevolution = 200;

int rpm;
int currentGear;
int mode;

#line 27 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void setup();
#line 37 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void loop();
#line 42 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void changeGear();
#line 70 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void controlClutch();
#line 74 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void gearOne();
#line 100 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void gearTwo();
#line 130 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void gearThree();
#line 157 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void gearFour();
#line 181 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void reverse();
#line 185 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void neutral();
#line 189 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
int changeMode(int md);
#line 193 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void spin(int motor,int steps);
#line 27 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
void setup()
{
    pinMode(dirPinX, OUTPUT);
    pinMode(stepPinX, OUTPUT);
    pinMode(dirPinY, OUTPUT);
    pinMode(stepPinY, OUTPUT);
    pinMode(drivePin, INPUT);
    pinMode(reversePin, INPUT);
}

void loop()
{
	
}

void changeGear(){
    rpm = analogRead(A0);
    rpm = map();
    switch (mode){
        case(1):
            if (rpm>=FIRST_LOWER & rpm<FIRST_UPPER){
                gearOne();
            }
            else if(rpm>=SECOND_LOWER & rpm<SECOND_UPPER){
                gearTwo();
            }
            else if(rpm>=THIRD_LOWER & rpm<THIRD_UPPER){
                gearThree();
            }
            else if(rpm>=FOURTH_LOWER & rpm<FOURTH_UPPER){
                gearFour();
            }
        case(2):
            neutral();
            reverse();
        default:
            neutral();
    }



}

void controlClutch(){

}

void gearOne(){
    switch(currentGear){
        case(0):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
        case(1):
            NULL;
        case(2): 
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
        case(3):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, LOW);
            spin(0, FULL_L);
            spin(1, FULL_L);
            digitalWrite(dirPinX, LOW);
        case(4):
            digitalWrite(dirPinX, LOW);
            spin(0, FULL_L);
    }
    currentGear = 1;
}

void gearTwo(){
    switch(currentGear){
        case(0):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
        case(1):
            digitalWrite(dirPinX, HIGH);
            spin(1, FULL_L);
            digitalWrite(dirPinX, LOW);
        case(2):
            NULL;
        case(3):
            digitalWrite(dirPinY, HIGH);
            spin(0, FULL_L);
            digitalWrite(dirPinY, LOW);
        case(4):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, HIGH);
            spin(0, FULL_L);
            spin(1, FULL_L);
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
    }
    currentGear = 2;
}

void gearThree(){
    switch(currentGear){
        case(0):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
        case(1):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, LOW);
            spin(0, FULL_L);
            spin(1, FULL_L);
            digitalWrite(dirPinX, LOW);
        case(2):
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
        case(3):
            NULL;
        case(4):
            digitalWrite(dirPinX, HIGH);
            spin(0, FULL_L);
            digitalWrite(dirPinX, LOW);
    }
    currentGear = 3;
}

void gearFour(){
    switch(currentGear){
        case(0):
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
        case(1):
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
        case(2):
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
            spin(0, FULL_L);
            spin(1, FULL_L);
        case(3):
            digitalWrite(dirPinX, LOW);
            spin(0, FULL_L);
        case(4):
            NULL;
    }
    currentGear = 4;
}

void reverse(){
    currentGear = 5;
}

void neutral(){
    currentGear = 0;
}

int changeMode(int md){
    mode = md;
}

void spin(int motor,int steps){
    switch(motor){
        case(0):
            for (int i = 0; i < stepsPerRevolution*steps; i++) {
                // These four lines result in 1 step:
                digitalWrite(stepPinX, HIGH);
                delayMicroseconds(200);
                digitalWrite(stepPinX, LOW);
                delayMicroseconds(200);
            }
        
        case(1):
            for (int i = 0; i < stepsPerRevolution*steps; i++) {
                // These four lines result in 1 step:
                digitalWrite(stepPinY, HIGH);
                delayMicroseconds(200);
                digitalWrite(stepPinY, LOW);
                delayMicroseconds(200);
            }
    }
}
