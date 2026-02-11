#ifndef DEF_H
#define DEF_H
#include <Arduino.h>
#include <Evo.h>

int linputmin = 80;
int linputmax = 336;
int rinputmin = 69;
int rinputmax = 286;
int outputMin = -20;
int outputMax = 300;


EVOX1 evo;
EvoMotor leftMotor(M2, EVOMotor100, false);
EvoMotor rightMotor(M1, EVOMotor100, true);
EvoTriButton button(GPIO1);
EvoRGBColorSensor csleft(I2C8);
uint16_t lr, lg, lb, lc;
EvoRGBColorSensor csright(I2C7);
uint16_t rr, rg, rb, rc;
EvoTOF frontds(I2C4);
EvoTOF rightds(I2C5);
EvoMotorPair motors(&leftMotor, &rightMotor);
EvoTOF leftds(I2C6);
void buttonISR() {
  esp_restart();
}


void intialise(){
    evo.begin();
    leftMotor.begin();
    rightMotor.begin();
    csleft.begin();
    csleft.setGain(TCS34725_GAIN_16X);
    csright.begin();
    csright.setGain(TCS34725_GAIN_16X);
    frontds.begin();
    rightds.begin();
    leftds.begin();
    frontds.setHighSpeedMode();
    rightds.setHighSpeedMode();
    leftds.setHighSpeedMode();
    pinMode(GPIO3, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(GPIO3), buttonISR, RISING);

    motors.setStartSpeed(2000);
    motors.setEndSpeed(2000);
}

void displayValues(){
    csleft.getRawRGBC(&lr, &lg, &lb, &lc);
    csright.getRawRGBC(&rr, &rg, &rb, &rc);
    evo.clearDisplay();
    evo.writeToDisplay(int(frontds.getDistance()), 0, 56); //front right left
    evo.writeToDisplay(int(rightds.getDistance()), 30, 56);
    evo.writeToDisplay(int(leftds.getDistance()), 60, 56);
    evo.writeToDisplay(int(map(lc, linputmin, linputmax, outputMin, outputMax)), 0, 40);
    evo.writeToDisplay(int(map(rc, rinputmin, rinputmax, outputMin, outputMax)), 0, 48);
    evo.writeToDisplay(evo.getBattery(), 0, 0);
    evo.writeToDisplay("Left CS:", 0, 8);
    evo.writeToDisplay(int(lr), 0, 16);
    evo.writeToDisplay(int(lg), 30, 16);
    evo.writeToDisplay(int(lb), 60, 16);
    evo.writeToDisplay(int(lc), 90, 16);
    evo.writeToDisplay("Right CS:", 0, 24);
    evo.writeToDisplay(int(rr), 0, 32);
    evo.writeToDisplay(int(rg), 30, 32);
    evo.writeToDisplay(int(rb), 60, 32);
    evo.writeToDisplay(int(rc), 90, 32);
    evo.drawDisplay();

}



#endif