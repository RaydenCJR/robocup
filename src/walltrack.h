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

    // Track around water bottle (target distance ~150mm)
    int target = 150;
    int error = currentDist - target;
    
    // Fast tracking with multiple scenarios
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

// Scenario 3: Aggressive speed tracking for fast water bottle following
void walltrackFast(int targetDistance = 150) {
    static int currentDist = 0;
    currentDist = rightds.getDistance();
    int error = currentDist - targetDistance;
    
    // Aggressive high-speed tracking scenarios
    if (currentDist > 500) {
        // Lost bottle - spin to find it
        motors.move(200, -200);
    } else if (currentDist > 350) {
        // Far away - sharp turn toward bottle
        motors.move(300, 100);
    } else if (currentDist > 250) {
        // Moderately far - medium turn
        motors.move(250, 150);
    } else if (currentDist > 200) {
        // Getting close - gentle turn
        motors.move(200, 150);
    } else if (currentDist > 130 && currentDist < 170) {
        // Target zone - full speed ahead
        motors.move(300, 300);
    } else if (currentDist < 100) {
        // Too close - back up and turn
        motors.move(-150, -50);
    } else {
        // Fine adjustment
        int correction = error / 2;
        motors.move(200 - correction, 200 + correction);
    }
}

// Scenario 4: Precision tracking with smooth curves
void walltrackSmooth(int targetDistance = 150) {
    static int currentDist = 0;
    static int lastDist = 0;
    currentDist = rightds.getDistance();
    
    // Calculate approach rate
    int approachRate = currentDist - lastDist;
    lastDist = currentDist;
    
    int error = currentDist - targetDistance;
    
    // Smooth curve tracking with approach consideration
    if (currentDist > 300) {
        // Wide arc toward bottle
        motors.move(180, 120);
    } else if (currentDist > 220) {
        // Gentle arc
        motors.move(170, 140);
    } else if (currentDist > 180) {
        // Very gentle approach
        motors.move(160, 150);
    } else if (currentDist >= 130 && currentDist <= 170) {
        // Target maintained - cruise speed
        motors.move(160, 160);
    } else if (currentDist > 100) {
        // Slight drift away - gentle correction
        motors.move(150, 160);
    } else if (currentDist > 60) {
        // Getting too close - curve away
        motors.move(140, 170);
    } else {
        // Emergency - sharp turn away
        motors.move(100, 180);
    }
}

// Scenario 5: Adaptive tracking with hysteresis zones
void walltrackAdaptive(int targetDistance = 150) {
    static int currentDist = 0;
    static unsigned long lastUpdate = 0;
    currentDist = rightds.getDistance();
    
    // Different speed profiles for different zones
    const int zone1 = targetDistance + 100;  // 250
    const int zone2 = targetDistance + 50;   // 200
    const int zone3 = targetDistance + 20;   // 170
    const int zone4 = targetDistance - 20;   // 130
    const int zone5 = targetDistance - 50;   // 100
    const int zone6 = targetDistance - 80;   // 70
    
    if (currentDist > 400) {
        // Lost tracking - search pattern
        motors.move(150, -150);
    } else if (currentDist > zone1) {
        // Far zone - aggressive approach
        motors.move(250, 100);
    } else if (currentDist > zone2) {
        // Outer zone - moderate approach
        motors.move(200, 130);
    } else if (currentDist > zone3) {
        // Approach zone - gentle
        motors.move(180, 150);
    } else if (currentDist >= zone4 && currentDist <= zone3) {
        // Sweet spot - maintain
        motors.move(200, 200);
    } else if (currentDist > zone5) {
        // Drifting close - ease away
        motors.move(150, 180);
    } else if (currentDist > zone6) {
        // Close zone - turn away
        motors.move(120, 200);
    } else {
        // Too close - emergency maneuver
        motors.move(80, 220);
    }
}

// Scenario 6: Multi-sensor fusion tracking (uses front sensor for safety)
void walltrackFusion(int targetDistance = 150) {
    static int currentDist = 0;
    currentDist = rightds.getDistance();
    int frontDist = frontds.getDistance();
    
    // Check front sensor for obstacles
    if (frontDist < 80 && frontDist != 0) {
        // Obstacle ahead - stop or turn
        motors.move(-100, 100);
        return;
    }
    
    int error = currentDist - targetDistance;
    
    // Normal tracking with safety margin
    if (currentDist > 350) {
        motors.move(200, 50);
    } else if (currentDist > 250) {
        motors.move(180, 100);
    } else if (currentDist > 200) {
        motors.move(160, 120);
    } else if (currentDist > 170) {
        motors.move(150, 140);
    } else if (currentDist >= 130 && currentDist <= 170) {
        motors.move(150, 150);
    } else if (currentDist > 100) {
        motors.move(140, 160);
    } else if (currentDist > 70) {
        motors.move(120, 180);
    } else if (currentDist > 40) {
        motors.move(100, 200);
    } else {
        motors.move(50, 200);
    }
}