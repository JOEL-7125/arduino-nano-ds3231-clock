#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const char* daysOfWeek[] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("ERROR: DS3231 not found!");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power!");
    Serial.println("Setting time to computer compile time...");

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println("DS3231 RTC started!");
  Serial.println("--------------------");
}

void loop() {
  DateTime now = rtc.now();

  Serial.print("Time: ");

  if (now.hour() < 10) Serial.print("0");
  Serial.print(now.hour());

  Serial.print(":");

  if (now.minute() < 10) Serial.print("0");
  Serial.print(now.minute());

  Serial.print(":");

  if (now.second() < 10) Serial.print("0");
  Serial.println(now.second());


  Serial.print("Date: ");

  if (now.day() < 10) Serial.print("0");
  Serial.print(now.day());

  Serial.print("/");

  if (now.month() < 10) Serial.print("0");
  Serial.print(now.month());

  Serial.print("/");
  Serial.println(now.year());


  Serial.print("Day: ");
  Serial.println(daysOfWeek[now.dayOfTheWeek()]);


  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");

  Serial.println("--------------------");

  delay(1000);
}