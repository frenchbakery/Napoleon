#include <kipr/wombat.h>

//Def fix variabeln
int Servo_Arm_1 = 0;	//Servo-Ports fuer den Arm
int Servo_Arm_2 = 2;	//Servo-Ports fuer den Arm
int Servo_Greifer = 1; 	//Servo-Port fuer den Greifer
int Greifer_offen = 1600;
int Greifer_zu = 1200;
int Servo_pos_1 = 0;	//Position fuer Unten
int Servo_pos_2 = 2047;	//Position fuer Unten
int Change_Value = 1;	//Arm-Geschwindigkeit rauf runter
int DIST = 0;
int LIGHT = 1;

void Arm(int hoehe){
    printf("Arm\n"); 
    Servo_pos_1 = get_servo_position(Servo_Arm_1);
    Servo_pos_2 = get_servo_position(Servo_Arm_2);
    while(Servo_pos_2 < hoehe || Servo_pos_2 > hoehe){		//Max = 2047
        set_servo_position(Servo_Arm_1,Servo_pos_1);
        set_servo_position(Servo_Arm_2,Servo_pos_2);
        if (Servo_pos_2 < hoehe) {
        	Servo_pos_1 -= Change_Value;
        	Servo_pos_2 += Change_Value;
        	msleep(2.5);
        }
        if (Servo_pos_2 > hoehe) {
           Servo_pos_1 += Change_Value;
        	Servo_pos_2 -= Change_Value;
        	msleep(2.5); 
    	}
	}
}

void Starteinstellungen(){
    enable_servo(Servo_Arm_1);
    enable_servo(Servo_Arm_2);
    enable_servo(Servo_Greifer);
    Arm(0);
    set_servo_position(Servo_Greifer,Greifer_offen);
    printf("Auf Licht warten...\n");
    while(1){
    	if(analog(LIGHT) < 300){
        	break;
        }
    }
    shut_down_in(117);
}

int main()
{
    //Hauptprogramm
    Starteinstellungen();
    printf("Start\n");
    Arm(900);
	//Robo aus der Box
    motor(0,60);
    motor(1,60);
    msleep(4000);
    //Linksdrift 45 Grad
    motor(1,-40);
    motor(0,40);
   	msleep(800);
    //Grade wieder
    motor(1,40);
    motor(0,40);
    
    //Smartes Ranfahren
    printf("Smart Ranfahrn\n");
    while(1){
        if(analog(DIST) > 1500){
            motor(0,0);
            motor(1,0);
            break;
        }
    }
    
    //Smarte Detection
    printf("Detection\n");
    motor(1,-20);
    motor(0,20);
    while(1){
        if(analog(DIST) > 1600){
            motor(1,15);
            motor(0,-15);
            break;
        }
    }
    msleep(500);
	while(1){
        if(analog(DIST) > 1500){
        	break;
        }
    }
   
    //Schublade?
    printf("Schublade\n");
    motor(0,20);
    motor(1,20);
    while(1){
    	if(analog(DIST) > 2000){
        motor(0,0);
		motor(1,0);
		break;
        }
    }
    set_servo_position(Servo_Greifer,Greifer_zu);
    msleep(600);
    Arm(0);
    motor(0,-40);
    motor(1,-40);
    msleep(600);
    set_servo_position(Servo_Greifer,Greifer_offen);
    msleep(2000);
    motor(0,0);
    motor(1,0);
    
    //bissl schiefer (rechts)
	motor(0,-40);
    msleep(700);
    motor(0,0);
    //Arm heben
    Arm(1200);
    //Grade wieder
    motor(1,40);
    motor(0,40);
    msleep(2700);	//2100 + Schubladenziehzeit
    //Stop
    motor(0,0);
    motor(1,0);
    //Vorfahrn
    motor(0,40);
    motor(1,40);
    msleep(600);
    //bissl Links
    motor(1,-40);
    msleep(400);
    motor(0,0);
    motor(1,0);
    //Hebel schalten
    set_servo_position(Servo_Greifer,950);
    Arm (1500);
    //Zurueck in die Box
    motor(0,-40);
    motor(1,-40);
    msleep(2000);
    motor(1,40);
    msleep(1000);
    motor(1,-40);
    msleep(8000);
    motor(0,20);
    motor(1,-20);
    msleep(1000);
    motor(0,0);
    motor(1,0);
    Arm(0);
    
    
    return 0;
}
