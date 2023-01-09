#include <Arduino.h>
#include <pt.h>

void resetBuzzer(int buzzer)
{
    noTone(buzzer);
}

void idleBuzzer(struct pt *pt, int buzzer)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    tone(buzzer, 1500);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    noTone(buzzer);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 14900);

    PT_END(pt);
}

void waitingBuzzer(struct pt *pt, int buzzer)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    tone(buzzer, 1500);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    noTone(buzzer);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    tone(buzzer, 1500);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    noTone(buzzer);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 9700);

    PT_END(pt);
}

void armedBuzzer(struct pt *pt, int buzzer)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    tone(buzzer, 1000);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 200);
    noTone(buzzer);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 200);
    tone(buzzer, 1500);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 200);
    noTone(buzzer);

    PT_END(pt);
}

void warningBuzzer(struct pt *pt, int buzzer)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    tone(buzzer, 1500);

    timestamp = millis();
    PT_WAIT_UNTIL(pt, millis() - timestamp > 150);

    noTone(buzzer);

    PT_END(pt);
}

void ignitingBuzzer(struct pt *pt, int buzzer)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    tone(buzzer, 1500);

    PT_END(pt);
}