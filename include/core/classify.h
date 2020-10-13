//
// Created by Abhigya Wangoo on 10/11/20.
//

#ifndef NAIVE_BAYES_CLASSIFY_H
#define NAIVE_BAYES_CLASSIFY_H

#include <map>
#include <vector>
#include <unordered_map>

#include "image.h"

namespace naivebayes {

    class Classify {
    public:

        /**
         * Overloaded operator to load trained images into list of Images
         *
         * @param ifs specifies the inputstream to recieve the images and labels from
         * @param classify object to load with images and labels
         * @return the result of the overloaded stream
         */
        friend std::ifstream &operator >> (std::ifstream &ifs, Classify &classify);

        /**
         * Finds the probability that a given image is of each class
         *
         * @param image to find class probabilities for
         * @return map of each class type, and the corresponding probability the image belongs to it
         */
        std::unordered_map<char, double> FindClassProbabilities(const Image &image) const;

        /**
         * Finds the probability of each pixel in the given image being shaded or not
         *
         * @param image to determine pixel probabilities for
         * @return map of each pixel value and the corresponding probability of it being shaded
         */
        std::map<char, double> FindPixelShadeProbabilities(const Image &image) const;

        // initialize kImages with this if the provided file with trained images is empty, otherwise call below 2
        /**
         * Initializes the trained model if it hasn't already
         *
         * @param images to add to the trained model file
         */
        void InitImages(const std::vector<Image> images);

        /**
         * Determines the probabilities of the class type and pixel shade
         */
        void GenerateGivenImageProbabilities(const Image &image);

        const std::vector<Image> &getTrainedImages() const;

    private:
        std::vector<Image> images_;


        /**
         * Generates file with trained model data
         */
        void GenerateTrainedModel(std::string file_name);

        double CalculatePriorProbabilityOfClass(char c) const;

        double CalculateShadedProbabilityOfAllPixels(const Image &image) const;

        double CalculateProbabilityPixelIsShaded(const size_t &x, const size_t &y, const char &classification, const double &lapace_k) const;
    };

}

#endif //NAIVE_BAYES_CLASSIFY_H
