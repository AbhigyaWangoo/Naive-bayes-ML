//
// Created by Abhigya Wangoo on 10/11/20.
//

#ifndef NAIVE_BAYES_PIXEL_H
#define NAIVE_BAYES_PIXEL_H

namespace naivebayes {
    /**
     * Pixel class represents a single pixel in an image
     */
    class Pixel {
    private:
        const char kPixelValue = ' ';

    public:
        /**
         * Constructor for initializing pixel with value
         *
         * @param pixelValue to initialize kPixelValue with
         */
        Pixel(const char &pixelValue);

        Pixel();

        const char getKPixelValue() const;

        /**
         * Determines whether the pixel's shade based on the value
         *
         * @return whether the pixel is shaded or not
         */
        bool IsShaded() const;
    };
}

#endif //NAIVE_BAYES_PIXEL_H
