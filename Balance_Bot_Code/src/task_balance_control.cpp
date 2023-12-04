/** @file  task_balance_control.cpp
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "PID_v1.h"
#include "task_balance_control.h"

double kP = 24;
double kI = 350;
double kD = 1.2;

double setpoint, input, output;   // PID variables
PID pid(&input, &output, &setpoint, kP, kI, kD, DIRECT); // PID setup

void task_balance_control(void *p_params)
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Balance Control");

    for (;;)
    {

    }
}