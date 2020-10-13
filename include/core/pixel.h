//
// Created by Abhigya Wangoo on 10/11/20.
//

#ifndef NAIVE_BAYES_PIXEL_H
#define NAIVE_BAYES_PIXEL_H

namespace naivebayes {
    class Pixel {
    private:
        const char kPixelValue = ' ';

    public:
        Pixel(const char &pixelValue);

        bool IsShaded() const;

        const char getKPixelValue() const;

        Pixel();
    };
}

#endif //NAIVE_BAYES_PIXEL_H
