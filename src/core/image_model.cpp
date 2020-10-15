//
// Created by Abhigya Wangoo on 10/13/20.
//

#include "core/image_model.h"

namespace naivebayes {
    void ImageModel::SetClassProbabilities(std::map<char, double> &classProbabilities) {
        class_probabilities_ = classProbabilities;
    }

    void ImageModel::SetPixelProbabilities(std::map<char, double> &pixelProbabilities) {
        pixel_probabilities_ = pixelProbabilities;
    }

    ImageModel::ImageModel(std::map<char, double> &class_probabilities, std::map<char, double> &pixel_probabilities)
            : class_probabilities_(class_probabilities), pixel_probabilities_(pixel_probabilities) {

    }
}