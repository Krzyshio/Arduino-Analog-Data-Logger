#include "Log.h"
#include "LCD.h"

uint32_t SetIntervalTime = 0;
uint32_t timediff;
uint32_t ts;
void OpenLogInit(void)
{
    lcd.clear();
    lcd.print("  Logger Active");
    if (SetIntervalTime == 0)
        SetIntervalTime = DEFAULT_INTERVAL;
    ts = millis();
}

void LogMainLoopHandler(void)
{
    
    uint32_t actual_ms = millis();
    if (actual_ms - ts >= SetIntervalTime)
    {
       ts = actual_ms;
       Serial.print(rtc.getTimeStr());
       Serial.print(" ");
       Serial.print(rtc.getDateStr());
       Serial.print(";");
       Serial.print(analogRead(1));
       Serial.print(";");
       Serial.print(analogRead(2));
       Serial.print(";");
       Serial.print(analogRead(3));
       Serial.print(";");
       Serial.print(analogRead(6));
       Serial.print(";");
       Serial.print(analogRead(7));
       Serial.print(";");
       Serial.println();
    }
}
