/** @file  main.cpp
 *         This file contains a homework assignment involving a
 *         4 step state machine that is controlled using a pushbutton.
 * @author Jake Vormbaum
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "task_debounce.h"

// The 250 Hz wave is output on GPIO 12.
const uint8_t WAVE_PIN = 12;
// Half the period of the wave is calculated in ms.
const uint16_t wave_delay = 1000 / (2 * 250);
// The inter-task variable is initialized.
extern Share<bool> hide;

/** @brief   Task function which creates the 250 Hz square wave.
 *  @details This task runs creates a 250 Hz square wave by cycling
 *           a pin high and low based on a calculated half period. The task is run
 *           when it recieves a false value for the hide variable from the state machine.
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_fast_wave(void *p_params)
{
    for (;;)
    {
        // A bool value is initialized that controls the wave on-off behavior
        bool hide_wave;
        // The inter-task variable is acquired
        hide.get(hide_wave);
        // GPIO 12 is configured as an output
        pinMode(WAVE_PIN, OUTPUT);
        // The wave is turned on
        if (hide_wave == false)
        {
            digitalWrite(WAVE_PIN, HIGH);
            vTaskDelay(wave_delay);
            digitalWrite(WAVE_PIN, LOW);
            vTaskDelay(wave_delay);
        }
        // Otherwise, the pin is commanded low and a delay is used before checking again.
        else
        {
            digitalWrite(WAVE_PIN, LOW);
            vTaskDelay(1);
        }
    }
}

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
    Serial << "Tasks and States!" << endl;
    xTaskCreate(task_debounce, "Debounce", 1024, NULL, 2, NULL);
    xTaskCreate(task_fast_wave, "250 Hz Square Wave", 1024, NULL, 5, NULL);
}

/** @brief   Arduino's low-priority loop function, which we don't use.
 *  @details A non-RTOS Arduino program runs all of its continuously running
 *           code in this function after @c setup() has finished. 
 */
void loop(void)
{
    // Delay for a whole minute, which is an eternity to a microcontroller
    vTaskDelay(60000);
}