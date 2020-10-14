//
// Created by Abhigya Wangoo on 10/13/20.
//

#include "core/image_model.h"

namespace naivebayes {

    const std::map<char, double> &ImageModel::getClassProbabilities() const {
        return class_probabilities_;
    }

    void ImageModel::setClassProbabilities(const std::map<char, double> &classProbabilities) {
        class_probabilities_ = classProbabilities;
    }

    const std::map<char, double> &ImageModel::getPixelProbabilities() const {
        return pixel_probabilities_;
    }

    void ImageModel::setPixelProbabilities(const std::map<char, double> &pixelProbabilities) {
        pixel_probabilities_ = pixelProbabilities;
    }
}