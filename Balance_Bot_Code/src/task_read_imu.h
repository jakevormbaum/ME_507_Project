/** @file  task_read_imu.h
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

/** @brief
 *  @details
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_read_imu(void *p_params);