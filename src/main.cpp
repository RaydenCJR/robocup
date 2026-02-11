#include "definitions.h"
#include "linetrack.h"
#include "walltrack.h"
void setup()
{
  intialise();
  leftMotor.brake();
  rightMotor.brake();
  evo.playTone(1000, 200);
  
 

  while (button.getButton(1) == 0)
  {
    // evo.playTone(1000, 200);
    displayValues();
  }
  evo.playTone(1000, 200);

  int frontDistance = frontds.getDistance();
  int criteriaCount = 0;
  int inLoopCount = false;


  button.waitForBump(1);
  while (button.getButton(1) == 0 ){
    frontDistance = frontds.getDistance();
    
    if (frontDistance < 90 && frontDistance != 0){
      if (!inLoopCount){
        criteriaCount += 1;
        inLoopCount = true;
      }else{
        criteriaCount+=1;
        
      }
      if (criteriaCount > 3){
        break;
      }
      
      
    }else{
      if (inLoopCount){
        inLoopCount = false;
        criteriaCount = 0;
      }

    }



    linetrack(55, 20, 4100); 
  }
  motors.brake();
  // evo.clearDisplay();
  // evo.writeToDisplay(leftMotor.getAngle(), 80, 56);
  // evo.drawDisplay();

  motors.moveDegrees(-4800,-4800, 120);
  motors.moveDegrees(-2000, 2000, 125);
  motors.moveDegrees(4500, 4500, 60);
  while (rc > 100){
    csright.getRawRGBC(&rr, &rg, &rb, &rc);
    walltrack(2, 13, 1500, 230, 1); //kp kd speed targetDistance wallSide
  }
  leftMotor.brake();
  rightMotor.brake();
  evo.playTone(1000, 200);
  motors.moveDegrees(2000, 2000, 125);
  while (rc > 93){
    csright.getRawRGBC(&rr, &rg, &rb, &rc);
    motors.move(0, 1500);
  }
  motors.brake();
}

void loop()
{
  delay(10);
  if (button.getButton(2) == 1)
  {
    esp_restart();
  }
}