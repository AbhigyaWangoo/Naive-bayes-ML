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
        char pixel_value_;

    public:
        /**
         * Constructor for initializing pixel with value
         *
         * @param pixel_value to initialize pixel_value_ with
         */
        Pixel(const char &pixel_value);
        
        /**
         * Simple empty constructor
         */
        Pixel();
        
        /**
         * Gets Pixel's value
         * 
         * @return pixel_value_ 
         */
        const char get_pixel_value() const;

        /**
         * Determines whether the pixel's shade based on the value
         *
         * @return whether the pixel is shaded or not
         */
        bool IsShaded() const;

        void setPixelValue(char pixelValue);
    };
}

#endif //NAIVE_BAYES_PIXEL_H
