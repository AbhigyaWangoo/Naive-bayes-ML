#include <core/image.h>

namespace naivebayes {
    const char &Image::getKAssignedClass() const {
        return assigned_class_;
    }

    const std::vector<std::vector<Pixel>> &Image::getKImagePixels() const {
        return image_pixels_;
    }

    const size_t Image::getLength() const {
        return length_;
    }

    const size_t Image::getWidth() const {
        return width_;
    }

    void Image::setAssignedClass(char assignedClass) {
        assigned_class_ = assignedClass;
    }

    Image::Image() {
    }

    Image::Image(const std::vector<std::vector<Pixel>> &kImagePixels, const char kAssignedClass, const size_t length,
                 const size_t width) : image_pixels_(kImagePixels), assigned_class_(kAssignedClass) {
        width_ = width;
        length_ = length;
    }

    void Image::AddPixel(std::vector<Pixel> &row) {
        image_pixels_.push_back(row);
    }

    void Image::ClearImage() {
        image_pixels_.clear();
        assigned_class_ = ' ';
    }
}  // namespace naivebayes