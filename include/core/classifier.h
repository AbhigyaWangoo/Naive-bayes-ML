//
// Created by Abhigya Wangoo on 10/11/20.
//

#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include "image.h"
#include "image_model.h"

#include <map>
#include <vector>
#include <iostream>

#include <fstream>

namespace naivebayes {
    /**
     * Class containing all naive bayes computational functionality
     */
    class Classifier {
    public:
        static int length_;
        static int width_;

        /**
         * Overloaded operator to load trained images into list of Images
         *
         * @param ifs specifies the inputstream to recieve the images and labels from
         * @param classify object to load with images and labels
         * @return the result of the overloaded stream
         */
        friend std::ifstream &operator>>(std::ifstream &ifs, Classifier &classify);

        /**
         * Initializes the trained model if it hasn't already with images_
         *
         * @param images to add to the trained model file
         * @param saved_model_file indicates the file to read the model from if already initialized
         */
        void InitModel(const std::string &saved_model_file);

        /**
         * Gets the values of the trained images loaded from data
         *
         * @return values in vector<Image> form
         */
        const std::vector<Image> &get_images() const;

        /**
         * Gets values of trained model
         * 
         * @return trained model 
         */
        const std::vector<ImageModel> &get_trained_model() const;

    private:
        std::vector<Image> images_;
        std::vector<ImageModel> trained_model_ = {};

        /**
         * Finds the probability that a given image is of each class
         *
         * @param image to find class probabilities for
         * @return map of each class type, and the corresponding probability the image belongs to it
         */
        std::map<char, double> FindClassProbabilities(const Image &image) const;

        /**
         * Finds the probability of each pixel in the given image being shaded or not
         *
         * @param image to determine pixel probabilities for
         * @return map of each pixel value and the corresponding probability of it being shaded
         */
        std::multimap<char, double> FindPixelShadeProbabilities(const Image &image) const;

        /**
         * Calculates the P(class= c) probability, or the prior probability an image belonging to a certain class
         *
         * @param c for the possible class
         * @param lapace_k for naivebayes' algorithm
         * @return the appropriate probability
         */
        double CalculatePriorProbabilityOfClass(char c, double lapace_k) const;

        /**
         * Calculates the "ALLPIXELVALUES", or the total shaded probability of each of the pixels in an image
         *
         * @param image to calculate for
         * @return the total probability
         */
        double CalculateShadedProbabilityOfAllPixels(const Image &image) const;

        /**
         * Calculates the probability that an individual pixel is shaded
         *
         * @param x location of the pixel
         * @param y location of the pixel
         * @param classification represents the assigned classification
         * @param lapace_k represents the lapace k constant used
         * @return the probability of the pixel being shaded
         */
        double CalculateProbabilityPixelIsShaded(const size_t x, const size_t y, const char classification,
                                                 const double lapace_k) const;

        /**
         * Writes a specific model's information to a file
         *
         * @param ofstream specifies the file to write to
         * @param model specifies the model to write
         */
        void AddModelToFile(std::ofstream &ofstream, ImageModel &model);

        /**
         * Reads a file's information to a trained_model_
         *
         * @param ifstream specifies the file to read from
         */
        void ReadFromModel(std::ifstream &ifstream);

        /**
         * Reads the dimensions into length_ and width_
         * 
         * @param ifstream specifies file to read dimensions from 
         */
        static void ReadDimensions(std::ifstream &ifstream);

        /**
         * Writes length and width of image into trained model file
         * 
         * @param ofstream specifies file to write dimensions to 
         */
        void WriteDimensions(std::ofstream &ofstream);
    };

}

#endif //NAIVE_BAYES_CLASSIFIER_H
