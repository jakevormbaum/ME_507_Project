/** @file  task_debounce.cpp
 *         This file contains a homework assignment task that implements
 *         a four part state machine. Using GPIO 13 as a input, the press
 *         of a button will pull the signal to ground and cause
 *         movement between states.
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_debounce.h"

// The pushbutton is connected to GND and GPIO 13.
const uint8_t DEBOUNCE_PIN = 13;
// This bool is assigned value based on the state of pushbutton.
bool hide_wave;
// Define the inter-task shared variable.
Share<bool> hide("Hide Wave");

/** @brief   Task function which defines a four part state machine.
 *  @details This task is run in main.cpp using FreeRTOS. It continuosly
 *           loops and makes checks of the push button that determines the state
 *           of the system.
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_debounce(void *p_params)
{
    // An 8 bit integer stores the State 0-3.
    uint8_t state = 0;
    // A counter is initialized.
    uint8_t count = 0;
    // timer is a value used in conjunction with count.
    uint16_t timer;
    // GPIO 13 is setup as an input with a pullup resistor.
    pinMode(DEBOUNCE_PIN, INPUT_PULLUP);

    for (;;)
    {
        if (state == 0)
        {
            // Reset counter
            count = 0;
            // Wait for push
            bool button = digitalRead(DEBOUNCE_PIN);
            // GPIO 13 is pulled to logic 0 when button is pushed
            if (button == 0)
            {
                state = 1;
            }
            // Show wave
            hide_wave = false;
            hide.put(hide_wave);
        }
        else if (state == 1)
        {
            // Print "?"
            Serial << "?";
            // Show wave
            hide_wave = false;
            hide.put(hide_wave);
            // Released?
            bool button = digitalRead(DEBOUNCE_PIN);
            if (button == 1)
            {
                state = 0;
            }
            /*Add one tick every time the task runs in
            State 1 and calculate elapsed time
            */
            count++;
            timer = count * 0.1;
            /*A while loop is used to latch the state at 2.
            This ensures that you can't cycle through all the
            states by holding the button but must release and press the
            button again to get to State 3
            */
            while (timer >= 5)
            {
                // Print "@"
                Serial << "@";
                // Hide wave
                hide_wave = true;
                hide.put(hide_wave);
                // Released?
                bool button = digitalRead(DEBOUNCE_PIN);
                if (button == 1)
                {
                    // If the button is released past 5 seconds, break out to state 2
                    state = 2;
                    break;
                }
                delay(100);
            }
        }
        else if (state == 2)
        {
            // Reset counter
            count = 0;
            // Print "@"
            Serial << "@";
            // Hide wave
            hide_wave = true;
            hide.put(hide_wave);
            // Wait for push
            bool button = digitalRead(DEBOUNCE_PIN);
            if (button == 0)
            {
                state = 3;
            }
        }
        else if (state == 3)
        {
            // Print "!"
            Serial << "!";
            // Hide wave
            hide_wave = true;
            hide.put(hide_wave);
            // Released?
            bool button = digitalRead(DEBOUNCE_PIN);
            if (button == 1)
            {
                state = 2;
            }
            /*Add one tick every time the task runs in
            State 3 and calculate elapsed time
            */
            count++;
            timer = count * 0.1;
            // Same latching logic as in State 1
            while (timer >= 1)
            {
                // Show wave
                hide_wave = false;
                hide.put(hide_wave);
                // Released?
                bool button = digitalRead(DEBOUNCE_PIN);
                if (button == 1)
                {
                    state = 0;
                    break;
                }
                delay(100);
            }
        }
        vTaskDelay(100);
    }
}