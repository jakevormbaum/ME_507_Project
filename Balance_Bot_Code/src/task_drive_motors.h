/** @file  task_drive_motors.h
 *
 * @brief Header file for the task to drive motors using a PID controller.
 *  * This code uses several external libraries. Make sure to include them in your project.
 *  * - [ME507-Support library](https://github.com/spluttflob/ME507-Support)
 * - [Arduino-PrintStream library](https://github.com/spluttflob/Arduino-PrintStream.git)
 * - [Arduino-PID-Library](https://github.com/br3ttb/Arduino-PID-Library.git)
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "PID_v1.h"
#include "balance_motor.h"

/** @brief
 *  @details Task function to drive motors using a PID controller.
 *
 *  @param p_params A pointer to function parameters which we don't use.
 */
void task_drive_motors(void *p_params);