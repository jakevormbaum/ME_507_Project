/** @file  balance_bot_main.cpp
 * 
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_read_imu.h"
#include "task_test_motors.h"

extern Share<float> angle;

void setup(void)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial << "Balance Bot!" << endl;
    // xTaskCreate(task_read_imu, "Read IMU", 2048, NULL, 4, NULL);
    xTaskCreate(task_test_motors, "Test Motors", 2048, NULL, 2, NULL);
}

void loop(void)
{
    // Delay for a whole minute, which is an eternity to a microcontroller
    vTaskDelay(60000);
}