#include "LCD.h"
#include "Buttons.h"
#include "Log.h"
LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

void menuInit()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Log :     SELECT");
    lcd.setCursor(0, 1);
    lcd.print("Config :   RIGHT");
}

void StartMenu()
{
    while (true)
    {

        if (GetButtonsState() == SELECT)
        {
            delay(MENU_DELAY);

            break;
        }

        if (GetButtonsState() == RIGHT)
        {
            delay(MENU_DELAY);
            MenuChoice();
            break;
        }
    }
}

void MenuChoice()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Date&Time:SELECT");
    lcd.setCursor(0, 1);
    lcd.print("Interval:  RIGHT");
    while (true)
    {

        if (GetButtonsState() == SELECT)
        {
            delay(MENU_DELAY);
            TimeSetup();
            break;
        }

        if (GetButtonsState() == RIGHT)
        {

            delay(MENU_DELAY);
            IntervalSetup();
            break;
        }
    }
}

void IntervalSetup()
{
    String intervalTime = "0000000000";
    IntervalSetupPrint(intervalTime);
    int positionInterval = 0;
    while (true)
    {
        IntervalSetupPrint(intervalTime);
        if (GetButtonsState() == LEFT && positionInterval > 0)
        {
            positionInterval--;
            delay(MENU_DELAY);
        }
        if (GetButtonsState() == RIGHT)
        {
            positionInterval++;
            delay(MENU_DELAY);
        }
        if (intervalTime[0] == '5')
            intervalTime[0] = '4';
        if (intervalTime[0] == '4' && intervalTime[1] == '2')
            intervalTime[1] = '1';

        intervalTime = ChoseIntervalTime(positionInterval, intervalTime);
        if (positionInterval < 10)
            animation(positionInterval - 4);
        if (GetButtonsState() == SELECT)
        {
            uint32_t intervalTimeResult = intervalTime.toInt();
            SetIntervalTime = intervalTimeResult;
            delay(MENU_DELAY);
            menuInit();
            StartMenu();
            break;
        }
    }
}

String ChoseIntervalTime(int arg, String IntervalTimeArg)
{
    IntervalSetupPrint(IntervalTimeArg);
    delay(MENU_DELAY);
    if (GetButtonsState() == UP)
    {
        if (IntervalTimeArg[arg] == '9')
            IntervalTimeArg[arg] = '0';
        else
            IntervalTimeArg[arg]++;
    }
    if (GetButtonsState() == DOWN)
    {
        if (IntervalTimeArg[arg] != '0')
            IntervalTimeArg[arg]--;
    }
    return IntervalTimeArg;
}

void IntervalSetupPrint(String arg)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Probe Interval");
    lcd.setCursor(0, 1);
    lcd.print(arg);
    lcd.setCursor(14, 1);
    lcd.print("ms");
}

void TimeSetup()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time :    SELECT");
    lcd.setCursor(0, 1);
    lcd.print("Date :     RIGHT");
    while (true)
    {

        if (GetButtonsState() == SELECT)
        {
            delay(MENU_DELAY);
            PrintTimeScreen(rtc.getDateStr());
            TimeSelect();
            break;
        }

        if (GetButtonsState() == RIGHT)
        {
            delay(MENU_DELAY);
            PrintDateScreen(rtc.getDateStr());
            DataSelect();
            break;
        }
    }
}

