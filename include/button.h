#pragma once

#include <stdint.h>
#include <functional>

namespace Cyberdemon {
  using ButtonEventFunction = std::function<void()>;

  /**
   *
   *
   */
  class Button {
    public:

      /**
       * Constructor.
       * @param pin Button pin.
       */
      Button(uint8_t pin);

      //! This is not the destructor you're looking for; move along, move along...
      virtual ~Button() {};

      /**
       * One-time button setup (registers pin, etc)
       * @return *this
       */
      Button& setup();

      /**
       * Enable / Disable button.
       * @param shouldEnable Whether or not to enable the button.
       * @return *this
       */
      Button& enable(const bool shouldEnable = true);

      /**
       * Sets the polling update interval in ms.
       * @param updateInterval Update interval to set (in ms)
       * @return *this
       */
      Button& setUpdateInterval(uint32_t updateInterval);

      /**
       * Sets the on push handler.
       * @param fn Button event function.
       * @return *this
       */
      Button& setOnPushed(ButtonEventFunction fn);

      /**
       * Sets the on release handler.
       * @param fn Button event function.
       * @return *this
       */
      Button& setOnReleased(ButtonEventFunction fn);

      /**
       * Sets the on click handler.
       * @param fn Button event function.
       * @return *this
       */
      Button& setOnClicked(ButtonEventFunction fn);

      /**
       * Sets the on double click handler.
       * @param fn Button event function.
       * @return *this
       */
      Button& setOnDoubleClicked(ButtonEventFunction fn);

      /**
       * Runs the update logic for this button.
       * @param currentTime Current time in ms.
       */
      void update(uint32_t currentTime);

      /**
       * Whether or not the button is enabled.
       * @return Returns true if the button is enabled, false otherwise.
       */
      const bool isEnabled() const;

    protected:

      /**
       * @protected
       * Whether or not the button is currently pushed.
       * @return Returns true if the button is pushed, false otherwise.
       */
      const bool isPushed();

      /**
       * @protected
       * Whether or not the button is currently released.
       * @return Returns true if the button is released, false otherwise.
       */
      const bool isReleased();

      /**
       * @protected
       * Whether or not the button is currently clicked.
       * @param currentTime Current time in ms.
       * @return Returns true if the button is clicked, false otherwise.
       */
      const bool isClicked(const uint32_t currentTime);

      /**
       * @protected
       * Whether or not the button is currently clicked.
       * @param currentTime Current time in ms.
       * @param minPushTime Minimum push time in ms.
       * @return Returns true if the button is clicked, false otherwise.
       */
      const bool isClicked(const uint32_t currentTime, const uint32_t minPushTime);

      /**
       * @protected
       * Whether or not the button is currently clicked.
       * @param currentTime Current time in ms.
       * @param minPushTime Minimum push time in ms.
       * @param minReleaseTime Minimum release time in ms.
       * @return Returns true if the button is clicked, false otherwise.
       */
      const bool isClicked(const uint32_t currentTime, const uint32_t minPushTime, const uint32_t minReleaseTime);

      /**
       * @protected
       * Whether or not the button is currently double clicked.
       * @param currentTime Current time in ms.
       * @return Returns true if the button is double clicked, false otherwise.
       */
      const bool isDoubleClicked(const uint32_t currentTime);

      /**
       * @protected
       * Whether or not the button is currently double clicked.
       * @param currentTime Current time in ms.
       * @param minPushTime Minimum push time in ms.
       * @return Returns true if the button is double clicked, false otherwise.
       */
      const bool isDoubleClicked(const uint32_t currentTime, const uint32_t minPushTime);

      /**
       * @protected
       * Whether or not the button is currently double clicked.
       * @param currentTime Current time in ms.
       * @param minPushTime Minimum push time in ms.
       * @param minReleaseTime Minimum release time in ms.
       * @return Returns true if the button is double clicked, false otherwise.
       */
      const bool isDoubleClicked(const uint32_t currentTime, const uint32_t minPushTime, const uint32_t minReleaseTime);

      /**
       * @protected
       * Whether or not the button is currently double clicked.
       * @param currentTime Current time in ms.
       * @param minPushTime Minimum push time in ms.
       * @param minReleaseTime Minimum release time in ms.
       * @param timeSpan Time between clicks to be considered a double click.
       * @return Returns true if the button is double clicked, false otherwise.
       */
      const bool isDoubleClicked(const uint32_t currentTime, const uint32_t minPushTime, const uint32_t minReleaseTime, const uint32_t timeSpan);

      /**
       * @protected
       * Whether or not the button is currently being held down.
       * @param currentTime Current time in ms.
       * @return Returns true if the button is being held down, false otherwise.
       */
      const bool isHolding(const uint32_t currentTime);

      /**
       * @protected
       * Whether or not the button is currently being held down.
       * @param currentTime Current time in ms.
       * @param interval How long the button must be held for.
       * @return Returns true if the button is being held down, false otherwise.
       */
      const bool isHolding(const uint32_t currentTime, const uint32_t interval);

      /**
       * @protected
       * Internal handler for button pushes.
       */
      void handlePush(const uint32_t currentTime);

      /**
       * @protected
       * Internal handler for button releases.
       */
      void handleRelease(const uint32_t currentTime);

    protected:
      ButtonEventFunction onPushedCB        = nullptr;
      ButtonEventFunction onReleasedCB      = nullptr;
      ButtonEventFunction onHoldingCB       = nullptr;
      ButtonEventFunction onClickedCB       = nullptr;
      ButtonEventFunction onDoubleClickedCB = nullptr;

      bool isSetupFlag    = false;
      bool isEnabledFlag  = false;
      bool isPushedFlag   = false;
      bool isReleasedFlag = false;
      bool isHoldingFlag  = false;

      uint8_t buttonPin;

      uint16_t currentClicks = 0;

      uint32_t pushTime              = 0;
      uint32_t releaseTime           = 0;
      uint32_t prevPushTime          = 0;
      uint32_t prevReleaseTime       = 0;
      uint32_t holdTime              = 0;
      uint32_t updateTime            = 0;
      uint32_t updateInterval        = 25;

      uint32_t defaultMinPushTime    = 40;
      uint32_t defaultMinReleaseTime = 40;
      uint32_t defaultTimeSpan       = 500;
      uint32_t defaultHoldInterval   = 500;
  };
}
