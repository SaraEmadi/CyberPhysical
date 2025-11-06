volatile bool myled=false;
# include <PinChangeInterrupt.h>

ISR (mytoggle)

{
myled=!myled;
digitalWrite(13,myled);
}
void setup() {
  // put your setup code here, to run once:mb
  pinMode(13,OUTPUT);
  pinMode(8,INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(8),mytoggle,FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:

}

