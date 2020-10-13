//
// Created by Abhigya Wangoo on 10/11/20.
//

#include "core/pixel.h"
namespace naivebayes {

    bool Pixel::IsShaded() const {
        return kPixelValue != ' ' && (kPixelValue == '#' || kPixelValue != '+');
    }

    Pixel::Pixel(const char &pixelValue): kPixelValue(pixelValue) {}

    Pixel::Pixel() {
    }

    const char Pixel::getKPixelValue() const {
        return kPixelValue;
    }
}