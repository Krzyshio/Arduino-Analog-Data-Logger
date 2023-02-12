#include "Date.h"
DS3231 rtc(SDA, SCL);

void DateInit(void)
{
    rtc.begin();
}
