#include <string>
#include <map>
#include <vector>

#include "pixel.h"

namespace naivebayes {

    // Global member variables
    static const std::vector<char> kClassifications = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    static const char kBlank = ' ';
    static const char kBlack = '#';
    static const char kGrey = '+';

    /**
     * Class holding representation of Image
     */
    class Image {
    public: 
        /**
         * Empty constructor for Image
         */
        Image();
        
        /**
         * Getter for assigned_class
         * 
         * @return assigned_class 
         */
        const char &get_assigned_class() const;

        /**
         * Getter for kImagePixels
         * 
         * @return image pixel values 
         */
        const std::vector<std::vector<Pixel>> &get_image_pixels() const;

        /**
         * Adds row of Pixels to current image_pixels_
         *
         * @param row to add
         */
        void AddPixel(std::vector<Pixel> &row);
        
        /**
         * Setter for assigned_class
         * 
         * @param assignedClass to set with 
         */
        void set_assigned_class(char assignedClass);

        /**
         * clears entire image
         */
        void ClearImage();

    private:
        std::vector<std::vector<Pixel>> image_pixels_;
        char assigned_class_;
    };

}  // namespace naivebayes