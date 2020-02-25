#include <Arduino.h>
#include <unity.h>

#include <button.h>

Cyberdemon::Button globalButt(5);

void test_button_enable() {
  globalButt.enable(true);
  TEST_ASSERT_EQUAL(true, globalButt.isEnabled());
}

void setup() {
  delay(500);

  UNITY_BEGIN();
  RUN_TEST(test_button_enable);
  UNITY_END();
}

void loop() {

}
