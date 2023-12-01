/** @file  task_drive_motors.cpp
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_read_encoders.h"

void task_read_encoders(void *p_params)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Reading Encoders");

    for (;;)
    {
    }
}