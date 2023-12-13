/** @file  balance_bot_main.cpp
 *
 * @brief Main file for the Balance Bot application.
 * * This code uses several external libraries. Make sure to include them in your project.
 * 
 * - [ME507-Support library](https://github.com/spluttflob/ME507-Support)
 * - [Arduino-PrintStream library](https://github.com/spluttflob/Arduino-PrintStream.git)
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


/**
 * @brief Arduino setup function. Initializes serial communication and creates FreeRTOS tasks.
 */
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


/**
 * @brief Arduino main loop function. Delays for a minute.
 */
void loop(void)
{
    // Delay for a whole minute, which is an eternity to a microcontroller
    vTaskDelay(60000);
}