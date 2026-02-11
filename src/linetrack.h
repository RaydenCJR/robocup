#include "definitions.h"

void linetrack(int kp, int kd, float speed){   //10-100
    csleft.getRawRGBC(&lr, &lg, &lb, &lc);
    csright.getRawRGBC(&rr, &rg, &rb, &rc);



    // Calculate error
    int leftValue = map(lc, linputmin, linputmax, outputMin, outputMax);
    int rightValue = map(rc, rinputmin, rinputmax, outputMin, outputMax);
    int error = leftValue - rightValue;




    // Calculate derivative
    static int lastError = 0;
    int derivative = error - lastError;
    lastError = error;

    // Calculate motor speeds
    int correction = kp * error + kd * derivative;
    int leftSpeed = speed + correction;
    int rightSpeed = speed - correction;

    // Set motor speeds
    leftMotor.run(int(leftSpeed));
    rightMotor.run(int(rightSpeed));

}