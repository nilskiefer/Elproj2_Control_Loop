#include <Arduino.h>

// OPA
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = 5;
int coil1 = D6;
int coil2 = D7;
int coil3 = D8;
int coil4 = D9;
uint32_t val = 0;
void setup() {

    Serial.begin(115200);
    Serial.println("BRUH");
    delay(5000);
    Serial.println("BRUH");
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    pinMode(sensor4, INPUT);

    // Virtual Pulldown
    digitalWrite(sensor1, LOW);
    digitalWrite(sensor2, LOW);
    digitalWrite(sensor3, LOW);
    digitalWrite(sensor4, LOW);

    pinMode(coil1, OUTPUT);
    pinMode(coil2, OUTPUT);
    pinMode(coil3, OUTPUT);
    pinMode(coil4, OUTPUT);

    // Virtual Pulldown
    digitalWrite(coil1, LOW);
    digitalWrite(coil2, LOW);
    digitalWrite(coil3, LOW);
    digitalWrite(coil4, LOW);

    Serial.println("Setup done!");
}

int coilOnDelay = 50;

int sensor1CutOff = 3500;
int sensor2CutOff = 3500;
int sensor3CutOff = 3500;
int sensor4CutOff = 3500;
void loop() {
    int valSensor1 = analogRead(sensor1);
    int valSensor2 = analogRead(sensor2);
    int valSensor3 = analogRead(sensor3);
    int valSensor4 = analogRead(sensor4);
    Serial.println("Sensor 1: " + String(valSensor1) + " Sensor 2: " + String(valSensor2) + " Sensor 3: " + String(valSensor3) + " Sensor 4: " + String(valSensor4));
    if (valSensor1 > sensor1CutOff) {
        Serial.println("Sensor 1, Coil 1 ON");
        digitalWrite(coil1, HIGH);
        delay(coilOnDelay);
        Serial.println("Coil 1 OFF");
        digitalWrite(coil1, LOW);
    }
    if (valSensor2 > sensor2CutOff) {
        Serial.println("Sensor 2, Coil 2 ON");
        digitalWrite(coil2, HIGH);
        delay(coilOnDelay);
        Serial.println("Coil 2 OFF");
        digitalWrite(coil2, LOW);
    }
    if (valSensor3 > sensor3CutOff) {
        Serial.println("Sensor 3, Coil 3 ON");
        digitalWrite(coil3, HIGH);
        delay(coilOnDelay);
        Serial.println("Coil 3 OFF");
        digitalWrite(coil3, LOW);
    }
    if (valSensor4 > sensor4CutOff) {
        Serial.println("Sensor 4, Coil 4 ON");
        digitalWrite(coil4, HIGH);
        delay(coilOnDelay);
        Serial.println("Coil 4 OFF");
        digitalWrite(coil4, LOW);
    }
}
