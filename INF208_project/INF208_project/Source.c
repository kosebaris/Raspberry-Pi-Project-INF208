#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define TRUE 1

#define TRIG 4
#define ECHO 5
#define LedPin 0

void setup() {
    wiringPiSetup();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LedPin, OUTPUT);

    //TRIG pin must start LOW
    digitalWrite(TRIG, LOW);
    delay(30);
}

int getCM() {
    //Send trig pulse
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    //Wait for echo start
    while (digitalRead(ECHO) == LOW);

    //Wait for echo end
    long startTime = micros();
    while (digitalRead(ECHO) == HIGH);
    long travelTime = micros() - startTime;

    //Get distance in cm
    int distance = travelTime / 58;

    return distance;
}

int main(void) {
    setup();

    while (TRUE) {
        delay(300);
        printf("Distance: %dcm\n", getCM());
        if (getCM() > 20)
            digitalWrite(LedPin, LOW);
        else {
            digitalWrite(LedPin, HIGH);
            delay(10000);
        }

    }

    return 0;
}

