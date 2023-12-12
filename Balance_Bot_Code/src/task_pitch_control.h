/** @file  task_pitch_control.h
 *
 * @brief Header file for the task to control pitch using an MPU6050 and PID controller.
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
 *  @details Task function to control pitch using an MPU6050 and PID controller.
 *
 *  @param p_params A pointer to function parameters which we don't use.
 */
void task_pitch_control(void *p_params);