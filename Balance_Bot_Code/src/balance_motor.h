/** @file  task_motor_control.h
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"

#ifndef DRV8871_MOTOR_H
#define DRV8871_MOTOR_H

/**
 * @brief
 */
class DRV8871_Motor
{
private:
    // Right motor driver input pin 1
    uint8_t right_pinIN1;
    // Right motor driver input pin 2
    uint8_t right_pinIN2;
    // Left motor driver input pin 1
    uint8_t left_pinIN1;
    // Left motor driver input pin 2
    uint8_t left_pinIN2;

public:
    /**
     * @brief Default constructor that initializes motor instances.
     */
    DRV8871_Motor(uint8_t right_IN1, uint8_t right_IN2, uint8_t left_IN1, uint8_t left_IN2);

    /**
     * @brief Public method to drive the motor.
     * @param duty_cycle
     */
    void drive_motor(int16_t duty_cycle);

private:
    /**
     * @brief Private method to set motor speed and direction.
     * @param duty_cycle
     * @param direction
     */
    void set_motor_speed(int16_t duty_cycle, bool direction);
};

#endif // DRV8871_MOTOR_H