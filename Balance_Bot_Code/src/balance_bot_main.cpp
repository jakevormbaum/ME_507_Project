/** @file  balance_bot_main.cpp
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_pitch_control.h"
// #include "task_test_motors.h"
#include "task_drive_motors.h"
// #include "task_read_battery.h"

void setup(void)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial << "Balance Bot!" << endl;
    xTaskCreate(task_pitch_control, "Read IMU", 2048, NULL, 4, NULL);
    xTaskCreate(task_drive_motors, "Balance with Motors", 4096, NULL, 2, NULL);
    // xTaskCreate(task_test_motors, "Test Motors", 2048, NULL, 2, NULL);
    // xTaskCreate(task_read_battery, "Read Battery Voltage", 1024, NULL, 10, NULL);
}

void loop(void)
{
    // Delay for a whole minute, which is an eternity to a microcontroller
    vTaskDelay(60000);
}