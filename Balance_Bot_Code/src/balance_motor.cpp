/** @file  task_balance_control.cpp
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "balance_motor.h"

DRV8871_Motor::DRV8871_Motor(uint8_t right_IN1, uint8_t right_IN2, uint8_t left_IN1, uint8_t left_IN2)
    : right_pinIN1(right_IN1), right_pinIN2(right_IN2), left_pinIN1(left_IN1), left_pinIN2(left_IN2)
{
    pinMode(right_IN1, OUTPUT);
    pinMode(right_IN2, OUTPUT);
    pinMode(left_IN1, OUTPUT);
    pinMode(left_IN2, OUTPUT);
}

void DRV8871_Motor::drive_motor(int16_t dutyCycle)
{
    // Set motor speed and direction
    set_motor_speed(abs(dutyCycle), dutyCycle >= 0);
}

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
