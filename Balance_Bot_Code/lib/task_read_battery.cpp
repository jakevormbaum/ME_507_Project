/** @file  task_read_battery.cpp
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_read_battery.h"

#define batteryPIN 13
float voltage_battery = 0;

void task_read_battery(void *p_params)
{
    pinMode(batteryPIN, INPUT);
    for (;;)
    {
        voltage_battery = analogRead(batteryPIN);
        voltage_battery *= 2;
        voltage_battery *= 3.3;
        voltage_battery /= 1024;
        Serial << "Battery Voltage: " << voltage_battery << endl;
        vTaskDelay(10000);
    }
}
