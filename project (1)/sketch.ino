#include <Arduino.h>
//global variables
volatile bool timer_flag=false;
volatile uint32_t time_sec=0;
volatile uint16_t adc_values[4];
void setupTimer1(){      //to initialize in the begining
cli();//interupts ignored
TCCR1A=0;//reset timer control register a
TCCR1B=0;//reset timer control register b
TCNT1=0;//Timer/Counter
OCR1A=15624;//when to count 1 sec
TCCR1B|=(1<<WGM12);//ctc 
TCCR1B|=(1<<CS12)|(1<<CS10);//prescscaler to 1024
TIMSK1|=(1<<OCIE1A);//compares
sei();//global interupts back on
}
//ADC initilization
void setupADC(){
ADMUX=(1<<REFS0);//reference voltage 5v
ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//ADC channel select and turn on (128)
}
//read one adc channel
uint16_t ADC_Read(uint8_t channel){
 ADMUX=(ADMUX&0xF8)|channel;//Erases the old ADC channel selection
ADCSRA|=(1<<ADSC);//to starts ADC conversion.
while(ADCSRA&(1<<ADSC));//waits until the conversion is complete
return ADC;
}
//TIMER INTERRUPT
ISR(TIMER1_COMPA_vect){
time_sec++;
//4 adc channels
for(uint8_t i=0;i<4;i++){
adc_values[i]=ADC_Read(i);
}
timer_flag=true;//signals main loop new data ready
}
// system initilaization
void setup(){
Serial.begin(115200);//baud set for faster
setupADC();//initilaize adc
setupTimer1();//enables interupts and timer
Serial.println("TIME,ADC1,ADC2,ADC3,ADC4");//csv header
}
//main program
void loop(){
if(timer_flag){
timer_flag=false;//reset flag
Serial.print(time_sec);
Serial.print(",");
for(uint8_t i=0;i<4;i++){
Serial.print(adc_values[i]);
if(i<3)Serial.print(",");//no comma needed after 3rd index
}
Serial.println();
}
}