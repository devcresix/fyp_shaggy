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
    rpm = map(rpm,0,1023,0,5000);
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
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinY, LOW);
        case(2): 
            digitalWrite(dirPinY, HIGH);
            spin(1, FULL_L);
            digitalWrite(dirPinY, LOW);
        default:
            NULL;
    }
    currentGear = 1;
}

void gearTwo(){
    switch(currentGear){
        case(1):
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
        case(3):
            digitalWrite(dirPinY, LOW);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
        default:
            NULL;
    }
    currentGear = 2;
}

void gearThree(){
    switch(currentGear){
        case(2):
            digitalWrite(dirPinY, HIGH);
            spin(1, HALF_L);
            digitalWrite(dirPinX, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
        case(4):
            digitalWrite(dirPinY, HIGH);
            spin(1, FULL_L);
            digitalWrite(dirPinY, LOW);
        default:
            NULL;
    }
    currentGear = 3;
}

void gearFour(){
    switch(currentGear){
        case(3):
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
        case(5):
            digitalWrite(dirPinY, LOW);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
        default:
            NULL;
    }
    currentGear = 4;
}

void gearFive(){
    switch(currentGear){
        case(4):
            digitalWrite(dirPinY, HIGH);
            spin(1, HALF_L);
            digitalWrite(dirPinX, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
        default:
            NULL;
    }
    currentGear = 5;
}

void reverse(){
    digitalWrite(dirPinX, HIGH);
    spin(0, HALF_L);
    digitalWrite(dirPinY, LOW);
    spin(1, HALF_L);
    currentGear = 6;
}

void neutral(){
    switch(currentGear){
        case(1):
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, LOW);
            spin(1, HALF_L);
            spin(0, HALF_L);
            digitalWrite(dirPinX, HIGH);
        case(6):
            digitalWrite(dirPinY, HIGH);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            spin(0, HALF_L);
    }
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