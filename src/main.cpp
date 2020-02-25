#include "cyberdemon.h"
#include <Adafruit_NeoPixel.h>

#define DATA_PIN 30
#define NUM_LEDS 6

Adafruit_NeoPixel pixels(NUM_LEDS, DATA_PIN, NEO_GRB);

unsigned long keyPrevMillis = 0;
const unsigned long keySampleIntervalMs = 25;
byte longKeyPressCountMax = 80;    // 80 * 25 = 2000 ms
byte longKeyPressCount = 0;
byte prevKeyState = HIGH;         // button is active low
// const byte keyPin = 5;            // button is connected to pin 2 and GND

#define KEY_PIN 16

// called when button is kept pressed for less than 2 seconds
void shortKeyPress() {
  Serial.println("short");
}
// called when button is kept pressed for more than 2 seconds
void longKeyPress() {
  Serial.println("long");
}
// called when key goes from not pressed to pressed
void keyPress() {
  Serial.println("key press");
  longKeyPressCount = 0;
}

// called when key goes from pressed to not pressed
void keyRelease() {
  Serial.println("key release");
  if (longKeyPressCount >= longKeyPressCountMax) {
    longKeyPress();
  }
  else {
    shortKeyPress();
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.println("Initializing Cyberdemon...");

  pinMode(KEY_PIN, INPUT_PULLUP);
  pixels.begin();
}

void loop() {
  if (millis() - keyPrevMillis >= keySampleIntervalMs) {
    keyPrevMillis = millis();
    byte currKeyState = digitalRead(KEY_PIN);
    if ((prevKeyState == HIGH) && (currKeyState == LOW)) {
        keyPress();
    }
    else if ((prevKeyState == LOW) && (currKeyState == HIGH)) {
        keyRelease();
    }
    else if (currKeyState == LOW) {
        longKeyPressCount++;
    }
    prevKeyState = currKeyState;
  }

  pixels.setPixelColor(0, pixels.Color(252, 132, 3));
  pixels.setPixelColor(1, pixels.Color(252, 44, 3));
  pixels.setPixelColor(2, pixels.Color(252, 44, 3));
  pixels.setPixelColor(3, pixels.Color(252, 44, 3));
  pixels.setPixelColor(4, pixels.Color(252, 44, 3));
  pixels.setPixelColor(5, pixels.Color(252, 44, 3));
  pixels.show();
}
