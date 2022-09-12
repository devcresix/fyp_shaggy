# 1 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
# 21 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
const int stepsPerRevolution = 200;

int rpm;
int currentGear;
int mode;

void setup()
{
    pinMode(2, 0x1);
    pinMode(3, 0x1);
    pinMode(4, 0x1);
    pinMode(5, 0x1);
    pinMode(6, 0x0);
    pinMode(7, 0x0);
}

void loop()
{

}

void changeGear(){
    rpm = analogRead(A0);
    rpm = map();
    switch (mode){
        case(1):
            if (rpm>=2000 & rpm<2500){
                gearOne();
            }
            else if(rpm>=2500 & rpm<3000){
                gearTwo();
            }
            else if(rpm>=3500 & rpm<4000){
                gearThree();
            }
            else if(rpm>=4500 & rpm<5000){
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
            digitalWrite(2, 0x1);
            digitalWrite(4, 0x0);
            spin(0, 10);
            spin(1, 10);
            digitalWrite(2, 0x0);
        case(1):
            
# 83 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
           __null
# 83 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
               ;
        case(2):
            digitalWrite(4, 0x0);
            spin(1, 20);
        case(3):
            digitalWrite(2, 0x1);
            digitalWrite(4, 0x0);
            spin(0, 20);
            spin(1, 20);
            digitalWrite(2, 0x0);
        case(4):
            digitalWrite(2, 0x0);
            spin(0, 20);
    }
    currentGear = 1;
}

void gearTwo(){
    switch(currentGear){
        case(0):
            digitalWrite(2, 0x1);
            digitalWrite(4, 0x1);
            spin(0, 10);
            spin(1, 10);
            digitalWrite(2, 0x0);
            digitalWrite(4, 0x0);
        case(1):
            digitalWrite(2, 0x1);
            spin(1, 20);
            digitalWrite(2, 0x0);
        case(2):
            
# 114 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
           __null
# 114 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
               ;
        case(3):
            digitalWrite(4, 0x1);
            spin(0, 20);
            digitalWrite(4, 0x0);
        case(4):
            digitalWrite(2, 0x1);
            digitalWrite(4, 0x1);
            spin(0, 20);
            spin(1, 20);
            digitalWrite(2, 0x0);
            digitalWrite(4, 0x0);
    }
    currentGear = 2;
}

void gearThree(){
    switch(currentGear){
        case(0):
            digitalWrite(2, 0x1);
            digitalWrite(4, 0x0);
            spin(0, 10);
            spin(1, 10);
            digitalWrite(2, 0x0);
        case(1):
            digitalWrite(2, 0x1);
            digitalWrite(4, 0x0);
            spin(0, 20);
            spin(1, 20);
            digitalWrite(2, 0x0);
        case(2):
            digitalWrite(4, 0x0);
            spin(1, 20);
        case(3):
            
# 148 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
           __null
# 148 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
               ;
        case(4):
            digitalWrite(2, 0x1);
            spin(0, 20);
            digitalWrite(2, 0x0);
    }
    currentGear = 3;
}

void gearFour(){
    switch(currentGear){
        case(0):
            digitalWrite(2, 0x0);
            digitalWrite(4, 0x0);
            spin(0, 10);
            spin(1, 10);
        case(1):
            digitalWrite(4, 0x0);
            spin(1, 20);
        case(2):
            digitalWrite(2, 0x0);
            digitalWrite(4, 0x0);
            spin(0, 20);
            spin(1, 20);
        case(3):
            digitalWrite(2, 0x0);
            spin(0, 20);
        case(4):
            
# 176 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
           __null
# 176 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
               ;
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
                digitalWrite(3, 0x1);
                delayMicroseconds(200);
                digitalWrite(3, 0x0);
                delayMicroseconds(200);
            }

        case(1):
            for (int i = 0; i < stepsPerRevolution*steps; i++) {
                // These four lines result in 1 step:
                digitalWrite(5, 0x1);
                delayMicroseconds(200);
                digitalWrite(5, 0x0);
                delayMicroseconds(200);
            }
    }
}
