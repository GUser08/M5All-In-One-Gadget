#include "DrUltraSonic.h"
#include <Arduino.h>


DrUltraSonic::DrUltraSonic(int echo_pin, int trig_pin)
{
    m_echo_pin = echo_pin;
    m_trig_pin = trig_pin;

    pinMode(m_echo_pin, INPUT);
    pinMode(m_trig_pin, OUTPUT);
}

double DrUltraSonic::measureReturnTime()
{
    double t;
    digitalWrite(m_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin, LOW);

    t = pulseIn(m_echo_pin, HIGH);
    return t;
}
