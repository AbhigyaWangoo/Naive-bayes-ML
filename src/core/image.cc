#include <core/image.h>
#include <iostream>

namespace naivebayes {
    const char &Image::getKAssignedClass() const {
        return assigned_class_;
    }

    const std::vector<std::vector<Pixel>> &Image::getKImagePixels() const {
        return image_pixels_;
    }

    const size_t Image::getLength() const {
        return image_pixels_.size();
    }

    const size_t Image::getWidth() const {
        return image_pixels_[0].size();
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

    void Image::AddPixel(char &c) {
        Pixel pixel = Pixel(c);
        image_pixels_[image_pixels_.size()].push_back(pixel); // TODO definately not working
    }

    void Image::ClearImage() {
        image_pixels_.clear();
        assigned_class_ = ' ';
    }
}  // namespace naivebayes