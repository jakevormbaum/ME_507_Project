/** @file  task_pitch_control.cpp
 *
 * @brief Implementation of the task to control pitch using an MPU6050 and PID controller.
 *
 * * This code uses several external libraries. Make sure to include them in your project.
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
#include "task_pitch_control.h"

// The inter-task variables are initialized.
Share<int16_t> control;

// IMU sample rate (Hz)
const uint8_t imu_rate = 20;

MPU6050 mpu(0x69); // Delete (0x69) for breakout board

/// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// Orientation/motion vars
Quaternion q;        // [w, x, y, z]         quaternion container
VectorInt16 aa;      // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity; // [x, y, z]            gravity vector
float euler[3];      // [psi, theta, phi]    Euler angle container
float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// PID setup
double kP = 15;
double kI = 2;
double kD = 4;

// PID variables
double setpoint = 0;
double input;
double output;

// PID setup
PID myPID(&input, &output, &setpoint, kP, kI, kD, REVERSE);


/**
 * @brief Task function to control pitch using an MPU6050 and PID controller.
 *
 * @param p_params A pointer to function parameters which we don't use.
 */
void task_pitch_control(void *p_params)
{
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock.

    Serial.begin(115200);
    while (!Serial)
    {
    }

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready!"));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(35, 240); 

    for (;;)
    {
        // if programming failed, don't try to do anything
        if (!dmpReady)
            return;
        // read a packet from FIFO
        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
        {
            // Get the Latest packet
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            // Serial << "Pitch: " << ypr[1] * 180 / M_PI << endl;
        }

        // PID calculations
        input = abs(ypr[1] * 180 / M_PI);
        myPID.Compute();
        // Serial << "PID Output: " << output << endl;

        // Put output in shared variable
        if (ypr[1] > 0)
        {
            control.put(output * -1);
        }
        else
        {
            control.put(output);
        }
        vTaskDelay(1000 / imu_rate);
    }
}
