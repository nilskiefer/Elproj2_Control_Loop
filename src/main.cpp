#include <Arduino.h>

enum SensorPins {
    SENSOR1 = A0,
    SENSOR2 = A1,
    SENSOR3 = A2,
    SENSOR4 = 5
};

enum CoilPins {
    COIL1 = D6,
    COIL2 = D7,
    COIL3 = D9,
    COIL4 = D8
};

enum SensorCutOffs {
    CUT_OFF1 = 4000,
    CUT_OFF2 = 3500,
    CUT_OFF3 = 3500,
    CUT_OFF4 = 4000
};

const int NUM_SENSOR_COILS = 4;
const int sensors[NUM_SENSOR_COILS] = {SENSOR1, SENSOR2, SENSOR3, SENSOR4};
const int coils[NUM_SENSOR_COILS] = {COIL1, COIL2, COIL3, COIL4};
const int sensorCutOffs[NUM_SENSOR_COILS] = {CUT_OFF1, CUT_OFF2, CUT_OFF3, CUT_OFF4};

void setup() {
    Serial.begin(115200);
    Serial.println("BRUH");
    delay(5000);
    Serial.println("BRUH");

    for (int i = 0; i < NUM_SENSOR_COILS; i++) {
        pinMode(sensors[i], INPUT);
        digitalWrite(sensors[i], LOW); // Virtual Pulldown
        pinMode(coils[i], OUTPUT);
        digitalWrite(coils[i], LOW); // Initial state LOW
    }

    Serial.println("Setup done!");
}

int coilOnDelay = 80;

void loop() {
    for (int i = 0; i < NUM_SENSOR_COILS; i++) {
        int valSensor = analogRead(sensors[i]);
        Serial.print("Sensor " + String(i + 1) + ": " + String(valSensor));

        if (valSensor < sensorCutOffs[i]) {
            Serial.println("Sensor " + String(i + 1) + ", Coil " + String(i + 1) + " ON");
            digitalWrite(coils[i], HIGH);
            delay(coilOnDelay);
            Serial.println("Coil " + String(i + 1) + " OFF");
            digitalWrite(coils[i], LOW);
            break; // Assuming only one sensor activates at a time
        }
    }
    Serial.println("");
}
