#include <Arduino.h>//importing
//global variables
volatile bool adc_ready=false;
volatile uint16_t adc_value=0;
volatile unsigned long time_sec=0;
//interupt
ISR(TIMER1_COMPA_vect)
{
time_sec++;
adc_ready=true;
}

void setupTimer1()//to initialize in the begining
{
cli();//disables interupts
TCCR1A=0;//reset timer control register A
TCCR1B=0;// rester timer control register b
OCR1A=15624;//when to count 1 sec
TCCR1B|=(1<<WGM12);//ctc clears when reaches 1 second
TCCR1B|=(1<<CS12)|(1<<CS10);//pre scaler to 1024
TIMSK1|=(1<<OCIE1A);//compares if one sec has come
sei();//global interups back on
}

void setup()
{
Serial.begin(115200);//initialize comms at 115200 baud rate 
setupTimer1();//timer start
}

void loop()//main loop
{
if(adc_ready)//compares if true 
{
adc_ready=false;// reset to flase
adc_value=analogRead(A0);//read voltage
Serial.print("TIME: ");
Serial.print(time_sec);
Serial.print(" ADC: ");
Serial.println(adc_value);
}
}
