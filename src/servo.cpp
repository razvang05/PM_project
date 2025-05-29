#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "servo.h"

// ---------- Servo cu Timer1 pe D9 și D10 ----------
void pwm_init_timer1() {
  // setez D9 și D10 ca ieșiri
  DDRB |= (1 << PB1) | (1 << PB2);

  // activez modul non_inverting pentru PWM pe D9 și D10
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  // setez prescaler la 8 si modul Fast PWM
  // cu ICR1 ca valoare de top
  // pentru a avea o frecvență de 50Hz (20ms per ciclu)
  // 50Hz = 20ms, iar pentru un prescaler de 8, ICR1 trebuie să fie 40000
  TCCR1B = (1 << WGM13) | (1 << CS11);
  ICR1 = 40000;
}

void servo_set_angle_timer1(uint8_t channel, uint8_t angle) {
  // durata impulusului pwm pentru un unghi de 0-180 grade
  uint16_t pulse = (angle * 11) + 1000;

  // OC1A este D9 și OC1B este D10 in mod pwm
  // controlez durata semnalului HIGH pe pinul respectiv
  if (channel == 1) OCR1A = pulse; // D9
  else if (channel == 2) OCR1B = pulse; // D10
}

// ---------- Servo manual pe D11 ----------
void setup_servo_d11() {
  DDRB |= (1 << PB3); // D11 output
}

void pulse_servo_d11(uint8_t angle) {
  uint16_t pulse_width_us = (angle * 11) + 1000;

  // setez pinul D11 HIGH pentru a genera un impuls
  PORTB |= (1 << PB3);
  // tin pinul HIGH pentru durata specificată
  for (uint16_t i = 0; i < pulse_width_us / 10; i++)
    _delay_us(10);

  // setez pinul D11 LOW pentru a încheia impulsul
  PORTB &= ~(1 << PB3);
  // așteaptă un impuls la fiecare 20 ms (~50 Hz).
  _delay_ms(20 - (pulse_width_us / 1000));
}