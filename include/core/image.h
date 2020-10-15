#include <string>
#include <map>
#include <vector>

#include "pixel.h"

namespace naivebayes {

    static const std::vector<char> kClassifications = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    static const char kBlank = ' ';
    static const char kBlack = '#';
    static const char kGrey = '+';

    /**
     * Class holding representation of Image
     */
    class Image {
    public: //todo javadocs
        Image();

        const char &get_assigned_class() const;

        const std::vector<std::vector<Pixel>> &getKImagePixels() const;

        /**
         * Adds row of Pixels to current image_pixels_
         *
         * @param row to add
         */
        void AddPixel(std::vector<Pixel> &row);
        
        /**
         * todo
         * @param assignedClass 
         */
        void setAssignedClass(char assignedClass);

        /**
         * clears entire image
         */
        void ClearImage();

    private:
        std::vector<std::vector<Pixel>> image_pixels_; // 2d vector of pixels
        char assigned_class_ = ' ';
    };

}  // namespace naivebayes