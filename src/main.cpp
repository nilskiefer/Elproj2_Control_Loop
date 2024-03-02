#include <Arduino.h>

#include <stdint.h>
enum SensorPins {
    SENSOR1 = A0,
    SENSOR2 = A1,
    SENSOR3 = A2,
    SENSOR4 = A3
};

enum CoilPins {
    COIL1 = 4,
    COIL2 = 5,
    COIL3 = 6,
    COIL4 = 7
};

enum SensorCutOffs {
    CUT_OFF1 = 500,
    CUT_OFF2 = 500,
    CUT_OFF3 = 500,
    CUT_OFF4 = 500
};

const int NUM_SENSOR_COILS = 4;
const int sensors[NUM_SENSOR_COILS] = {SENSOR1, SENSOR2, SENSOR3, SENSOR4};
const int coils[NUM_SENSOR_COILS] = {COIL1, COIL2, COIL3, COIL4};
const int sensorCutOffs[NUM_SENSOR_COILS] = {CUT_OFF1, CUT_OFF2, CUT_OFF3, CUT_OFF4};

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < NUM_SENSOR_COILS; i++) {
        pinMode(sensors[i], INPUT);
        digitalWrite(sensors[i], LOW); // Virtual Pulldown
        pinMode(coils[i], OUTPUT);
        digitalWrite(coils[i], LOW); // Initial state LOW
    }
    while (analogRead(SENSOR1) < CUT_OFF1 || analogRead(SENSOR2) < CUT_OFF2 || analogRead(SENSOR3) < CUT_OFF3 || analogRead(SENSOR4) < CUT_OFF4) {
        // Serial.println("Waiting for sensors connected...");
        Serial.println("Sensor 1: " + String(analogRead(SENSOR1)) + ", Sensor 2: " + String(analogRead(SENSOR2)) + ", Sensor 3: " + String(analogRead(SENSOR3)) + ", Sensor 4: " + String(analogRead(SENSOR4)));
        delay(50);
    }
    Serial.println("Setup done!");
}

uint16_t baseCoilOnDelay = 20; // Base delay in milliseconds
float scalingFactor = 1;       // Determines how much the delay changes, adjust as needed

float minCoilOnDelay = 0;  // Minimum coil on delay in milliseconds
float maxCoilOnDelay = 70; // Maximum coil on delay in milliseconds

void loop() {
    for (int i = 0; i < NUM_SENSOR_COILS; i++) {
        int valSensor = analogRead(sensors[i]);

        if (valSensor < sensorCutOffs[i]) {

            float currentTime = millis();
            while (analogRead(sensors[i]) < sensorCutOffs[i]) {
                //
                if (millis() - currentTime > maxCoilOnDelay) {
                    break;
                }
            }
            float senseTime = millis() - currentTime;

            // Scale coilOnDelay based on senseTime
            float coilOnDelay = (float)(scalingFactor * senseTime);
            // Enforce limits to keep the delay within a reasonable range

            Serial.println("Sensor " + String(i + 1) + ", Coil " + String(i + 1) + " ON" + ", Delay: " + String(coilOnDelay) + "ms" + ", Time since last activation: " + String(senseTime) + "ms");
            coilOnDelay = max(coilOnDelay, minCoilOnDelay);
            coilOnDelay = min(coilOnDelay, maxCoilOnDelay);
            digitalWrite(coils[i], HIGH);
            delay(coilOnDelay);
            digitalWrite(coils[i], LOW);
        }
    }

    // lapTime = millis() - lastLapTime;
    // Serial.println("Lap cnt: " + String(lapCnt) + "\nLap speed: " + String(lapTime) + "ms\n");
}
