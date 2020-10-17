//
// Created by Abhigya Wangoo on 10/13/20.
//

#include "core/image_model.h"

namespace naivebayes {
    ImageModel::ImageModel(std::map<char, double> &class_probabilities, std::multimap<char, double> &pixel_probabilities)
            : class_probabilities_(class_probabilities), pixel_probabilities_(pixel_probabilities) {

    }

    const std::multimap<char, double> &ImageModel::get_pixel_probabilities() const {
        return pixel_probabilities_;
    }

    const std::map<char, double> &ImageModel::get_class_probabilities() const {
        return class_probabilities_;
    }
}