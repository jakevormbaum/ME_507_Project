/** @file  task_drive_motors.cpp
 *
 * @brief Implementation of the task to drive motors using a PID controller.
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_drive_motors.h"
#include "balance_motor.h"

#define control_rate 20

// Right Motor
#define right_motor_IN1 14
#define right_motor_IN2 32

// Left Motor
#define left_motor_IN1 15
#define left_motor_IN2 33

// Create motor instances
DRV8871_Motor dualMotor(right_motor_IN1, right_motor_IN2, left_motor_IN1, left_motor_IN2);

// Motor speeds
int speedLeft = 0;
int speedRight = 0;

// PID controller output
extern Share<int16_t> control;
int16_t dutyCycle;


/**
 * @brief Task function to drive motors using a PID controller.
 *
 * @param p_params Task parameters (not used).
 */
void task_drive_motors(void *p_params)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Balance Control");

    for (;;)
    {
        control.get(dutyCycle);
        Serial << "Motor Input: " << dutyCycle << endl;
        dualMotor.drive_motor(dutyCycle);
        vTaskDelay(1000 / control_rate);
    }
}