#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"


#define LCD_ADDR 0x27

// ---------- I2C LCD ----------
void i2c_start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

//---------- I2C Stop ----------
void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}
//---------- I2C Write ----------
void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

//---------- I2C Read ----------
void lcd_write_raw(uint8_t data) {
    i2c_start();
    i2c_write(LCD_ADDR << 1);
    i2c_write(data);
    i2c_stop();
    _delay_ms(1);
}

//---------- LCD Command ----------
void lcd_command(uint8_t cmd) {
    uint8_t h = cmd & 0xF0;
    uint8_t l = (cmd << 4) & 0xF0;
    lcd_write_raw(h | 0x0C);
    lcd_write_raw(h | 0x08);
    lcd_write_raw(l | 0x0C);
    lcd_write_raw(l | 0x08);
}

//---------- LCD Write ----------
void lcd_write(uint8_t d) {
    uint8_t h = d & 0xF0;
    uint8_t l = (d << 4) & 0xF0;
    lcd_write_raw(h | 0x0D);
    lcd_write_raw(h | 0x09);
    lcd_write_raw(l | 0x0D);
    lcd_write_raw(l | 0x09);
}

//---------- LCD Clear ----------
void lcd_clear() {
    lcd_command(0x01);
    _delay_ms(2);
}

//---------- LCD Set Cursor ----------
void lcd_set_cursor(uint8_t col, uint8_t row) {
  lcd_command(0x80 | (row * 0x40 + col));
}

//---------- LCD Print ----------
void lcd_print(const char* str) {
    while (*str) lcd_write(*str++);
}

//---------- LCD Init ----------
void lcd_init() {
    _delay_ms(50);
    lcd_command(0x33); 
    lcd_command(0x32);
    lcd_command(0x28); 
    lcd_command(0x0C);
    lcd_command(0x06); 
    lcd_command(0x01);
    _delay_ms(5);
}