//
// Created by Abhigya Wangoo on 10/13/20.
//

#include "core/image_model.h"

namespace naivebayes {
    ImageModel::ImageModel(std::map<char, double> &class_probabilities,
                           std::multimap<char, double> &pixel_probabilities)
            : class_probabilities_(class_probabilities), pixel_probabilities_(pixel_probabilities) {
        
    }

    const std::multimap<char, double> &ImageModel::get_pixel_probabilities() const {
        return pixel_probabilities_;
    }

    const std::map<char, double> &ImageModel::get_class_probabilities() const {
        return class_probabilities_;
    }
    
    std::ofstream &operator<<(std::ofstream &ofs, ImageModel &image_model) {
        std::map<char, double> classification_probabilities = image_model.get_class_probabilities();
        std::multimap<char, double> pixel_probabilities = image_model.get_pixel_probabilities();
        std::map<char, double>::iterator it;

        for (it = classification_probabilities.begin(); it != classification_probabilities.end(); it++) {
            ofs << it->first << it->second << ",";
        }

        for (it = pixel_probabilities.begin(); it != pixel_probabilities.end(); it++) {
            ofs << it->first << it->second << ",";
        }
        ofs.flush();

        return ofs;
    }
}