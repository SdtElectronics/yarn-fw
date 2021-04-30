#include <string>
#include "color.h"

color::color(const std::string& path):
    redRaw(open((path + "in_intensity_red_raw").c_str(), O_WRONLY)),
    blueRaw(open((path + "in_intensity_blue_raw").c_str(), O_WRONLY)),
    greenRaw(open((path + "in_intensity_green_raw").c_str(), O_WRONLY)){
    if(redRaw < 0 || blueRaw < 0 || greenRaw < 0){
        throw std::runtime_error(strerror(errno));
    }
}

color::RGB color::getData(){
    char raw_R[4], raw_G[4], raw_B[4];
    read(redRaw, raw_R, 4);
    read(blueRaw, raw_B, 4);
    read(greenRaw, raw_G, 4);
    color::RGB colors{
        .red = atoi(raw_R),
        .blue = atoi(raw_B),
        .green = atoi(raw_G)
    };
    return colors;
}

void color::flipPattern(){
    pattern = ~pattern;
}

color::~color(){
    close(redRaw);
    close(greenRaw);
    close(blueRaw);
}

color::color_set color::decideColor(const color::RGB& C){
    if(C.red == std::max(C.red, C.blue, C.green)){
        return RED;
        // 2 stands for detection of RED
    }else if(C.blue == std::max(C.red, C.blue, C.green)){
        return BLUE;
        // 1 stands for detection of BLUE
    }else if(C.green == std::max(C.red, C.blue, C.green)){
        return GREEN;
        // 0 stands for detection of GREEN 
    }
}