// Arduino code for gradual fan speed control
const int fanPin = 9;  // PWM pin for fan control (via transistor base/gate)

void setup() {
    pinMode(fanPin, OUTPUT);
}

void loop() {
    // Wait 10 seconds with fan off (15s total - 5s on = 10s off)
    analogWrite(fanPin, 0);
    delay(10000);
    
    // Turn on fan for 5 seconds with gradually increasing speed
    // Speed increases every second (5 steps)
    for(int speed = 51; speed <= 255; speed += 51) {
        analogWrite(fanPin, speed);
        delay(1000);  // 1 second at each speed level
    }
}
