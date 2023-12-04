/** @file  task_motor_control.h
 *
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"

/**
 * @brief
 */
class DRV8871_Motor
{
protected:

public:
    DRV8871_Motor(int IN1, int IN2, int speed_limit);

    void drive_motor(int speed);
    
};
