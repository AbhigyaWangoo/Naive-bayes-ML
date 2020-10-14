#include <string>
#include <map>
#include <vector>

#include "pixel.h"

namespace naivebayes {

    static const std::vector<char> kClassifications = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    static const char kBlank = ' ';
    static const char kBlack = '#';
    static const char kGrey = '+';

    static size_t length_ = 28;
    static size_t width_ = 28;

    /**
     * Class holding representation of Image
     */
    class Image {

    public:
        Image();

        Image(const std::vector<std::vector<Pixel>> &kImagePixels, const char kAssignedClass, const size_t length,
              const size_t width);

        const char &getKAssignedClass() const;

        const std::vector<std::vector<Pixel>> &getKImagePixels() const;

        const size_t getLength() const;

        const size_t getWidth() const;

        /**
         * Adds row of Pixels to current image_pixels_
         *
         * @param row to add
         */
        void AddPixel(std::vector<Pixel> &row);

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