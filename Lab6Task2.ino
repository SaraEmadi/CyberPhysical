// Bare-metal SPI Master on Arduino Uno (ATmega328P)
// SPI config: Fosc/16, MSB first, Mode 3

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit(void) {
  // Set MOSI (PB3), SCK (PB5), SS (PB2) as output; MISO (PB4) as input
  DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2);  // MOSI, SCK, SS output
  DDRB &= ~(1 << PB4);                           // MISO input

  // Keep SS high (no slave selected at start)
  PORTB |= (1 << PB2);

  // SPI Control Register (SPCR):
  // SPE: SPI Enable
  // MSTR: Master mode
  // CPOL=1, CPHA=1 for Mode 3
  // SPR0=1, SPR1=0 => Fosc/16
  SPCR = (1 << SPE)  |  // Enable SPI
         (1 << MSTR) |  // Master mode
         (1 << CPOL) |  // Clock polarity = 1
         (1 << CPHA) |  // Clock phase = 1  (Mode 3)
         (1 << SPR0);   // SPR0=1, SPR1=0 => Fosc/16

  // SPI2X in SPSR = 0 (no double speed), so speed = Fosc/16
  SPSR &= ~(1 << SPI2X);
}

uint8_t SPI_MasterTransfer(uint8_t data) {
  // Load data into SPI Data Register
  SPDR = data;

  // Wait until transmission complete (SPIF flag set)
  while (!(SPSR & (1 << SPIF))) {
    // wait
  }

  // Return received data from slave
  return SPDR;
}

int main(void) {
  uint8_t dataToSend = 0x55;
  uint8_t received;

  SPI_MasterInit();

  // Optional: you can configure an LED on PB0 to debug
  DDRB |= (1 << PB0);

  while (1) {
    // Select slave: pull SS low
    PORTB &= ~(1 << PB2);

    // Transfer one byte
    received = SPI_MasterTransfer(dataToSend);

    // Deselect slave: pull SS high
    PORTB |= (1 << PB2);

    // Optional: toggle LED to show activity
    PORTB ^= (1 << PB0);

    // Toggle data pattern between 0x55 and 0xAA
    if (dataToSend == 0x55) {
      dataToSend = 0xAA;
    } else {
      dataToSend = 0x55;
    }

    _delay_ms(500);
  }
}