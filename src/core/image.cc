#include <core/image.h>

namespace naivebayes {
    const char &Image::get_assigned_class() const {
        return assigned_class_;
    }

    const std::vector<std::vector<Pixel>> &Image::getKImagePixels() const {
        return image_pixels_;
    }

    void Image::setAssignedClass(char assignedClass) {
        assigned_class_ = assignedClass;
    }

    Image::Image() {
    }

    void Image::AddPixel(std::vector<Pixel> &row) {
        image_pixels_.push_back(row);
    }

    void Image::ClearImage() {
        image_pixels_.clear();
        assigned_class_ = ' ';
    }
}  // namespace naivebayes