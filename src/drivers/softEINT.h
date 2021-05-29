/*
* softEINT: class external interrupt driver 
* SdtElectronics 2021.5
*/

#pragma once

#include <array>
#include <gpiod.hpp>

class seint{
  public:
    enum evType{RISING_EDGE = 1, FALLING_EDGE, BOTH_EDGE};
    using glReq = gpiod::line_request;
    using biasType = decltype(glReq::FLAG_OPEN_DRAIN);

    seint(gpiod::line& intPin, evType ev, biasType bias);
    evType waitEv(const std::chrono::nanoseconds& timeout = std::chrono::hours(1));

  private:
    using reqType = decltype(glReq::EVENT_BOTH_EDGES);
    gpiod::line& _intPin;

    static constexpr std::array<reqType, 4> evMap{
        reqType::DIRECTION_AS_IS,       //Just a placeholder
        reqType::EVENT_RISING_EDGE, 
        reqType::EVENT_FALLING_EDGE, 
        reqType::EVENT_BOTH_EDGES
    };
};