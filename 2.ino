volatile bool myled=false;
ISR (INT10_vect)
{

myled=!myled;
digitalWrite(13,myled);
}

void setup() {

// put your setup code here, to run once:mb
pinMode(13,OUTPUT);
pinMode(2,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(2),INT10_vect,FALLING);
}
void loop() {
// put your main code here, to run repeatedly:
}