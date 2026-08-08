# LED Matrix Scrolling Clock

A 32x8 LED matrix clock built on an Arduino Nano, showing time, day, date, and temperature in a continuously animated sequence, powered by a DS3231 RTC.

## Features

- Live time display (`HH:MM`), updates every minute
- Scrolling day of week and full date
- Temperature reading (with decimal precision) pulled directly from the DS3231's internal sensor
- Animated transitions between screens (scroll, fade, mesh effects) via MD_Parola
- Adjustable display brightness

## Hardware

| Component            | Notes                                  |
|-----------------------|-----------------------------------------|
| Arduino Nano           | ATmega328P                             |
| 4x 8x8 LED matrix (MAX7219) | Chained together for a 32x8 display |
| DS3231 RTC module (e.g. HW-084) | I2C real-time clock with onboard temperature sensor |

## Wiring

**LED Matrix (hardware SPI)**

| Matrix Pin | Nano Pin |
|------------|----------|
| DIN        | D11 (MOSI) |
| CLK        | D13 (SCK)  |
| CS         | D10        |
| VCC        | 5V         |
| GND        | GND        |

**DS3231 RTC (I2C)**

| RTC Pin | Nano Pin |
|---------|----------|
| SDA     | A4       |
| SCL     | A5       |
| VCC     | 5V       |
| GND     | GND      |

## Libraries

Install via Arduino IDE Library Manager:

- [RTClib](https://github.com/adafruit/RTClib) (Adafruit)
- [MD_Parola](https://github.com/MajicDesigns/MD_Parola)
- [MD_MAX72xx](https://github.com/MajicDesigns/MD_MAX72XX)
- Wire (bundled with Arduino IDE)
- SPI (bundled with Arduino IDE)

## Setup

1. Wire the hardware as described above.
2. Install the libraries listed.
3. Open the sketch in Arduino IDE, select **Board: Arduino Nano** and the correct processor/bootloader variant.
4. Upload. On first boot, if the RTC has lost power, it auto-sets itself to your computer's current date/time at compile time.

## Customization

**Brightness** — edit this line at the top of the sketch:

```cpp
#define BRIGHTNESS 7
```

Valid range is **0–15** (hardware limit of the MAX7219's intensity register), where `0` is dimmest and `15` is maximum.

**Animation speed** — adjust `SPEED` (lower = faster scrolling) and `HOLD_PAUSE` (how long the temperature screen holds before scrolling away).

## Troubleshooting

- **Sketch too big / exceeds flash**: Arduino Nano has 32KB of flash. If you add features, you may need to trim Serial debug output or update your AVR Boards package (enables link-time optimization, often saves several hundred bytes).
- **`DS3231 NOT FOUND!`**: check I2C wiring (SDA/SCL) and that the RTC module has power.
- **Degree symbol not displaying**: some font builds don't include glyph 176 — a custom character may be needed as a fallback.

## License

MIT — see [LICENSE](LICENSE).
