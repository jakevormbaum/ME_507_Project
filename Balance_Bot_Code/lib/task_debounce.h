/** @file  task_debounce.h
 *         This is a header file for the task that
 *         defines the four part state machine used in HW 4.
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"

// The comment for this function is in the .cpp file
void task_debounce(void *p_params);