/** @file  task_drive_motors.cpp
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_drive_motors.h"

// Right Motor
#define right_motor_IN1 14
#define right_motor_IN2 32

// Left Motor
#define left_motor_IN1 15
#define left_motor_IN2 33

#define max_signal 255
#define delay_time 1

void task_drive_motors(void *p_params)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("DRV8871 test");
    pinMode(left_motor_IN1, OUTPUT);
    pinMode(left_motor_IN2, OUTPUT);
    pinMode(right_motor_IN1, OUTPUT);
    pinMode(right_motor_IN2, OUTPUT);

    for (;;)
    {
        // ramp up forward
        digitalWrite(left_motor_IN1, LOW);
        digitalWrite(right_motor_IN2,  LOW);
        for (int i = 0; i < max_signal; i++)
        {
            analogWrite(left_motor_IN2, i);
            analogWrite(right_motor_IN1, i);
            vTaskDelay(delay_time);
        }

        // forward full speed for one second
        vTaskDelay(1000);

        // ramp down forward
        for (int i = max_signal; i >= 0; i--)
        {
            analogWrite(left_motor_IN2, i);
            analogWrite(right_motor_IN1, i);
            vTaskDelay(delay_time);
        }

        // ramp up backward
        digitalWrite(left_motor_IN2, LOW);
        digitalWrite(right_motor_IN1, LOW);
        for (int i = 0; i < max_signal; i++)
        {
            analogWrite(left_motor_IN1, i);
            analogWrite(right_motor_IN2, i);
            vTaskDelay(delay_time);
        }

        // backward full speed for one second
        vTaskDelay(1000);

        // ramp down backward
        for (int i = max_signal; i >= 0; i--)
        {
            analogWrite(left_motor_IN1, i);
            analogWrite(right_motor_IN2, i);
            vTaskDelay(delay_time);
        }
        vTaskDelay(1000);
    }
}