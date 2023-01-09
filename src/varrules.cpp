#include <Arduino.h>

#include <VirtualWire.h>
#include <pt.h>

void isArmed(struct pt *pt, bool *armed, int pin)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    if (!digitalRead(pin) && millis() - timestamp > 10)
    {
        timestamp = millis();
    }

    if (millis() - timestamp < 200)
    {
        *armed = true;
    }
    else
    {
        *armed = false;
    }
    PT_END(pt);
}

char *conn_check = "p"; // pass
char *go_check = "g";   // go

void isConnected(struct pt *pt, bool *connected, char *message)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    if (((strcmp(message, conn_check) == 0) || (strcmp(message, go_check) == 0)) && (millis() - timestamp > 10))
    {
        timestamp = millis();
        *connected = true;
    }

    if (millis() - timestamp > 1000)
    {
        *connected = false;
    }

    PT_END(pt);
}

void isGo(struct pt *pt, bool *go, char *message)
{
    static unsigned long timestamp = 0;

    PT_BEGIN(pt);

    if (strcmp(message, go_check) == 0 && (millis() - timestamp > 10))
    {
        timestamp = millis();
        *go = true;
    }

    if (millis() - timestamp > 200)
    {
        *go = false;
    }

    PT_END(pt);
}
