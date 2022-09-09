
int rpm;
const int FIRST_LOWER = 2000;
const int FIRST_UPPER =2500;
const int SECOND_LOWER = 2500;
const int SECOND_UPPER = 3000;
const int THIRD_LOWER = 3500;
const int THIRD_UPPER = 4000;
const int FOURTH_LOWER = 4500;
const int FOURTH_UPPER = 5000;

void setup()
{
	
}

void loop()
{
	
}

void changeGear(){
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
}

void controlClutch(){
    
}

void gearOne(){

}

void gearTwo(){

}

void gearThree(){

}

void gearFour(){

}

void reverse(){

}

void neutral(){

}