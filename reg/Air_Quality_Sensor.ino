#include"AirQuality.h"
#include"Arduino.h"
AirQuality airqualitysensor;
int Tast = 2;
#define LED 13
const int Sum = 3;
#define Red 5
#define Yellow 6
#define Green 7
int current_quality =-1;

void setup()
{
Serial.begin(9600);
airqualitysensor.init(14);
pinMode(Tast, INPUT_PULLUP);
pinMode(LED, OUTPUT);
pinMode(Sum, OUTPUT);
pinMode(Red, OUTPUT);
pinMode(Yellow, OUTPUT);
pinMode(Green, OUTPUT);


digitalWrite(LED, LOW);
digitalWrite (Sum, LOW);
digitalWrite (Red, LOW);
digitalWrite (Yellow, LOW);
digitalWrite (Green, LOW);

}
void loop()
{
current_quality=airqualitysensor.slope();

if (current_quality >= 0)// if a valid data returned.
{
if (current_quality==0)
{
Serial.println("High pollution! Force signal active");

/* add coder :
AQ = 0 and
- Tast = 1
*/
digitalWrite(Tast, HIGH);
/***************/

digitalWrite(LED, LOW);
digitalWrite (Green, LOW);
digitalWrite (Yellow, LOW);
tone (Sum, 2000);

/* add coder : */
digitalWrite(Tast, LOW);
/***************/

digitalWrite (Red, HIGH);
}
else if (current_quality==1)
{
Serial.println("High pollution!");
digitalWrite(LED, LOW);
digitalWrite(Green, LOW);
digitalWrite(Yellow, LOW);
noTone(Sum);

/* add */
current_quality = 0;

digitalWrite(Red, HIGH);
}
else if (current_quality==2)
{
Serial.println("Low pollution!");
digitalWrite(LED, LOW);
digitalWrite(Green, LOW);
digitalWrite(Red, LOW);
noTone(Sum);
/* add */
current_quality = 0;
digitalWrite(Yellow, HIGH);
}
else if (current_quality ==3)
{
Serial.println("Fresh air");
digitalWrite(LED, LOW);
digitalWrite(Red, LOW);
digitalWrite(Yellow, LOW);
noTone(Sum);
/* add */
current_quality = 0;
digitalWrite(Green, HIGH);
}
}
}

ISR(TIMER1_OVF_vect)
{
if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
{

airqualitysensor.last_vol=airqualitysensor.first_vol;
airqualitysensor.first_vol=analogRead(A0);
airqualitysensor.counter=0;
airqualitysensor.timer_index=1;
PORTB=PORTB^0x20;
}
else
{
airqualitysensor.counter++;
}
}
