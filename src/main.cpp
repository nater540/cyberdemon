#define ARDUINO_NRF52832_FEATHER

#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 11
#define NUM_LEDS 2
CRGB leds[NUM_LEDS];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  leds[0] = CRGB::Red;
  FastLED.show();

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);

  leds[0] = CRGB::Black;
  FastLED.show();

  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}
