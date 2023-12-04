/** @file  main.cpp
 *         This file contains a homework assignment involving a
 *         4 step state machine that is controlled using a pushbutton.
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "stat_tracker.h"

const uint16_t size = 20;
uint32_t data[size] = {
    70,
    7,
    37,
    66,
    18,
    84,
    10,
    21,
    79,
    36,
    89,
    92,
    62,
    53,
    26,
    70,
    54,
    27,
    69,
    27,

};
uint32_t add = 10;
StatTracker test;

/** @brief   Arduino setup function which runs once at program startup.
 *  @details This function sets up a serial port for communication and creates the
 *           tasks which will be run.
 */
void setup(void)
{
    // The serial port must begin before it may be used
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial << "Statistically Significant!" << endl;
    for (uint16_t i = 0; i < size; i++)
    {
        test.add_data(data[i]);
    }
    Serial << test.average() << endl;
    Serial << test.std_dev() << endl;
    Serial << test.num_points() << endl;

    test.add_data(add);

    Serial << test.average() << endl;
    Serial << test.std_dev() << endl;
    Serial << test.num_points() << endl;

    test.clear();

    Serial << test.average() << endl;
    Serial << test.std_dev() << endl;
    Serial << test.num_points() << endl;
}

void loop(void)
{
}