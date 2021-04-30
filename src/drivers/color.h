
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

class color{
    public:
        color(const std::string& path);
        enum color_set {
            GREEN,
            BLUE,
            RED
        };
        struct RGB{
            unsigned int red;
            unsigned int blue;
            unsigned int green;
        };
        RGB getData();
        void flipPattern();
        color_set decideColor(const color::RGB& C);
        ~color();
        
        
    private:
        bool pattern = 1; //default mode(=1): TASK1
                                //mode 2(=0): stop trigger
        const int redRaw;
        const int blueRaw;
        const int greenRaw;
        
};