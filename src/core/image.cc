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

    Image::Image() {
    }

    void Image::AddRow(std::vector<Pixel> &row) {
        image_pixels_.push_back(row);
    }

    void Image::ClearImage() {
        image_pixels_.clear();
        assigned_class_ = ' ';
    }

    std::ifstream &operator>>(std::ifstream &ifs, Image &image) {
        std::vector<Pixel> row;
        int length = 0;
        size_t characters_read = 0;
        size_t rows_read = 0;
        char c;

        ifs >> c;
        while (!ifs.eof()) {
            while (length == 0) {
                row.push_back(Pixel(c));
                ifs.get(c);
                characters_read++;

                if (c == '\n') {
                    length = characters_read;
                    characters_read = 0;
                    image.AddRow(row);
                    rows_read++;

                    row.clear();
                }
            }

            ifs.get(c);
            characters_read++;
            row.push_back(Pixel(c));

            if (characters_read == length) {
                image.AddRow(row);
                rows_read++;
                row.clear();

                ifs.get(c);
                characters_read = 0;
            }

            if (rows_read == length) {
                break;
            }
        }

        return ifs;
    }

    void Image::SetPixel(const Pixel &pixel, const size_t x, const size_t y) {
        image_pixels_[x][y] = Pixel(pixel.get_pixel_value());
    }
}  // namespace naivebayes