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
    if (currentDist > 400) {
        // Too far - turn sharper right toward bottle
        motors.move(120, 30);
    } else if (currentDist > 250) {
        // Moderately far - gentle right turn
        motors.move(100, 60);
    } else if (currentDist > 180) {
        // Slightly far - slight right correction
        motors.move(90, 75);
    } else if (currentDist > 120) {
        // Sweet spot - go straight
        motors.move(100, 100);
    } else if (currentDist > 80) {
        // Slightly close - slight left
        motors.move(75, 90);
    } else if (currentDist > 40) {
        // Moderately close - turn left
        motors.move(60, 100);
    } else {
        // Too close - sharp left away from bottle
        motors.move(30, 120);
    }
}
