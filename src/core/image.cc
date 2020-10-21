#include <core/image.h>

namespace naivebayes {
    const char &Image::get_assigned_class() const {
        return assigned_class_;
    }

    const std::vector<std::vector<Pixel>> &Image::get_image_pixels() const {
        return image_pixels_;
    }

    void Image::set_assigned_class(char assignedClass) {
        assigned_class_ = assignedClass;
    }
    
    void Image::AddRow(std::vector<Pixel> &row) {
        image_pixels_.push_back(row);
    }

    void Image::ClearImage() {
        image_pixels_.clear();
    }
    
    void Image::SetPixel(const Pixel &pixel, const size_t x, const size_t y) {
        image_pixels_[x][y] = Pixel(pixel.get_pixel_value());
    }
}  // namespace naivebayes