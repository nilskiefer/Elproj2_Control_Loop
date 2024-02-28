#include <Arduino.h>
#include <algorithm>
#include <stdint.h>

enum SensorPins {
    SENSOR1 = A0,
    SENSOR2 = A1,
    SENSOR3 = A2,
    SENSOR4 = A3
};

enum CoilPins {
    COIL1 = D5,
    COIL2 = D8,
    COIL3 = D10,
    COIL4 = D7
};

enum SensorCutOffs {
    CUT_OFF1 = 15,
    CUT_OFF2 = 15,
    CUT_OFF3 = 15,
    CUT_OFF4 = 15
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
    Serial.println(String(analogRead(SENSOR1)) + " " + String(analogRead(SENSOR2)) + " " + String(analogRead(SENSOR3)) + " " + String(analogRead(SENSOR4)));

    while (analogRead(SENSOR1) < 4000 && analogRead(SENSOR2) < 4000 && analogRead(SENSOR3) < 4000 && analogRead(SENSOR4) < 4000) {
        Serial.println(String(analogRead(SENSOR1)) + " " + String(analogRead(SENSOR2)) + " " + String(analogRead(SENSOR3)) + " " + String(analogRead(SENSOR4)));
        // Serial.println("Waiting for sensors connected...");
    }
    Serial.println("Setup done!");
}

uint16_t baseCoilOnDelay = 20; // Base delay in milliseconds
float scalingFactor = 1;       // Determines how much the delay changes, adjust as needed

float minCoilOnDelay = 0;  // Minimum coil on delay in milliseconds
float maxCoilOnDelay = 70; // Maximum coil on delay in milliseconds

int readSensorDelta(int sensorPin) {
    int valSensor = analogRead(sensors[sensorPin]);
    delay(1);
    int currentRead = analogRead(sensors[sensorPin]);
    int delta = valSensor - currentRead;
    return delta;
}
void loop() {
    for (int i = 0; i < NUM_SENSOR_COILS; i++) {
        int sensorDelta = readSensorDelta(i);
        Serial.print("Sensor " + String(i + 1) + " delta: " + String(sensorDelta) + "Sensor reading" + analogRead(sensors[i]) + "\n");
        if (abs(readSensorDelta(i)) > sensorCutOffs[i]) {
            Serial.println("Sensor " + String(i + 1) + " activated");
            digitalWrite(coils[i], HIGH);
            float currentTime = millis();
            while (abs(sensorDelta) > sensorCutOffs[i]) {
                Serial.println("Waiting for sensor " + String(i + 1) + " to deactivate..." + String(analogRead(sensors[i])) + " " + String(sensorDelta));
                sensorDelta = readSensorDelta(i);
                if (millis() - currentTime > maxCoilOnDelay) {
                    break;
                }
                //
            }
            float senseTime = millis() - currentTime;

            // Scale coilOnDelay based on senseTime
            float coilOnDelay = (float)(scalingFactor * senseTime);
            // Enforce limits to keep the delay within a reasonable range

            Serial.println("Sensor " + String(i + 1) + ", Coil " + String(i + 1) + " ON" + ", Delay: " + String(coilOnDelay) + "ms" + ", Time since last activation: " + String(senseTime) + "ms");
            coilOnDelay = min(coilOnDelay, minCoilOnDelay);

            delay(coilOnDelay);
            digitalWrite(coils[i], LOW);
        }
    }
    Serial.println();

    // lapTime = millis() - lastLapTime;
    // Serial.println("Lap cnt: " + String(lapCnt) + "\nLap speed: " + String(lapTime) + "ms\n");
}
