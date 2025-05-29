#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <string.h>
#include<Arduino.h>
#include "bluetooth.h"
#include "servo.h"
#include "lcd.h"
#include "buzzer.h"
#include "adc.h"
#include "parola.h"


void setup_all() {
  init();
  uart_init();
  pwm_init_timer1();
  setup_servo_d11();
  adc_init();

  // LED pe D7, buzzer pe D3
  DDRD |= (1 << PD7) | (1 << PD3);
  // Senzor flacără pe D8 (input)
  DDRB &= ~(1 << PB0);
  // pull-up pe D8
  PORTB |= (1 << PB0);
  TWSR = 0;
  TWBR = 32;

  DDRD &= ~((1 << PD5) | (1 << PD4));
  // pull-up pe D5 și D4
  PORTD |= (1 << PD5) | (1 << PD4);

  // D2 input (microfon)
  DDRD &= ~(1 << PD2);
  // D6 input (fotorezistor)
  DDRD &= ~(1 << PD6);
  // D12 output (LED alb)
  DDRB |= (1 << PB4);
}


void control_led() {
    bool sunet_detectat = PIND & (1 << PD2);
    bool lumina_detectata = PIND & (1 << PD6);

    // Condiție: dacă e întuneric și se detectează sunet, aprindem LED-ul
    if (lumina_detectata && !sunet_detectat) {
      PORTB |= (1 << PB4); // Aprinde LED alb pe D12
      _delay_ms(1000); // Așteaptă 1 secundă
    } else {
      PORTB &= ~(1 << PB4); // Stinge LED-ul
    }
}

int main(void) {
  setup_all();

  lcd_init();
  lcd_set_cursor(0, 0);
  lcd_print("Smart Home");

  while (1) {
    if (is_bluetooth_connected()) {
          // Bluetooth activ: accept comenzi din aplicație
          control_bluetooth();
    } else {
      ParolaMorse();
      // Senzor fotoelectric pe A0
      uint16_t fotoelectric = read_adc(0);
      if (fotoelectric < 500) {
        
        pulse_servo_d11(40); // D11
        
      } else {
        // Barieră jos
        pulse_servo_d11(90);
      }


      // Umiditate sol pe A3
      uint16_t umiditate = read_adc(3);
      if (umiditate < 1000) {
        PORTD |= (1 << PD7);
        generate_tone(1000, 300);
        _delay_ms(2000);
        PORTD &= ~(1 << PD7);
      }

      // Senzor flacără pe D8
      if (!(PINB & (1 << PB0))) {
        PORTD |= (1 << PD7);
        generate_tone(1500, 300);
        _delay_ms(2000);
        PORTD &= ~(1 << PD7);
      }

      uint16_t ploaie = read_adc(2);
      if(ploaie < 100) {
        servo_set_angle_timer1(2,10);
        _delay_ms(100);
    
      } else {
        servo_set_angle_timer1(2,0);
        _delay_ms(100);
      }
      control_led();
      
    }
  
  }

}
