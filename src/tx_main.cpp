#include <Arduino.h>

#include <VirtualWire.h>
#include <pt.h>

#include <ledrules.cpp>

int led_pin = A4;
int tx_pin = A5;
int button_pin = A3;

bool go = false;
char *data;

static struct pt led_pt;

void send(char *message)
{
    vw_send((uint8_t *)message, strlen(message));
    vw_wait_tx();
}

void setup()
{
    Serial.begin(9600);

    pinMode(button_pin, INPUT_PULLUP);

    PT_INIT(&led_pt);

    vw_set_tx_pin(tx_pin);
    vw_setup(2000); // Bits per sec

    delay(2000);
}

void loop()
{

    if (!digitalRead(button_pin))
    {
        go = true;
        data = "g"; // go
        warningLed(&led_pt, led_pin);
    }
    else
    {
        go = false;
        data = "p"; // pass
        waitingLed(&led_pt, led_pin);
    }

    Serial.print("sent : ");
    Serial.println(data);
    send(data);
}