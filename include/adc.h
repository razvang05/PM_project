#ifndef ADC_H
#define ADC_H
#include <stdint.h>

void adc_init();
uint16_t read_adc(uint8_t channel);

#endif // ADC_H