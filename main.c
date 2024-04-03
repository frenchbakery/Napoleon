#include <kipr/wombat.h>

int main()
{
    int LIGHT = 0;	//Lichtsensor
    int DIST = 1;	//Abstandsensor
    int BUTTON_1 = 0;	//Knöpfe hinten zum an Wand kalibrieren
    int BUTTON_2 = 1;
    int BOOL = 1;	//Für die Hauptschleife
    int GRAP_DIST = 2900;	//Abstand zum Greifen
    int GRAP_OPEN = 400;	//Servo-Position Greifer offen
    int GRAP_CLOSE = 50;	//Servo-Position Greifer zu
    
    enable_servo(0);
    set_servo_position(0,GRAP_OPEN);
    
    printf("Auf Licht warten\n");
    while(1){
    msleep(200);
    if (analog(LIGHT) < 500){
    	break;
    	}
    }
    shut_down_in(119);	//Shutdown nach 2min
    
    //Hauptprogramm
    printf("Start\n");
    while(BOOL == 1){
    	motor(0,50);
   		motor(1,50);
    	if(analog(DIST) > 2900){	//Wenn in Nähe von Objekt (Pool-Nudel, Stange,...); Begrenzung wird nicht erkannt
            printf("Objekt erkannt!\n");
    			motor(0,10);
                motor(1,10);
            	while(1){
                	if (analog(DIST) == GRAP_DIST){		//Sobald in Nähe zum Greifen
                		set_servo_position(0,GRAP_CLOSE);
                		break;
                	}
                }
                motor(0,-50);
                motor(1,-50);
                if (digital(BUTTON_1)==1 && digital(BUTTON_2)==1){	//Sobald an Wand kalibriert
                	printf("Ausgerichtet\n\n");
                    motor(0,0);
                    motor(1,0);
                    BOOL = 0;	//Hauptschleife Aus
                   	break;
                }  
   		}
    }
    return 0;
