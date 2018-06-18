//최종본


// hanguel clock
#include <Time.h>
#include <TimeLib.h>
#include <DS1302RTC.h>
#include <Adafruit_NeoPixel.h>

tmElements_t tm;


#define RST 2
#define DAT 3
#define CLK 4
#define PIN 6

DS1302RTC RTC( RST, DAT, CLK );
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(36, PIN, NEO_GRB + NEO_KHZ800);

// binary value
int binary_apm[] = { 3, 2049 }; // 오전 오후
int binary_mid[] = { 96, 192 }; // 자정 정오
long binary_hour[] = { 0, 131584, 131328, 131076, 131080, 151552, 155648, 131120, 131264, 229376, 132096, 132608, 132100 };
long binary_minute[] =
{
    0, 4352, 4608, 5120, 6144, 135168, 69632, 36864, 20480, 12288,
    4097, 4353, 4609, 5121, 6145, 135169, 69633, 36865, 20481, 12289,
    4113, 4369, 4625, 5137, 6161, 135185, 69649, 36881, 20497, 12305,
    4105, 4361, 4617, 5129, 6153, 135177, 69641, 36873, 20489, 12297,
    4101, 4357, 4613, 5125, 6149, 135173, 69637, 36869, 20485, 12293,
    7099, 4355, 4611, 5123, 6147, 135171, 69635, 36867, 20482, 12291
};

// function
void tossTime(int hour, int minute, int mid, int apm );
void printLed(long arr_hour, long arr_min);
void rtc();


void setup() {
    Serial.begin(9600);
    pixels.begin();
    rtc();
}

void loop() {

    RTC.read(tm);
    
    if( tm.Second == 0 ) rtc();
    delay(100);
}

void rtc(){

    int hour = 0, mid = 0, apm = 0;
    if( !RTC.read(tm) )
    {
        if( tm.Hour == 0 && tm.Minute == 0 ) mid = 1;
        else if( tm.Hour == 12 && tm.Minute == 0 ) mid = 2;
        else
        {
            if( tm.Hour < 12 )
            {
                apm = 0;
                if( tm.Hour == 0 ) hour = 12;
                else hour = tm.Hour;
            }
            else
            {
                apm = 1;
                if( tm.Hour == 12 ) hour = 12;
                else hour = tm.Hour - 12;
            }
        }
    }

    tossTime( hour, tm.Minute, mid, apm );
} 

void tossTime(int hour, int minute, int mid, int apm) {
    Serial.print( (apm == 0)?("오전\ "):("오후 ") );
    Serial.print( hour );
    Serial.print( " : " );
    Serial.println( minute );
    if(mid) printLed( binary_mid[mid - 1], 0 );
    else printLed( binary_hour[hour] | binary_apm[apm], binary_minute[minute] );
}

void printLed(long arr_hour, long arr_min) {
    for( int i = 0; i < 18; i++ )
    {
        if( arr_hour % 2 ) pixels.setPixelColor( i, pixels.Color(255, 255, 255) );
        else pixels.setPixelColor( i, pixels.Color( 0, 0, 0 ) );

        if( arr_min % 2 ) pixels.setPixelColor( i + 18, pixels.Color( 255, 255, 255 ) );
        else pixels.setPixelColor( i + 18, pixels.Color( 0, 0, 0 ) );

        arr_hour >>= 1;
        arr_min >>= 1;
    }

    pixels.show();
}
