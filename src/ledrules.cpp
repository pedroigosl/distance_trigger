#include <Arduino.h>
#include <pt.h>

void resetLed(int led)
{
    digitalWrite(led, LOW);
}

void idleLed(struct pt *pt, int led)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    digitalWrite(led, HIGH);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 2000);
    digitalWrite(led, LOW);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 1000);
    digitalWrite(led, HIGH);

    PT_END(pt);
}

void waitingLed(struct pt *pt, int led)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    digitalWrite(led, HIGH);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    digitalWrite(led, LOW);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    digitalWrite(led, HIGH);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    digitalWrite(led, LOW);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 1200);

    PT_END(pt);
}

void armedLed(struct pt *pt, int led)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 150);
    digitalWrite(led, HIGH);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 150);
    digitalWrite(led, LOW);

    PT_END(pt);
}

void warningLed(struct pt *pt, int led, int counter = 2000)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 50);
    digitalWrite(led, HIGH);
    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 50);
    digitalWrite(led, LOW);

    PT_END(pt);
}

void ignitingLed(struct pt *pt, int led)
{

    PT_BEGIN(pt);

    digitalWrite(led, HIGH);

    PT_END(pt);
}