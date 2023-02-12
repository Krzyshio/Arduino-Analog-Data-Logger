#include <LiquidCrystal.h>

#define pin_RS    8
#define pin_EN    9
#define pin_d4    4
#define pin_d5    5
#define pin_d6    6
#define pin_d7    7

#define MENU_DELAY 300
#define BLINK_TIMER 50

void menuInit(void);
void StartMenu(void);
extern LiquidCrystal lcd;
