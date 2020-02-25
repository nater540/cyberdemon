#include "button.h"
#include "cyberdemon.h"

namespace Cyberdemon {
  Button::Button(uint8_t pin)
  : buttonPin(pin) {
    setup();
  }

  Button& Button::setup() {
    if (!this->isSetupFlag) {
      pinMode(this->buttonPin, INPUT);
    }

    this->isSetupFlag = true;
    return *this;
  }

  Button& Button::enable(const bool shouldEnable) {
    this->isEnabledFlag = shouldEnable;
    return *this;
  }

  Button& Button::setUpdateInterval(uint32_t updateInterval) {
    this->updateInterval = updateInterval;
    return *this;
  }

  Button& Button::setOnPushed(ButtonEventFunction fn) {
    this->onPushedCB = fn;
    return *this;
  }

  Button& Button::setOnReleased(ButtonEventFunction fn) {
    this->onReleasedCB = fn;
    return *this;
  }

  Button& Button::setOnClicked(ButtonEventFunction fn) {
    this->onClickedCB = fn;
    return *this;
  }

  Button& Button::setOnDoubleClicked(ButtonEventFunction fn) {
    this->onDoubleClickedCB = fn;
    return *this;
  }

  void Button::update(uint32_t currentTime) {
    if (!this->isEnabledFlag || !this->isSetupFlag) {
      return;
    }

    if (currentTime - this->updateTime >= this->updateInterval) {
      this->updateTime = currentTime;

      // Grab the current button state
      if (digitalRead(this->buttonPin) == 0x1) {
        handlePush(currentTime);
      }
      else {
        handleRelease(currentTime);
      }

      // Handle pushes
      if (this->isPushed() && this->onPushedCB != nullptr) {
        this->onPushedCB();
      }

      if (this->isReleased() && this->onReleasedCB != nullptr) {
        this->onReleasedCB();
      }

      if (this->isClicked(currentTime) && this->onClickedCB != nullptr) {
        this->onClickedCB();
      }

      if (this->isDoubleClicked(currentTime) && this->onDoubleClickedCB != nullptr) {
        this->onDoubleClickedCB();
      }

      if (this->isHolding(currentTime) && this->onHoldingCB != nullptr) {
        this->onHoldingCB();
      }
    }
  }

  const bool Button::isEnabled() const {
    return this->isEnabledFlag;
  }

  const bool Button::isPushed() {
    if (this->isPushedFlag) {
      this->isPushedFlag = false;
      return true;
    }

    return false;
  }

  const bool Button::isReleased() {
    if (this->isReleasedFlag && (this->pushTime < this->releaseTime)) {
      this->isReleasedFlag = false;
      return true;
    }

    return false;
  }

  const bool Button::isClicked(const uint32_t currentTime) {
    return isClicked(currentTime, this->defaultMinPushTime);
  }

  const bool Button::isClicked(const uint32_t currentTime, const uint32_t minPushTime) {
    return isClicked(currentTime, minPushTime, this->defaultMinReleaseTime);
  }

  const bool Button::isClicked(const uint32_t currentTime, const uint32_t minPushTime, const uint32_t minReleaseTime) {
    bool minTime        = currentTime - this->pushTime    >= minPushTime;
    bool releaseTimeout = currentTime - this->releaseTime >= minReleaseTime;

    if (!this->isHoldingFlag && minTime && releaseTimeout && this->isReleased()) {
      this->currentClicks++;
      return true;
    }

    return false;
  }

  const bool Button::isDoubleClicked(const uint32_t currentTime) {
    return isDoubleClicked(currentTime, this->defaultMinReleaseTime);
  }

  const bool Button::isDoubleClicked(const uint32_t currentTime, const uint32_t minPushTime) {
    return isDoubleClicked(currentTime, minPushTime, this->defaultMinReleaseTime);
  }

  const bool Button::isDoubleClicked(const uint32_t currentTime, const uint32_t minPushTime, const uint32_t minReleaseTime) {
    return isDoubleClicked(currentTime, minPushTime, minReleaseTime, this->defaultTimeSpan);
  }

  const bool Button::isDoubleClicked(const uint32_t currentTime, const uint32_t minPushTime, const uint32_t minReleaseTime, const uint32_t timeSpan) {
    bool hasBeenClicked = this->prevReleaseTime - this->prevPushTime    >= minPushTime;
    bool inTimeSpan     = currentTime           - this->prevPushTime    <= timeSpan;
    bool releaseTimeout = currentTime           - this->prevReleaseTime >= minReleaseTime;

    if (hasBeenClicked && inTimeSpan && releaseTimeout && isClicked(currentTime, minPushTime)) {
      this->pushTime = 0;
      return true;
    }

    return false;
  }

  const bool Button::isHolding(const uint32_t currentTime) {
    return isHolding(currentTime, this->defaultHoldInterval);
  }

  const bool Button::isHolding(const uint32_t currentTime, const uint32_t interval) {
    if (this->isPushedFlag && (currentTime - this->holdTime >= interval)) {
      this->holdTime      = currentTime;
      this->isHoldingFlag = true;
      return true;
    }

    return false;
  }

  void Button::handlePush(const uint32_t currentTime) {
    if (!this->isPushedFlag) {
      this->isPushedFlag    = true;
      this->prevPushTime    = this->pushTime;
      this->prevReleaseTime = this->releaseTime;

      this->pushTime      = currentTime;
      this->holdTime      = currentTime;
      this->isHoldingFlag = false;
    }
  }

  void Button::handleRelease(const uint32_t currentTime) {
    if (this->isPushedFlag) {
      this->isPushedFlag   = false;
      this->isReleasedFlag = true;
      this->releaseTime    = currentTime;
    }
  }
}