void TimeSelect()
{
    String Time_ = rtc.getTimeStr(2);
    int positionTime = 0;
    while (true)
    {
        if (GetButtonsState() == LEFT && positionTime > 0)
        {
            positionTime--;
            delay(MENU_DELAY);
        }
        if (GetButtonsState() == RIGHT  && positionTime < 5)
        {
            positionTime++;
        }
        switch (positionTime)
        {
        case 0:
            Time_ = ChoseTime(0, Time_);
            if (Time_[0] == '3')
                Time_[0] = '2';
            animation(0);
            break;
        case 1:
            Time_ = ChoseTime(1, Time_);
            if (Time_[0] == '2' && int(Time_[1]) > 51)
                Time_[1] = '3';
            animation(1);
            break;
        case 2:
            Time_ = ChoseTime(3, Time_);
            if (Time_[3] == '6')
                Time_[3] = '5';
            animation(3);
            break;
        case 3:
            Time_ = ChoseTime(4, Time_);
            animation(4);
            break;
        case 4:
            Time_ = ChoseTime(6, Time_);
            if (Time_[6] == '6')
                Time_[6] = '5';
            animation(6);
            break;
        case 5:
            Time_ = ChoseTime(7, Time_);

            animation(7);
            break;
        }

        if (GetButtonsState() == SELECT)
        {

            int hour_ = (Time_[0] - 48) * 10 + Time_[1] - 48;
            int min_ = (Time_[3] - 48) * 10 + Time_[4] - 48;
            int sec_ = (Time_[6] - 48) * 10 + Time_[7] - 48;

            Serial.println(hour_);
            rtc.setTime(hour_, min_, sec_);
            delay(MENU_DELAY);
            Serial.println(Time_);
            menuInit();
            StartMenu();
            break;
        }

        Serial.println(positionTime);
    }
}
void animation(int position_)
{
    lcd.setCursor(position_ + 4, 1);
    lcd.print(" ");
    delay(BLINK_TIMER);
}

String ChoseTime(int arg, String TimeArg)
{
    PrintTimeScreen(TimeArg);
    delay(MENU_DELAY);
    if (GetButtonsState() == UP)
    {
        if (TimeArg[arg] == '9')
            TimeArg[arg] = '0';
        else
            TimeArg[arg]++;
    }
    if (GetButtonsState() == DOWN)
    {
        if (TimeArg[arg] != '0')
            TimeArg[arg]--;
    }
    return TimeArg;
}

void PrintTimeScreen(String arg)
{

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Format HH:MM:SS");
    lcd.setCursor(4, 1);
    lcd.print(arg);
}

void DataSelect()
{
    String Data_ = rtc.getDateStr();
    int positionDate = 0;
    while (true)
    {
        if (GetButtonsState() == LEFT && positionDate > 0)
        {
            positionDate--;
            delay(MENU_DELAY);
        }
        if (GetButtonsState() == RIGHT && positionDate< 5)
            positionDate++;

        switch (positionDate)
        {
        case 0:
            Data_ = ChoseDate(0, Data_);
            if (Data_[0] == '4')
                Data_[0] = '3';
            animation(0);
            break;
        case 1:
            Data_ = ChoseDate(1, Data_);
            if (Data_[0] == '3' && int(Data_[1]) > 49)
                Data_[1] = '1';
            animation(1);
            break;
        case 2:
            Data_ = ChoseDate(3, Data_);
            if (Data_[3] == '2')
                Data_[3] = '1';
            animation(3);
            break;
        case 3:
            Data_ = ChoseDate(4, Data_);
            if (Data_[3] == '1' && int(Data_[4]) > 49)
                Data_[4] = '2';
            animation(4);
            break;
        case 4:
            Data_ = ChoseDate(8, Data_);
            animation(8);

            break;
        case 5:
            Data_ = ChoseDate(9, Data_);
            animation(9);
            break;
        }

        if (GetButtonsState() == SELECT)
        {

            int day_ = (Data_[0] - 48) * 10 + Data_[1] - 48;
            int month_ = (Data_[3] - 48) * 10 + Data_[4] - 48;
            int year_ = 2000 + (Data_[8] - 48) * 10 + Data_[9] - 48;

            rtc.setDate(day_, month_, year_);
            delay(MENU_DELAY);
            menuInit();
            StartMenu();
            break;
        }
    }
}
String ChoseDate(int arg, String DateArg)
{
    PrintDateScreen(DateArg);
    delay(MENU_DELAY);
    if (GetButtonsState() == UP)
    {
        if (DateArg[arg] == '9')
            DateArg[arg] = '0';
        else
            DateArg[arg]++;
    }
    if (GetButtonsState() == DOWN)
    {
        if (DateArg[arg] != '0')
            DateArg[arg]--;
    }
    return DateArg;
}

void PrintDateScreen(String arg)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Format DD:MM:YYYY");
    lcd.setCursor(4, 1);
    lcd.print(arg);
}
