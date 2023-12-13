/** @file  task_pitch_control.h
 *
 * @brief Header file for the task to control pitch using an MPU6050 and PID controller.
 *
 *  * This code uses several external libraries. Make sure to include them in your project.
 * - [MPU6050 library](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
 * - [ME507-Support library](https://github.com/spluttflob/ME507-Support)
 * - [Arduino-PrintStream library](https://github.com/spluttflob/Arduino-PrintStream.git)
 * - [Arduino-PID-Library](https://github.com/br3ttb/Arduino-PID-Library.git)
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