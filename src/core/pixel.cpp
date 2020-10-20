//
// Created by Abhigya Wangoo on 10/11/20.
//
#include "core/pixel.h"

namespace naivebayes {
    bool Pixel::IsShaded() const {
        return pixel_value_ == '+' || pixel_value_ == '#'; 
    }

    Pixel::Pixel(const char &pixel_value) : pixel_value_(pixel_value) {}

    Pixel::Pixel() : pixel_value_(' ') {
    }

    const char Pixel::get_pixel_value() const {
        return pixel_value_;
    }

    void Pixel::setPixelValue(char pixelValue) {
        pixel_value_ = pixelValue;
    }
}