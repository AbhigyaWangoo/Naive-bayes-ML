#include <string>
#include <map>
#include <vector>

#include "pixel.h"

namespace naivebayes {

    static const std::vector<char> kClassifications = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    static const char kBlank = ' ';
    static const char kBlack = '#';
    static const char kGrey = '+';

    class Image {

    public:
        Image();

        Image(const std::vector<std::vector<Pixel>> &kImagePixels, const char kAssignedClass, const size_t length,
              const size_t width);

        const char &getKAssignedClass() const;

        const std::vector<std::vector<Pixel>> &getKImagePixels() const;

        const size_t getLength() const;

        const size_t getWidth() const;

        void AddPixel(char &c);

        void setAssignedClass(char assignedClass);

        void ClearImage();

    private:
        std::vector<std::vector<Pixel>> image_pixels_ = {{}}; // 2d vector of pixels
        char assigned_class_;

        const size_t length = 28;
        const size_t width = 28;
    };

}  // namespace naivebayes