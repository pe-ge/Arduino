#include <Arduino.h>
#include <TM1637Display.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define DISP_CLK 2
#define DISP_DIO 3

#define BMP_SCK 13
#define BMP_SDC 12
#define BMP_SDA 11
#define BMP_CSB 10

TM1637Display display(DISP_CLK, DISP_DIO);
Adafruit_BMP280 bme(BMP_CSB);

void setup() {
  display.setBrightness(0x0f);
  bme.begin();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  int altitude = bme.readAltitude(1013.25);
  display.showNumberDec(altitude, false);

  delay(1000);
  int temperature = bme.readTemperature();
  display.showNumberDec(temperature, false);
}
