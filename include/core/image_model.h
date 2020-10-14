//
// Created by Abhigya Wangoo on 10/13/20.
//

#ifndef NAIVE_BAYES_IMAGE_MODEL_H
#define NAIVE_BAYES_IMAGE_MODEL_H

#include <map>
#include <vector>

namespace naivebayes {
    /**
     * Trained model for specific Image
     */
    class ImageModel {
    private:
        std::map<char, double> class_probabilities_;
        std::map<char, double> pixel_probabilities_;
    public:
        /**
         * Finds class_probabilities_
         *
         * @return class_probabilities_
         */
        const std::map<char, double> &getClassProbabilities() const;

        /**
         * Assigns values to class_probabilities_
         *
         * @param classProbabilities to assign to class_probabilities_
         */
        void setClassProbabilities(const std::map<char, double> &classProbabilities);

        /**
         * Finds pixel_probabilities_
         *
         * @return pixel_probabilities_
         */
        const std::map<char, double> &getPixelProbabilities() const;

        /**
         * Assigns a value to pixel_probabilities_
         *
         * @param pixelProbabilities to assign to pixel_probabilities_
         */
        void setPixelProbabilities(const std::map<char, double> &pixelProbabilities);
    };

}
#endif //NAIVE_BAYES_IMAGE_MODEL_H
