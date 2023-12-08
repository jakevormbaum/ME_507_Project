/** @file  task_read_battery.h
 *         
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"

/** @brief
 *  @details
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_read_battery(void *p_params);