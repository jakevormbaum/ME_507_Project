/** @file  stat_tracker.cpp
 *         This file contains a homework assignment that uses
 *         classes to perform statistical analysis on a data set.
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include <cmath>
#include "stat_tracker.h"

/**
 * @brief Default constructor that initializes variables for zero data.
 */
StatTracker::StatTracker(void)
{
    numPoints = 0;
    sum = 0;
    sumSquares = 0;
}

/**
 * @brief Add one float data point to the set being tracked.
 * @param data The float data point to be added.
 */
void StatTracker::add_data(float data)
{

    numPoints++;
    sum += data;
    sumSquares += data * data;
}

/**
 * @brief Add one signed integer data point to the set being tracked.
 * @param data The signed integer data point to be added.
 */
void StatTracker::add_data(int32_t data)
{

    numPoints++;
    sum += data;
    sumSquares += data * data;
}

/**
 * @brief Add one unsigned integer data point to the set being tracked.
 * @param data The unsigned integer data point to be added.
 */
void StatTracker::add_data(uint32_t data)
{

    numPoints++;
    sum += data;
    sumSquares += data * data;
}

/**
 * @brief Returns the number of data points added.
 * @return The number of data points.
 */
uint32_t StatTracker::num_points(void)
{
    return numPoints;
}

/**
 * @brief Returns the average of the data.
 * @return The average of the data.
 */
float StatTracker::average(void)
{
    if (numPoints == 0) // Avoid divide by 0 if no data.
    {
        return 0;
    }
    else
    {
        return sum / numPoints;
    }
}

/**
 * @brief Returns the standard deviation of the data.
 * @return The standard deviation of the data.
 */
float StatTracker::std_dev(void)
{
    if (numPoints == 0) // Avoid divide by zero if no data.
    {
        return 0;
    }
    return sqrt((sumSquares / numPoints) - pow((sum / numPoints), 2));
}

/**
 * @brief Deletes all the data, returning to no points added state.
 */
void StatTracker::clear(void)
{
    numPoints = 0;
    sum = 0;
    sumSquares = 0;
}