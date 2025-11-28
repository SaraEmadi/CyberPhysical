// Bare metal code for ATmega328P
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set PD6 (Pin 6 on Arduino) as output
    DDRD |= (1 << PD6);
    
    while(1) {
        // Turn on LED for 3 seconds
        PORTD |= (1 << PD6);
        _delay_ms(3000);
        
        // Turn off LED for 1 second
        PORTD &= ~(1 << PD6);
        _delay_ms(1000);
    }
    
    return 0;
}
