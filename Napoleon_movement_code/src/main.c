#include <kipr/wombat.h>

int main()
{
    int LIGHT = 0; // Variable für den Lichtsensor
    int DIST = 1;  // Variable für den Abstandssensor
    int BUTTON_1 = 0; // Variable für den ersten Button
    int BUTTON_2 = 1; // Variable für den zweiten Button
    int BOOL = 1; // Variable zur Steuerung der Schleife
    int GRAP_DIST = 1500; // Variable für die Distanz, bei der der Greifer schließen soll
    int GRAP_OPEN = 400; // Variable für die geöffnete Position des Greifers

    enable_servo(0); // Den Greifer aktivieren
    set_servo_position(0,GRAP_OPEN); // Den Greifer in die geöffnete Position bringen
    printf("Auf Licht warten\n"); // Ausgabe: "Auf Licht warten"
    while(1){
        msleep(200); // Warten für 200 ms
        if (analog(LIGHT) < 500){ // Wenn das Licht signal stark genug ist
            break; // Die Schleife verlassen
        }
    }
    shut_down_in(119); // Den Roboter nach 119 Sekunden herunterfahren

    printf("Start\n"); // Ausgabe: "Start"
    while(BOOL == 1){ // Solange BOOL gleich 1 ist
        motor(0,50); // Den linken Motor mit 50% betreiben
        motor(1,50); // Den rechten Motor mit 50% betreiben
        if(analog(DIST) > 2900){ // Wenn ein Objekt erkannt wird
            printf("Objekt erkannt!\n"); // Ausgabe: "Objekt erkannt!"
            while(1){ // Solange kein Objekt erfasst ist
                motor(0,20); // Den linken Motor mit 20% betreiben
                motor(1,20); // Den rechten Motor mit 20% betreiben
                if (analog(DIST) == GRAP_DIST){ // Wenn der Abstand zum Objekt gleich GRAP_DIST ist
                    set_servo_position(0,0); // Den Greifer schließen
                }
                motor(0,-50); // Den linken Motor mit -50% betreiben
                motor(1,-50); // Den rechten Motor mit -50% betreiben
                if (digital(BUTTON_1)==1 && digital(BUTTON_2)==1){ // Wenn beide Buttons gedrückt werden
                    printf("Ausgerichtet\n\n"); // Ausgabe: "Ausgerichtet"
                    motor(0,0); // Den linken Motor stoppen
                    motor(1,0); // Den rechten Motor stoppen
                    BOOL = 0; // BOOL auf 0 setzen
                    break; // Die Schleife verlassen
                }  
            }
        }
    }
    return 0;
}