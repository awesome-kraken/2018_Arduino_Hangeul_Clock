#include <Time.h>
#include <TimeLib.h>
#include <DS1302RTC.h>

#define RST 2
#define DAT 3
#define CLK 4

DS1302RTC RTC(RST, DAT, CLK);

void setup()
{
  Serial.begin(9600);

  setDateTime();

  if ( RTC.haltRTC() ) Serial.println( "The DS1302 is stopped. Please run the SetTime");
  if ( !RTC.writeEN() ) Serial.println( "The DS1302 is write protected. This normal.");
}

void loop()
{
  tmElements_t tm;

  
  if( ! RTC.read(tm) )
  {
    if( tm.Hour == 0 && tm.Minute == 0 )
    {
      Serial.println("자정");
    }
    else if( tm.Hour == 12 && tm.Minute == 0 )
    {
      Serial.println("정오");
    }
    else
    {
      if( tm.Hour < 12 )
      {
        Serial.print("오전 ");

        if( tm.Hour == 0 ) Serial.print( 12 );
        else Serial.print( tm.Hour ); 
      }
      else
      {
        Serial.print("오후 ");

        if( tm.Hour == 12 ) Serial.print( 12 );
        else Serial.print( tm.Hour - 12 );
      }
  
      Serial.print( " : " );
      Serial.print( tm.Minute );
  
      Serial.print( " : " );
      Serial.println( tm.Second );
    }

    delay(1000);
  }
}

void setDateTime() {
time_t t;
tmElements_t tm;
tm.Year = CalendarYrToTm(2018);
tm.Month = 6;
tm.Day = 8;
tm.Hour = 16;
tm.Minute = 33;
tm.Second = 20;
t = makeTime(tm);
if(RTC.set(t) == 0) { // Success
setTime(t);
Serial.print("RTC set to: ");
Serial.println("");
}
else
Serial.println("RTC set failed!");
}
