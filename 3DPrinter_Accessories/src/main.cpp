#include <Arduino.h>

#include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <AverageThermistor.h>

#include <L298NX2.h>

#include <Adafruit_SleepyDog.h>

#define SENSOR_PIN A3
#define REFERENCE_RESISTANCE 100000
#define NOMINAL_RESISTANCE 100000
#define NOMINAL_TEMPERATURE 25
#define B_VALUE 3950

#define IDEAL_TEMP 32

/**
  How many readings are taken to determine a mean temperature.
  The more values, the longer a calibration is performed,
  but the readings will be more accurate.
*/
#define READINGS_NUMBER 10

/**
  Delay time between a temperature readings
  from the temperature sensor (ms).
*/
#define DELAY_TIME 10

Thermistor *thermistor = NULL;

const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;

const unsigned int lightSwitch = 12;
unsigned int aSpeed = 50;
unsigned int lightSwitchValue = 0;

L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

void setup()
{
  // put your setup code here, to run once:

  // Used to display information

  thermistor = new AverageThermistor(
      new NTC_Thermistor(
          SENSOR_PIN,
          REFERENCE_RESISTANCE,
          NOMINAL_RESISTANCE,
          NOMINAL_TEMPERATURE,
          B_VALUE),
      READINGS_NUMBER,
      DELAY_TIME);

  pinMode(lightSwitch, INPUT); // sets the digital pin 12 as input
  motors.forward();
  motors.setSpeedA(aSpeed);
}
/*
Print some informations in Serial Monitor
*/

void loop()
{
  // put your main code here, to run repeatedly:
  // ramp up/ ramp down speed for temp
  const double celsius = thermistor->readCelsius();

  if (celsius > IDEAL_TEMP)
  {
    if (aSpeed >= 255)
      ;
    else
    {
      aSpeed += 20;
      if (aSpeed >= 255)
        aSpeed = 255;
      motors.setSpeedA(aSpeed);
    }
  }

  else if (celsius < IDEAL_TEMP)
  {
    if (aSpeed <= 0)
      ;
    else
    {
      aSpeed -= 20;
      if (aSpeed <= 0)
        aSpeed = 0;
      motors.setSpeedA(aSpeed);
    }

    ;
  }
  // LED based on if Switch is on
  lightSwitchValue = digitalRead(lightSwitch);

  if (lightSwitchValue == 1)
  {
    motors.forwardB();
    motors.setSpeedB(155);
  }
  else if (lightSwitchValue == 0)
  {
    motors.stopB();
    motors.setSpeedB(0);
  }

  delay(1000);
}