/** @file  stat_tracker.h
 *         This file contains a homework assignment that uses
 *         classes to perform statistical analysis on a data set.     
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"

/**
 * @brief A class for tracking and computing statistical parameters from a set of measurements.
 */
class StatTracker 
{
protected:
    uint32_t numPoints;  // Number of data points
    float sum;           // Sum of the data points
    float sumSquares;    // Sum of the squares of the data points

public:

    StatTracker(void);

    void add_data(float data);

    void add_data(int32_t data);

    void add_data(uint32_t data);

    uint32_t num_points(void);

    float average(void);

    float std_dev(void);

    void clear(void);
};