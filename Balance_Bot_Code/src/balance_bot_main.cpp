/** @file  task_debounce.cpp
 *         This file contains a homework assignment task that implements
 *         a four part state machine. Using GPIO 13 as a input, the press
 *         of a button will pull the signal to ground and cause
 *         movement between states.
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include "task_read_imu.h"
#include "task_drive_motors.h"

extern Share<float> angle;

void setup(void)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial << "Balance Bot!" << endl;
    // xTaskCreate(task_read_imu, "Read IMU", 2048, NULL, 4, NULL);
    xTaskCreate(task_drive_motors, "Drive Motors", 2048, NULL, 2, NULL);
}

void loop(void)
{
    // Delay for a whole minute, which is an eternity to a microcontroller
    vTaskDelay(60000);
}