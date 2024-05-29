#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include <dht.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

dht dht22;

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

void setup() {
  Serial.begin(9600);
  delay(250);
  display.begin(i2c_Address, true);
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10, 10, SH110X_WHITE);
  display.display();
  delay(2000);
}

void loop() {
  int readData = dht22.read22(7);
  float t = dht22.temperature;
  float h = dht22.humidity;
  display.display();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  //display.print("Tem:");
  display.print(t, 1);
  display.setTextSize(1);
  display.print(" o ");
  display.setTextSize(3);
  display.println("C");
  display.setTextSize(1);
  display.println();
  //display.print("Hum:");
  display.setTextSize(3);
  display.print(h, 1);
  display.println(" %");
  analogWrite(11, 255);
  delay(800);
  for(int i = 255; i > 0; i--)
  {
    analogWrite(11, i);
    delay(5);
  }
  analogWrite(11, 0);
  delay(200);
}
