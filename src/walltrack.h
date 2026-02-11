#include "definitions.h"

void walltrack(int kp, int kd, int speed, int targetDistance, int wallSide){
    static int currentDist = 0;
    // if (wallSide == 1){
    currentDist = rightds.getDistance();
    // } else {
    //     currentDist = leftds.getDistance();
    // }
    int error = currentDist - targetDistance;
    
    static int lastError = 0;
    int derivative = error - lastError;
    lastError = error;
    
    int correction = kp * error + kd * derivative;
    
    int lss, rss;
    if (wallSide == 0) {
        lss = speed - correction;
        rss = speed + correction;
    } else {
        lss = speed + correction;
        rss = speed - correction;
    }        
    evo.writeToDisplay(int(currentDist), 0, 56, true, true);
    leftMotor.run(lss);
    rightMotor.run(rss);


}

void walltrack2(){
    static int currentDist = 0;
    currentDist = rightds.getDistance();

    if 
}