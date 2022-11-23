# 1 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
# 2 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 2
# 3 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
# 28 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
const int stepsPerRevolution = 200;

int rpm;
int speed;
int currentGear=0;
int mode=1;

void setup()
{
    pinMode(5, 0x1);
    pinMode(2, 0x1);
    pinMode(6, 0x1);
    pinMode(3, 0x1);
    pinMode(9, 0x0);
    pinMode(10, 0x0);
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
            digitalWrite(7, 0x1);
            Serial.println("Pressing clutch!");
            for (int i = 0; i < stepsPerRevolution/4; i++) {
                // These four lines result in 1 step:
                digitalWrite(4, 0x1);
                delayMicroseconds(200000);
                digitalWrite(4, 0x0);
                delayMicroseconds(200000);
            }
            break;

        case(1):
            digitalWrite(7, 0x0);
            Serial.println("Releasing clutch!");
            for (int i = 0; i < stepsPerRevolution/4; i++) {
                // These four lines result in 1 step:
                digitalWrite(4, 0x1);
                delayMicroseconds(200000);
                digitalWrite(4, 0x0);
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
            digitalWrite(5, 0x0);
            digitalWrite(6, 0x1);
            spin(0, 4);
            spin(1, 4);
            currentGear = 1;
            controlClutch(1);
        }

        break;
    case (1):
        if (rpm > 2500 & speed > 25)
        {
            controlClutch(0);
            Serial.println("GEAR 02: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x0);
            spin(1, 8);
            currentGear = 2;
            controlClutch(1);
        }

        else if (rpm < 750)
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
            digitalWrite(5, 0x1);
            digitalWrite(6, 0x0);
            spin(1, 4);
            spin(0, 4);
            digitalWrite(5, 0x1);
            currentGear = 0;
            controlClutch(1);
        }
        break;
    case (2):
        if (rpm > 2500 & speed > 40)
        {
            controlClutch(0);
            Serial.println("Gear 03: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x1);
            spin(1, 4);
            digitalWrite(5, 0x1);
            spin(0, 4);
            spin(1, 4);
            digitalWrite(6, 0x0);
            digitalWrite(5, 0x0);
            currentGear = 3;
            controlClutch(1);
        }
        else if (speed < 25 | rpm < 750)
        {
            controlClutch(0);
            Serial.println("Gear 01: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x1);
            spin(1, 8);
            currentGear = 1;
            digitalWrite(6, 0x0);
            controlClutch(1);
        }
        break;
    case (3):
        if (rpm > 2500 & speed > 60)
        {
            controlClutch(0);
            Serial.println("Gear 04: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x0);
            spin(1, 8);
            currentGear = 4;
            controlClutch(1);
        }
        else if (speed < 40 | rpm < 750)
        {
            controlClutch(0);
            Serial.println("Gear 02: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x0);
            spin(1, 4);
            digitalWrite(5, 0x0);
            spin(0, 4);
            spin(1, 4);
            currentGear = 2;
            controlClutch(1);
        }
        break;
    case (4):
        if (rpm > 2500 & speed > 75)
        {
            controlClutch(0);
            Serial.println("Gear 05: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x1);
            spin(1, 4);
            digitalWrite(5, 0x1);
            spin(0, 4);
            spin(1, 4);
            digitalWrite(5, 0x0);
            digitalWrite(6, 0x0);
            currentGear = 5;
            controlClutch(1);
        }
        else if (speed < 60 | rpm < 750)
        {
            controlClutch(0);
            Serial.println("Gear 03: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x1);
            spin(1, 8);
            currentGear = 3;
            digitalWrite(6, 0x0);
            controlClutch(1);
        }
        break;
    case (5):
        if (speed < 75 | rpm < 750)
        {
            controlClutch(0);
            Serial.println("Gear 04: ");
            Serial.print("Speed->");
            Serial.print(speed);
            Serial.print(" RPM->");
            Serial.println(rpm);
            digitalWrite(6, 0x0);
            spin(1, 4);
            digitalWrite(5, 0x0);
            spin(0, 4);
            spin(1, 4);
            currentGear = 4;
            controlClutch(1);
        }
        break;
    default:
        
# 283 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
       __null
# 283 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
           ;
        break;
    }
}

void reverse(){
    digitalWrite(5, 0x1);
    spin(0, 4);
    digitalWrite(6, 0x0);
    spin(1, 4);
    currentGear = 6;
}

void neutral(){
    switch(currentGear){
        case(1):
            digitalWrite(5, 0x1);
            digitalWrite(6, 0x0);
            spin(1, 4);
            spin(0, 4);
            digitalWrite(5, 0x1);
            break;
        case(6):
            digitalWrite(6, 0x1);
            spin(1, 4);
            digitalWrite(5, 0x0);
            spin(0, 4);
            break;
        default:
            
# 312 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
           __null
# 312 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
               ;
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
                digitalWrite(2, 0x1);
                delayMicroseconds(2000);
                digitalWrite(2, 0x0);
                delayMicroseconds(2000);
            }
            break;

        case(1):
            for (int i = 0; i < stepsPerRevolution*steps; i++) {
                // These four lines result in 1 step:
                digitalWrite(3, 0x1);
                delayMicroseconds(2000);
                digitalWrite(3, 0x0);
                delayMicroseconds(2000);
            }
            break;

        default:
            
# 345 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino" 3 4
           __null
# 345 "/Users/ireshmadhusankha/Projects/Programming/FYP/shaggy/sketch.ino"
               ;
            break;
    }
}
