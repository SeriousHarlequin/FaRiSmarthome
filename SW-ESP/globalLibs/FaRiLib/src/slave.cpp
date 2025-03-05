#include "slave.h"
#include "modulesDefinitions.h"

TaskState checkConnectedModule(){
    static unsigned long timeADC = 0;
    static TaskState moduleSet = NONE;


    if(millis() - timeADC > WAIT_ADC){
        timeADC = millis();
        int rawADC = analogRead(MOD_PIN);
        Serial.println(rawADC);
    
        //Überprüfen welches Modul angesteckt ist
        if((MOTION_ADC - TOLERANZ) < rawADC  && rawADC < (MOTION_ADC + TOLERANZ)){
          moduleSet = MOTION;
        } 
        else if((SWITCH_ADC - TOLERANZ) < rawADC  && rawADC < (SWITCH_ADC + TOLERANZ)){
          moduleSet = SWITCH;
        } 
        else if(rawADC <= 100)
          moduleSet = NONE;
    }
    return moduleSet;
}