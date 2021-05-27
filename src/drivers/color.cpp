#include <string>
#include "color.h"

color::color(const std::string& path, int upperThre = 1500, int loweThre = 100):
    redRaw(open((path + "in_intensity_red_raw").c_str(), O_RDONLY)),
    blueRaw(open((path + "in_intensity_blue_raw").c_str(), O_RDONLY)),
    greenRaw(open((path + "in_intensity_green_raw").c_str(), O_RDONLY)),
    upperThreshold(open((path + "events/in_intensity_clear_thresh_rising_value").c_str(), O_RDWR)),
    lowerThreshold(open((path + "events/in_intensity_clear_thresh_falling_value").c_str(), O_RDWR)),
    enable(open((path + "events/in_intensity_clear_thresh_either_en").c_str(), O_RDWR)),
    marginPeriod(open((path + "events/in_intensity_clear_thresh_either_en").c_str(), O_RDWR)){
    if(redRaw < 0 || blueRaw < 0 || greenRaw < 0 || upperThreshold < 0 || lowerThreshold < 0 || enable < 0 || marginPeriod < 0){
        throw std::runtime_error("Error when opening TCS34725"s + strerror(errno));
    }
}

color::RGB color::getData(){
    char raw_R[5], raw_G[5], raw_B[5];
    read(redRaw, raw_R, 5);
    lseek(redRaw, 0, SEEK_SET);
    read(blueRaw, raw_B, 5);
    lseek(blueRaw, 0, SEEK_SET);
    read(greenRaw, raw_G, 5);
    lseek(greenRaw, 0, SEEK_SET);
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

bool color::getPattern(){
    return pattern;
}

void color::enableInt(int upperThre, int lowerThre, size_t period){
    std::array<char, 3> str1;
    std::array<char, 3> str2;
    std::array<char, 3> str3;
    char* strBeg1 = str1.data();
    char* strBeg2 = str2.data();
    char* strBeg3 = str3.data();
    auto [ptr1, e1] = std::to_chars(strBeg1, strBeg1 + str1.size(), upperThre);
    auto [ptr2, e2] = std::to_chars(strBeg2, strBeg2 + str2.size(), lowerThre);
    auto [ptr3, e3] = std::to_chars(strBeg3, strBeg3 + str3.size(), period);
    if (write(upperThreshold, strBeg1, ptr1 - strBeg1) < 0){
        throw std::runtime_error("Error when writing upper threshold"s + strerror(errno));
    };
    if (write(lowerThreshold, strBeg2, ptr2 - strBeg2) < 0){
        throw std::runtime_error("Error when writing lower threshold"s + strerror(errno));
    };
    if (write(marginPeriod, strBeg3, ptr3 - strBeg3) < 0){
        throw std::runtime_error("Error when writing margin period"s + strerror(errno));
    };
    if (write(enable, "1", 2) < 0){
        throw std::runtime_error("Error when enabling TCS34725 Interrupt"s + strerror(errno));
    };
}

void color::disableInt(){
    if (write(enable, "0", 2) < 0){
        throw std::runtime_error("Error when disabling TCS34725 Interrupt"s + strerror(errno));
    }
}

color::~color(){
    close(redRaw);
    close(greenRaw);
    close(blueRaw);
    close(upperThreshold);
    close(lowerThreshold);
    close(enable);
    close(marginPeriod);
}

color::color_set color::decideColor(const color::RGB& C){
    if(C.red == std::max({C.red, C.blue, C.green})){
        return RED;
        // 2 stands for detection of RED
    }else if(C.blue == std::max({C.red, C.blue, C.green})){
        return BLUE;
        // 1 stands for detection of BLUE
    }else if(C.green == std::max({C.red, C.blue, C.green})){
        return GREEN;
        // 0 stands for detection of GREEN 
    }
}