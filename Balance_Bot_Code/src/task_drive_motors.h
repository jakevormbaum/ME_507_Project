/** @file  task_drive_motors.h
 *
 * @brief Header file for the task to drive motors using a PID controller.
 *
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