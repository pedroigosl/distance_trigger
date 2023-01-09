#include <Arduino.h>

#include <VirtualWire.h>
#include <pt.h>

#include <ledrules.cpp>
#include <buzzerrules.cpp>
#include <varrules.cpp>

byte message[VW_MAX_MESSAGE_LEN];
byte msgLength = VW_MAX_MESSAGE_LEN;

// int builtin_led_pin = LED_BUILTIN;

int led_pin = A4;
int buzzer_pin = A5;
int rx_pin = 12;
int relay_pin = 2;
int arm_pin = 3;

int state = 0;
int new_state = 0;
unsigned long timing = 0;

// Signals whether there is a fuse connected
bool armed = false;
// Signals whether there is transmitter signal
bool connected = false;
// Signals whether transmitted signal received
bool go = false;

char *input;

// PROTOTHREAD POINTERS DECLARATION
// External led
static struct pt led_pt;
static struct pt buzzer_pt;
static struct pt armed_pt;
static struct pt connected_pt;
static struct pt go_pt;

void resetAll(int led, int buzzer)
{
    resetLed(led);
    resetBuzzer(buzzer);
}

void stateReport()
{
    Serial.print("\t   STATE ");
    Serial.println(state);
    Serial.print("Connected: ");
    Serial.print(connected);
    Serial.println();
    Serial.print("Armed: ");
    Serial.print(armed);
    Serial.println();
    Serial.print("Go: ");
    Serial.print(go);
    Serial.println();
    Serial.println("-----------------------------");
}

int nextState(int default_to)
{
    if (default_to != -1)
    {
        return default_to;
    }
    if (!connected && !armed && !go)
    {
        return 0;
    }
    if (connected && !armed && !go)
    {
        return 1;
    }
    if (connected && armed && !go)
    {
        return 2;
    }
    if (connected && armed && go)
    {
        return 3;
    }
    return default_to; //-1;
}

void stateUpdate(int default_to = -1)
{
    new_state = nextState(default_to);
    if (new_state != state)
    {
        resetAll(led_pin, buzzer_pin);
        state = new_state;
        stateReport();
    }
}

void setup()
{
    Serial.begin(9600);

    Serial.println("### Detonator rx connected ###");

    pinMode(led_pin, OUTPUT);
    pinMode(buzzer_pin, OUTPUT);
    pinMode(arm_pin, INPUT_PULLUP);
    pinMode(relay_pin, OUTPUT);

    // Rx setup
    vw_set_rx_pin(rx_pin);
    vw_setup(2000); // Bits per second
    vw_rx_start();

    // PROTOTHREAD POINTERS INSTANTIATION
    PT_INIT(&led_pt);
    PT_INIT(&buzzer_pt);
    PT_INIT(&armed_pt);
    PT_INIT(&connected_pt);

    timing = millis();
    state = 0;
    new_state = -1;

    input = NULL;

    delay(2000);
    stateReport();
}

void loop()
{
    uint8_t message[VW_MAX_MESSAGE_LEN];
    uint8_t msgLength = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(message, &msgLength)) // Non-blocking
    {
        input = (char *)message;
    }
    else
    {
        input = "d"; // disconnected
    }

    isConnected(&connected_pt, &connected, input);
    isArmed(&armed_pt, &armed, arm_pin);
    isGo(&go_pt, &go, input);

    switch (state)
    {
    case 0: // default state. unarmed, disconnected
        timing = millis();
        idleLed(&led_pt, led_pin);
        idleBuzzer(&buzzer_pt, buzzer_pin);
        stateUpdate();
        break;
    case 1: // Unarmed, connected, no go
        timing = millis();
        waitingLed(&led_pt, led_pin);
        waitingBuzzer(&buzzer_pt, buzzer_pin);
        stateUpdate();
        break;
    case 2: // Armed, connected, no go
        timing = millis();
        armedLed(&led_pt, led_pin);
        armedBuzzer(&buzzer_pt, buzzer_pin);
        stateUpdate();
        break;

    case 3: // Armed, connected, go signal received, warning
        warningLed(&led_pt, led_pin);
        warningBuzzer(&buzzer_pt, buzzer_pin);

        if (millis() - timing > 2500)
        {
            timing = millis();
            resetAll(led_pin, buzzer_pin);
            stateUpdate(4);
        }
        break;
    case 4: // Armed, connected, go signal received, igniting
        ignitingLed(&led_pt, led_pin);
        ignitingBuzzer(&buzzer_pt, buzzer_pin);
        digitalWrite(relay_pin, HIGH);
        Serial.println("IGNITING!!");
        go = false;

        if (millis() - timing > 2500)
        {
            timing = millis();
            digitalWrite(relay_pin, LOW);
            stateUpdate();
        }
        break;
    default: // Any undefined combination
        timing = millis();
        warningLed(&led_pt, led_pin);
        warningBuzzer(&buzzer_pt, buzzer_pin);
        stateUpdate();
        break;
    }
}