/** @file  task_pitch_control.h
 *         
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include "PID_v1.h"

/** @brief
 *  @details
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_pitch_control(void *p_params);