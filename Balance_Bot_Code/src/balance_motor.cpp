/** @file  task_balance_control.cpp
 *
 * @brief Implementation of the DRV8871_Motor class for controlling motors in a balance control task.
 *  * This code uses several external libraries. Make sure to include them in your project.
 * - [ME507-Support library](https://github.com/spluttflob/ME507-Support)
 * - [Arduino-PrintStream library](https://github.com/spluttflob/Arduino-PrintStream.git)
 * 
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "balance_motor.h"


/**
 * @brief Constructor for DRV8871_Motor class.
 *
 * @param right_IN1 Pin for right motor input 1.
 * @param right_IN2 Pin for right motor input 2.
 * @param left_IN1 Pin for left motor input 1.
 * @param left_IN2 Pin for left motor input 2.
 */

DRV8871_Motor::DRV8871_Motor(uint8_t right_IN1, uint8_t right_IN2, uint8_t left_IN1, uint8_t left_IN2)
    : right_pinIN1(right_IN1), right_pinIN2(right_IN2), left_pinIN1(left_IN1), left_pinIN2(left_IN2)
{
    pinMode(right_IN1, OUTPUT);
    pinMode(right_IN2, OUTPUT);
    pinMode(left_IN1, OUTPUT);
    pinMode(left_IN2, OUTPUT);
}


/**
 * @brief Drive the motor with the specified duty cycle.
 *
 * @param dutyCycle The duty cycle of the motor, ranging from -255 to 255.
 */

void DRV8871_Motor::drive_motor(int16_t dutyCycle)
{
    // Set motor speed and direction
    set_motor_speed(abs(dutyCycle), dutyCycle >= 0);
}


/**
 * @brief Set the motor speed and direction.
 *
 * @param dutyCycle The duty cycle of the motor, ranging from 0 to 255.
 * @param direction The direction of the motor (true for forward, false for reverse).
 */
void DRV8871_Motor::set_motor_speed(int16_t dutyCycle, bool direction)
{
    if (direction == true)
    {
        digitalWrite(right_pinIN1, LOW);
        analogWrite(right_pinIN2, dutyCycle);
        digitalWrite(left_pinIN2, LOW);
        analogWrite(left_pinIN1, dutyCycle);
    }
    else if (direction == false)
    {
        digitalWrite(right_pinIN2, LOW);
        analogWrite(right_pinIN1, dutyCycle);
        digitalWrite(left_pinIN1, LOW);
        analogWrite(left_pinIN2, dutyCycle);
    }
}
