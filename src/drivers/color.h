
// Driver of Color recognizer
// By Bill

#pragma once

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdexcept>
#include <array>
#include <charconv>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

using std::literals::string_literals::operator ""s;

class color{
    public:
        color(const std::string& path, int upperThre, int lowerThre);
        enum color_set {
            GREEN,
            BLUE,
            RED
        };
        struct RGB{
            int red;
            int blue;
            int green;
        };
        RGB getData();
        void flipPattern();
        bool getPattern();
        color_set decideColor(const color::RGB& C);
        void enableInt(int upperThre, int lowerThre, size_t period);
        void disableInt();
        ~color();
        
        
    private:
        bool pattern = 1; //default mode(=1): TASK1
                                //mode 2(=0): stop trigger
        const int redRaw;
        const int blueRaw;
        const int greenRaw;
        const int upperThreshold;
        const int lowerThreshold;
        const int enable;
        const int marginPeriod;
};