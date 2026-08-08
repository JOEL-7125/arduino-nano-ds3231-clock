#include <Wire.h>
#include <RTClib.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CS_PIN 10

MD_Parola display(
  HARDWARE_TYPE,
  CS_PIN,
  MAX_DEVICES
);

RTC_DS3231 rtc;

#define SPEED 70
#define NO_PAUSE 0
#define HOLD_PAUSE 1700
#define BRIGHTNESS 2

const char* days[] = {
  "SUNDAY",
  "MONDAY",
  "TUESDAY",
  "WEDNESDAY",
  "THURSDAY",
  "FRIDAY",
  "SATURDAY"
};

const char* months[] = {
  "JANUARY",
  "FEBRUARY",
  "MARCH",
  "APRIL",
  "MAY",
  "JUNE",
  "JULY",
  "AUGUST",
  "SEPTEMBER",
  "OCTOBER",
  "NOVEMBER",
  "DECEMBER"
};

char message[40];

int lastMinute = -1;

int animationStep = 0;

bool animationRunning = false;

void setup()
{
  if (!rtc.begin())
  {
    while (1);
  }

  if (rtc.lostPower())
  {
    rtc.adjust(
      DateTime(F(__DATE__), F(__TIME__))
    );
  }

  display.begin();

  display.setIntensity(BRIGHTNESS);

  display.displayClear();

  DateTime now = rtc.now();

  lastMinute = now.minute();

  showTimeStatic();
}

void loop()
{
  if (display.displayAnimate())
  {
    if (animationRunning)
    {
      nextAnimation();
    }
  }

  DateTime now = rtc.now();

  if (now.minute() != lastMinute)
  {
    lastMinute = now.minute();

    animationRunning = true;

    animationStep = 0;

    showTimeOut();
  }
}

void nextAnimation()
{
  animationStep++;

  if (animationStep == 1)
  {
    showDay();
  }

  else if (animationStep == 2)
  {
    showDate();
  }

  else if (animationStep == 3)
  {
    showTemperature();
  }

  else if (animationStep == 4)
  {
    animationRunning = false;

    showTimeReturn();
  }
}


void showTimeStatic()
{
  DateTime now = rtc.now();

  sprintf(
    message,
    "%02d:%02d",
    now.hour(),
    now.minute()
  );

  display.displayText(
    message,
    PA_CENTER,
    0,
    0,
    PA_PRINT,
    PA_NO_EFFECT
  );
}


void showTimeOut()
{
  DateTime now = rtc.now();

  sprintf(
    message,
    "%02d:%02d",
    now.hour(),
    now.minute()
  );

  display.displayText(
    message,
    PA_CENTER,
    SPEED,
    NO_PAUSE,

    PA_NO_EFFECT,

    PA_SCROLL_UP
  );
}


void showDay()
{
  DateTime now = rtc.now();

  strcpy(
    message,
    days[now.dayOfTheWeek()]
  );

  display.displayText(
    message,
    PA_CENTER,
    SPEED,
    NO_PAUSE,

    PA_SCROLL_LEFT,

    PA_SCROLL_LEFT
  );
}


void showDate()
{
  DateTime now = rtc.now();

  sprintf(
    message,
    "%02d %s %04d",
    now.day(),
    months[now.month() - 1],
    now.year()
  );

  display.displayText(
    message,
    PA_CENTER,
    SPEED,
    NO_PAUSE,

    PA_SCROLL_LEFT,

    PA_SCROLL_LEFT
  );
}


void showTemperature()
{
  float temperature = rtc.getTemperature();

  char tempStr[8];
  dtostrf(temperature, 4, 1, tempStr);

  char *p = tempStr;
  while (*p == ' ')
  {
    p++;
  }

  sprintf(
    message,
    "%s%cC",
    p,
    (char)176
  );

  display.displayText(
    message,
    PA_CENTER,
    SPEED,
    HOLD_PAUSE,

    PA_MESH,

    PA_SCROLL_UP
  );
}


void showTimeReturn()
{
  DateTime now = rtc.now();

  sprintf(
    message,
    "%02d:%02d",
    now.hour(),
    now.minute()
  );

  display.displayText(
    message,
    PA_CENTER,
    SPEED,
    0,

    PA_FADE,

    PA_NO_EFFECT
  );
}
