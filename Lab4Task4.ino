// Arduino code for optocoupler circuit
const int fanPin = 8;  // Digital pin connected to optocoupler LED side

void setup() {
    pinMode(fanPin, OUTPUT);
}

void loop() {
    // Turn on fan for 3 seconds
    digitalWrite(fanPin, HIGH);
    delay(3000);
    
    // Turn off fan for 10 seconds
    digitalWrite(fanPin, LOW);
    delay(10000);
}
