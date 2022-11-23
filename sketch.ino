#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define dirPinX 5
#define stepPinX 2
#define dirPinY 6
#define stepPinY 3
#define stepPinZ 4
#define dirPinZ 7
#define drivePin 9
#define reversePin 10

#define IDL 750
#define SHIFT 2500
#define MAXIMUM 7000

#define FIRST_LOWER 0
#define SECOND_LOWER 25
#define THIRD_LOWER 40
#define FOURTH_LOWER 60
#define FIFTH_LOWER 75

#define HALF_L 4
#define FULL_L 8

const int stepsPerRevolution = 200;

int rpm;
int speed;
int currentGear=0;
int mode=1;

void setup()
{
    pinMode(dirPinX, OUTPUT);
    pinMode(stepPinX, OUTPUT);
    pinMode(dirPinY, OUTPUT);
    pinMode(stepPinY, OUTPUT);
    pinMode(drivePin, INPUT);
    pinMode(reversePin, INPUT);
    lcd.begin();
    lcd.backlight();
    Serial.begin(9600);
}

void loop()
{
    print();
    gearChange();
    print();
    delay(1);
}

void print(){
    Serial.print(speed);
    Serial.print(" ");
    Serial.print(rpm);
    Serial.print(" ");
    Serial.println(currentGear);
    lcd.setCursor(0,0);
    lcd.print("RPM |SPEED|GEAR");
    lcd.setCursor(0,1);
    lcd.print(rpm);
    lcd.setCursor(6,1);
    lcd.print(speed);
    lcd.setCursor(12,1);
    lcd.print(currentGear);
}


void controlClutch(int dir){
    switch(dir){
        case(0):
            digitalWrite(dirPinZ, HIGH);
            Serial.println("Pressing clutch!");
            for (int i = 0; i < stepsPerRevolution/4; i++) {
                // These four lines result in 1 step:
                digitalWrite(stepPinZ, HIGH);
                delayMicroseconds(200000);
                digitalWrite(stepPinZ, LOW);
                delayMicroseconds(200000);
            }
            break;

        case(1):
            digitalWrite(dirPinZ, LOW);
            Serial.println("Releasing clutch!");
            for (int i = 0; i < stepsPerRevolution/4; i++) {
                // These four lines result in 1 step:
                digitalWrite(stepPinZ, HIGH);
                delayMicroseconds(200000);
                digitalWrite(stepPinZ, LOW);
                delayMicroseconds(200000);
            }
            break;
    }
}

void gearChange(){
    rpm = analogRead(A0);
    rpm = map(rpm,0,1023,0,7000);
    speed = analogRead(A1);
    speed = map(speed,0,1023,0,180);
    print();

    switch (currentGear)
    {
    case (0):
        if (mode == 1)
        { 
            controlClutch(0);
            Serial.print("Gear 01: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            currentGear = 1;
            controlClutch(1);
        }

        break;
    case (1):
        if (rpm > SHIFT & speed > SECOND_LOWER)
        {
            controlClutch(0);
            Serial.println("GEAR 02: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
            currentGear = 2;
            controlClutch(1);
        }

        else if (rpm < IDL)
        {
            controlClutch(0);
        }

        else if (mode == 0)
        {
            controlClutch(0);
            Serial.println("N: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinX, HIGH);
            digitalWrite(dirPinY, LOW);
            spin(1, HALF_L);
            spin(0, HALF_L);
            digitalWrite(dirPinX, HIGH);
            currentGear = 0;
            controlClutch(1);
        }
        break;
    case (2):
        if (rpm > SHIFT & speed > THIRD_LOWER)
        {
            controlClutch(0);
            Serial.println("Gear 03: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, HIGH);
            spin(1, HALF_L);
            digitalWrite(dirPinX, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinY, LOW);
            digitalWrite(dirPinX, LOW);
            currentGear = 3;
            controlClutch(1);
        }
        else if (speed < SECOND_LOWER | rpm < IDL)
        {
            controlClutch(0);
            Serial.println("Gear 01: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, HIGH);
            spin(1, FULL_L);
            currentGear = 1;
            digitalWrite(dirPinY, LOW);
            controlClutch(1);
        }
        break;
    case (3):
        if (rpm > SHIFT & speed > FOURTH_LOWER)
        {
            controlClutch(0);
            Serial.println("Gear 04: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, LOW);
            spin(1, FULL_L);
            currentGear = 4;
            controlClutch(1);
        }
        else if (speed < THIRD_LOWER | rpm < IDL)
        {
            controlClutch(0);
            Serial.println("Gear 02: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, LOW);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
            currentGear = 2;
            controlClutch(1);
        }
        break;
    case (4):
        if (rpm > SHIFT & speed > FIFTH_LOWER)
        {
            controlClutch(0);
            Serial.println("Gear 05: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, HIGH);
            spin(1, HALF_L);
            digitalWrite(dirPinX, HIGH);
            spin(0, HALF_L);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            digitalWrite(dirPinY, LOW);
            currentGear = 5;
            controlClutch(1);
        }
        else if (speed < FOURTH_LOWER | rpm < IDL)
        {
            controlClutch(0);
            Serial.println("Gear 03: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, HIGH);
            spin(1, FULL_L);
            currentGear = 3;
            digitalWrite(dirPinY, LOW);
            controlClutch(1);
        }
        break;
    case (5):
        if (speed < FIFTH_LOWER | rpm < IDL)
        {
            controlClutch(0);
            Serial.println("Gear 04: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(dirPinY, LOW);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            spin(0, HALF_L);
            spin(1, HALF_L);
            currentGear = 4;
            controlClutch(1);
        }
        break;
    default:
        NULL;
        break;
    }
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
            break;
        case(6):
            digitalWrite(dirPinY, HIGH);
            spin(1, HALF_L);
            digitalWrite(dirPinX, LOW);
            spin(0, HALF_L);
            break;
        default:
            NULL;
            break;
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
                delayMicroseconds(2000);
                digitalWrite(stepPinX, LOW);
                delayMicroseconds(2000);
            }
            break;

        case(1):
            for (int i = 0; i < stepsPerRevolution*steps; i++) {
                // These four lines result in 1 step:
                digitalWrite(stepPinY, HIGH);
                delayMicroseconds(2000);
                digitalWrite(stepPinY, LOW);
                delayMicroseconds(2000);
            }
            break;
        
        default:
            NULL;
            break;
    }
}
