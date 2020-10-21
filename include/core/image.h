#include <string>
#include <map>
#include <vector>
#include <fstream>

#include "pixel.h"

namespace naivebayes {

    // Global member variables
    static const std::vector<char> kClassifications = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    
    /**
     * Class holding representation of Image
     */
    class Image {
    public:
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
        void AddRow(std::vector<Pixel> &row);

        /**
         * Adds Pixel to current image_pixels_ spot
         *
         * @param row to add
         */
        void SetPixel(const Pixel &pixel, const size_t x, const size_t y);
        
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