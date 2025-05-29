#ifndef LCD_H
#define LCD_H
#include <stdint.h>

void lcd_init();
void lcd_clear();
void lcd_command(uint8_t cmd);
void lcd_write(uint8_t d);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print(const char* str);
void lcd_write_raw(uint8_t data);
void i2c_start();
void i2c_stop();
void i2c_write(uint8_t data);


#endif