#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect) {
    // Toggle LED on PB0
    PORTB ^= (1 << PORTB5);
}

void setup() {
    // --- LED setup ---
    DDRB |= (1 << DDB0);     // PB0 as output
    PORTB &= ~(1 << PORTB5); // LED initially OFF

    // --- Button setup (INT0 = PD2) ---
    DDRD &= ~(1 << DDD2);    // PD2 as input
    PORTD |= (1 << PORTD2);  // Enable pull-up resistor

    // --- Interrupt setup ---
    EICRA |= (1 << ISC01);   // Falling edge trigger (ISC01=1, ISC00=0)
    EICRA &= ~(1 << ISC00);

    EIFR |= (1 << INTF0);    // Clear any pending INT0 flag
    EIMSK |= (1 << INT0);    // Enable INT0 interrupt

    sei();                   // Enable global interrupts
}

void loop() {
    // Do nothing; LED toggles in ISR
}
