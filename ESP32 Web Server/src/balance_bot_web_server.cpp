/** @file balance_bot_web_server.cpp
 *
 * @brief Main file for the Balance Bot web server application.
 *
 * This file contains the setup and loop functions, as well as the implementation of tasks
 * responsible for handling the web server, reading IMU data, and serving HTML pages.
 *
 * @author Jack Raventos
 */

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <PrintStream.h>

MPU6050 mpu;
float imuAngles[3];

WebServer server(80);

/**
 * @brief Generates the HTML header for the web page.
 *
 * @param a_string The string to which the HTML header will be appended.
 * @param page_title The title of the HTML page.
 */

void HTML_header(String& a_string, const char* page_title) {
    a_string += "<!DOCTYPE html> <html>\n";
    a_string += "<head><meta name=\"viewport\" content=\"width=device-width,";
    a_string += " initial-scale=1.0, user-scalable=no\">\n<title> ";
    a_string += page_title;
    a_string += "</title>\n";
    a_string += "<style>html { font-family: Helvetica; display: inline-block;";
    a_string += " margin: 0px auto; text-align: center;}\n";
    a_string += "body{margin-top: 50px;} h1 {color: #4444AA;margin: 50px auto 30px;}\n";
    a_string += "p {font-size: 24px;color: #222222;margin-bottom: 10px;}\n";
    a_string += "</style>\n";
    a_string += "<script>\n";
    a_string += "function updateIMU() {\n";
    a_string += "  fetch('/imu')\n";
    a_string += "    .then(response => response.json())\n";
    a_string += "    .then(data => {\n";
    a_string += "      document.getElementById('pitch').innerText = data.pitch + ' degrees';\n";
    a_string += "      document.getElementById('roll').innerText = data.roll + ' degrees';\n";
    a_string += "      document.getElementById('yaw').innerText = data.yaw + ' degrees';\n";
    a_string += "    });\n";
    a_string += "}\n";
    a_string += "setInterval(updateIMU, 100);\n";
    a_string += "</script>\n";
    a_string += "</head>\n";
}


/**
 * @brief Sets up the WiFi access point for the Balance Bot.
 */
void setup_wifi() {
    Serial.begin(115200);
    delay(100);
    while (!Serial) { }
    delay(1000);

    Serial << "Setting up WiFi access point...";
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Balance_Bot", "password123");
    Serial << "done." << endl;
}


/**
 * @brief Handles the HTTP request for IMU data.
 */
void handle_IMU() {
    String imu_data = "{";
    imu_data += "\"pitch\":" + String(imuAngles[1], 2) + ",";
    imu_data += "\"roll\":" + String(imuAngles[2], 2) + ",";
    imu_data += "\"yaw\":" + String(imuAngles[0], 2) + "}";
    server.send(200, "application/json", imu_data);
}


/**
 * @brief Handles the HTTP request for the document root.
 */
void handle_DocumentRoot() {
    Serial << "HTTP request from client #" << server.client() << endl;

    String a_str;
    HTML_header(a_str, "Balance Bot Web Server");
    a_str += "<body>\n<div id=\"webpage\">\n";
    a_str += "<h1>Balance Bot IMU Angles</h1>\n";
    a_str += "<p><p> Pitch: <span id=\"pitch\">" + String(imuAngles[1], 2) + " degrees</span>\n";
    a_str += "<p> Roll: <span id=\"roll\">" + String(imuAngles[2], 2) + " degrees</span>\n";
    a_str += "<p> Yaw: <span id=\"yaw\">" + String(imuAngles[0], 2) + " degrees</span>\n";
    a_str += "</div>\n</body>\n</html>\n";
    server.send(200, "text/html", a_str);

    
}


/**
 * @brief Task function for the web server.
 *
 * Handles incoming client requests and serves web pages.
 */
void task_webserver(void* p_params) {
    server.on("/", handle_DocumentRoot);
    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found");
    });

    server.begin();
    Serial.println("HTTP server started");

    for (;;) {
        server.handleClient();
        vTaskDelay(500);
    }
}


/**
 * @brief Task function for reading IMU data.
 *
 * Reads data from the MPU6050 IMU and updates the global imuAngles array.
 */
void task_read_imu(void* p_params) {
    Wire.begin();
    mpu.initialize();

    bool dmpReady = false;
    uint8_t mpuIntStatus;
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[64];
    Quaternion q;
    VectorFloat gravity;
    float ypr[3];

    devStatus = mpu.dmpInitialize();

    if (devStatus == 0) {
        mpu.setXGyroOffset(220);
        mpu.setYGyroOffset(76);
        mpu.setZGyroOffset(-85);
        mpu.setZAccelOffset(1788);

        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.setDMPEnabled(true);

        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    }

    for (;;) {
        if (!dmpReady)
            return;

        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

            imuAngles[0] = ypr[0] * 180 / M_PI;
            imuAngles[1] = ypr[1] * 180 / M_PI;
            imuAngles[2] = ypr[2] * 180 / M_PI;

           
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        
        }
        vTaskDelay(1000 / 40);
    }
}
/**
 * @brief Arduino setup function.
 *
 * Initializes WiFi, tasks, and server routes.
 */
void setup() {
    setup_wifi();
    Wire.begin();
    xTaskCreate(task_webserver, "Web Server", 8192, NULL, 2, NULL);
    xTaskCreate(task_read_imu, "Read IMU", 8192, NULL, 3, NULL);
    server.on("/imu", HTTP_GET, handle_IMU);
}

/**
 * @brief Arduino main loop function.
 */
void loop() {
    vTaskDelay(1000);
}
