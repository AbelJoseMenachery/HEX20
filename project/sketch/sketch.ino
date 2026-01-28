
#include <Arduino.h>
// initialize import arduino features
volatile unsigned long seconds = 0;
//variable to count seconds (global)
//to run when timer1 reaches 15624 i.e 1second
ISR(timer1) //interupt
{
  seconds++;
}
//to run when the arduino starts
void setup()
{
  Serial.begin(9600);//baud rate 9600 bits per second
  cli(); //to clear all interupts while seting up timer
  //reset timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624; //timer1's compare value 16mhz/1024
  TCCR1B |=(1 << WGM12); //ctc mode resets when timer reaches compare value
  TCCR1B |=(1 << CS12)|(1 << CS10); //time prescaler to 1024 (counts 1 in 15624 clicks)
  TIMSK1 |=(1 << OCIE1A);//to call the interupt when it reaches 1 second
  sei(); //interupt enabled back
}
//to run after setup
void loop()
{
  static unsigned long last = 0;//stores last printed values for comparing
  if (seconds != last);//check if the value was updated
  {
  Serial.println("tick");
}}
