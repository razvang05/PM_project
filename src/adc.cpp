#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "adc.h"


// ---------- ADC ----------
void adc_init() {
  ADMUX = (1 << REFS0); // AVcc ca referință
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // prescaler 64
}

// ---------- Citire ADC ----------
uint16_t read_adc(uint8_t channel) {
    // selectez canalul ADC
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    // aștept finalizarea conversiei
    while (ADCSRA & (1 << ADSC));
    // returnez valoarea ADC
    return ADC;
}