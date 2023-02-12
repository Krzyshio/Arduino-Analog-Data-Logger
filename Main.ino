#include "LCD.h"
#include "Log.h"
#include "Date.h"
#include "Buttons.h"
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

void setup()
{   
  SoftwareSerial mySerial(2, 3); // RX, TX
    Serial.begin(9600);
    DateInit();
    menuInit();
    StartMenu();
    OpenLogInit();
    mySerial.begin(9600);
}

void loop()

{   
  LogMainLoopHandler();
  delay(100);
}
