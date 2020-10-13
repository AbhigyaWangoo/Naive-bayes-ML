//
// Created by Abhigya Wangoo on 10/11/20.
//

#include "core/classify.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

namespace naivebayes {

    std::unordered_map<char, double> Classify::FindClassProbabilities(const Image &image) const {
        std::unordered_map<char, double> classifications;
        size_t current_class_probability;
        double pixels_shade_probability;

        for (char c: naivebayes::kClassifications) {
            // P(class = c | AllPixelValues)
            current_class_probability = CalculatePriorProbabilityOfClass(c); // P(class = 0)
            pixels_shade_probability = CalculateShadedProbabilityOfAllPixels(image); // P(ALLPIXELVALUES | class = c)

            classifications.emplace(c, current_class_probability * pixels_shade_probability);
        }

        return classifications;
    }

    std::map<char, double> Classify::FindPixelShadeProbabilities(const Image &image) const {
        std::map<char, double> image_pixel_probabilities;
        double current_probability;

        for (size_t i = 0; i < image.getKImagePixels().size(); i++) {
            for (size_t j = 0; j < image.getKImagePixels()[i].size(); j++) {
                current_probability = CalculateProbabilityPixelIsShaded(i, j, image.getKAssignedClass(),
                                                                        .02); // P(i,j = 1 | class = c)

                image_pixel_probabilities.emplace(image.getKImagePixels()[i][j].getKPixelValue(), current_probability);
            }
        }

        return image_pixel_probabilities;
    }

    // initialize kImages with this if the provided file with trained images is empty, otherwise call below 2
    /**
     * Initializes the trained model if it hasn't already
     *
     * @param images to extract data from and then write to file
     * @param saved_model_file to specify trained model file
     */
    void Classify::InitModel(const std::vector<Image> images, const std::string &saved_model_file) {
        std::ifstream ifs;

        ifs.open(saved_model_file);
        if(ifs.eof()) {
            ifs.close();

            std::ofstream ofs;
            ofs.open(saved_model_file);
            std::unordered_map<char, double> class_probabilities;
            std::map<char, double> pixel_probabilities;

            for(Image image : images){
                class_probabilities = FindClassProbabilities(image);
                pixel_probabilities = FindPixelShadeProbabilities(image);

                //write class and pixel probabilities to file
            }
        } else {

        }
    }

    void Classify::GenerateGivenImageProbabilities(const Image &image) {
        std::unordered_map<char, double> class_probabilities = FindClassProbabilities(image);
        std::map<char, double> pixel_probabilities = FindPixelShadeProbabilities(image);
    }

    std::ifstream &operator>>(std::ifstream &ifs, Classify &classify) {
        char c = ifs.get();
        size_t image_index = 0;
        size_t image_characters_read = 0;
        Image current_image;

        while (!ifs.eof() && (c == naivebayes::kBlack || c == naivebayes::kBlank || c == naivebayes::kGrey)) {
            if (image_characters_read == current_image.getWidth() * current_image.getLength()) {
                image_characters_read = 0;

                classify.images_.push_back(current_image);
                current_image.ClearImage();
            }

            current_image.AddPixel(c);
            image_characters_read++;
        }

        while (!ifs.eof()) {
            classify.images_[image_index].setAssignedClass(c);
            c = ifs.get();
        }

        if (classify.images_.empty() || (classify.images_[0].getWidth() != width_) ||
            classify.images_[0].getLength() != length_) {
            throw std::runtime_error("File was empty or of incorrect type");
        }

        return ifs;
    }

    void Classify::GenerateTrainedModel(std::string file_name) {
        // write trained images and classifications to file
    }

    double Classify::CalculatePriorProbabilityOfClass(char c) const {
        int total_class_count = 0;

        for (Image image : images_) {
            if (image.getKAssignedClass() == c) {
                total_class_count++;
            }
        }

        return total_class_count / images_.size();
    }

    double Classify::CalculateShadedProbabilityOfAllPixels(const Image &image) const {
        double total_pixel_probability = 0;

        for (size_t i = 0; i < image.getKImagePixels().size(); i++) {
            for (size_t j = 0; j < image.getKImagePixels()[i].size(); j++) {
                if (total_pixel_probability == 0) {
                    total_pixel_probability += CalculateProbabilityPixelIsShaded(i, j, image.getKAssignedClass(), 0.02);
                }

                total_pixel_probability *= CalculateProbabilityPixelIsShaded(i, j, image.getKAssignedClass(), 0.02);
            }
        }

        return total_pixel_probability;
    }

    double Classify::CalculateProbabilityPixelIsShaded(const size_t &x, const size_t &y, const char &classification,
                                                       const double &lapace_k) const {
        double num_images_with_shaded_pixel_at_spot = 0;
        double num_images_of_classification = 0;

        for (Image image : images_) {
            if (image.getKAssignedClass() == classification) { // P(i,j = 1 | class = c)
                num_images_of_classification++;
            }

            if (image.getKImagePixels()[x][y].IsShaded()) {
                num_images_with_shaded_pixel_at_spot++;
            }
        }

        return (lapace_k + num_images_with_shaded_pixel_at_spot) / (2 * lapace_k + num_images_of_classification);
    }

    const std::vector<Image> &Classify::getTrainedImages() const {
        return images_;
    }
}
