#include "softEINT.h"

seint::seint(gpiod::line& intPin, evType ev = BOTH_EDGE, biasType bias = 0): 
    _intPin(intPin){
    _intPin.request({"", evMap[ev], bias});
}

seint::evType seint::waitEv(const std::chrono::nanoseconds& timeout){
    while(1){
        auto event = _intPin.event_wait(timeout);
        if(event){
            return static_cast<evType>(_intPin.event_read().event_type);
        }
    }
}