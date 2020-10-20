//
// Created by Abhigya Wangoo on 10/11/20.
//
#include "core/classifier.h"

namespace naivebayes {
    int Classifier::length_ = 0;
    int Classifier::width_ = 0;

    std::map<char, double> Classifier::FindLikelyhoodScores(const Image &image) {
        std::map<char, double> classifications;
        std::multimap<char, double> pixel_probabilities;
        std::map<char, double> prior_probabilities = CalculatePriorProbabilitiesOfModel();
        double current_class_probability;
        double pixels_shade_probability;

        for (char label: kClassifications) {
            current_class_probability = prior_probabilities.at(label);
            pixel_probabilities = FindPixelShadeProbabilities(image, label);
            pixels_shade_probability = CalculateShadedProbabilityOfAllPixels(pixel_probabilities);
            
            classifications.insert(
                    std::pair<char, double>(label, std::log10(current_class_probability) * pixels_shade_probability));
        }

        return classifications;
    }

    std::multimap<char, double> Classifier::FindPixelShadeProbabilities(const Image &image, const char label) const {
        std::multimap<char, double> image_pixel_probabilities;
        double current_probability;

        for (size_t i = 0; i < length_; i++) {
            for (size_t j = 0; j < width_; j++) {
                if(image.get_image_pixels()[i][j].IsShaded()) {
                    current_probability = CalculatePixelShadeProbability(i, j, label, true);
                } else if (!image.get_image_pixels()[i][j].IsShaded()) {
                    current_probability = CalculatePixelShadeProbability(i, j, label, false);
                }

                image_pixel_probabilities.insert(
                        std::pair<char, double>(image.get_image_pixels()[i][j].getKPixelValue(), current_probability));
            }
        }

        return image_pixel_probabilities;
    }

    void Classifier::InitializeModel(const std::string &saved_model_file) {
        std::ifstream ifs;

        ifs.open(saved_model_file);
        if (ifs.peek() == std::ifstream::traits_type::eof()) {
            ifs.close();

            std::ofstream ofs;
            ofs.open(saved_model_file);

            WriteDimensions(ofs);
            size_t i = 0;
            std::map<char, double> class_probabilities = CalculatePriorProbabilitiesOfModel();
            for (const Image &image : images_) {
                std::multimap<char, double> pixel_probabilities = FindPixelShadeProbabilities(image,
                                                                                              image.get_assigned_class());
                ImageModel current_image_model = ImageModel(class_probabilities, pixel_probabilities);

                trained_model_.push_back(current_image_model);

                ofs << trained_model_[i];
                i++;
            }

            ofs.close();

        } else {
            ReadFromModel(ifs);
            ifs.close();
        }
    }

    std::ifstream &operator>>(std::ifstream &ifs, Classifier &classify) {
        char current_character;
        size_t image_index = 0;
        size_t image_characters_read = 0;
        Image current_image;
        std::vector<Pixel> current_row = {};
        bool is_image_file = true;
        size_t total_read = 0;

        while (ifs.get(current_character) && !ifs.eof()) {
            if (std::count(kClassifications.begin(), kClassifications.end(), current_character)) {
                is_image_file = false;
                classify.images_[image_index].set_assigned_class(current_character);
                image_index++;
            } else if ((current_character == naivebayes::kBlack || current_character == naivebayes::kBlank || current_character == naivebayes::kGrey || current_character == '\n') &&
                       is_image_file) {

                if (current_character == '\n') {
                    current_image.AddRow(current_row);
                    if (classify.images_.empty()) {
                        Classifier::length_ = current_row.size();
                        Classifier::width_ = current_row.size();
                    }
                    current_row.clear();

                    if (image_characters_read == Classifier::width_ * Classifier::length_) {
                        image_characters_read = 0;

                        classify.images_.push_back(current_image);
                        current_image.ClearImage();
                    }

                } else {
                    image_characters_read++;
                    total_read++;
                    current_row.push_back(Pixel(current_character));
                }


            } else if (current_character == '\n') {
                continue;
            } else {
                throw std::runtime_error("incorrect type");
            }
        }
        if (classify.images_.empty()) {
            throw std::runtime_error("invalid file");
        }
        return ifs;
    }

    std::map<char, double> Classifier::CalculatePriorProbabilitiesOfModel() const {
        std::map<char, double> image_class_probabilites;
        double class_count = 0;

        for (const char k : kClassifications) {
            for (const Image &img : images_) {
                if (k == img.get_assigned_class()) {
                    class_count++;
                }
            }
            image_class_probabilites.insert(
                    std::pair<char, double>(k, (lapace_k + class_count) / (2 * lapace_k + images_.size())));
            class_count = 0;
        }

        return image_class_probabilites;
    }

    double Classifier::CalculateShadedProbabilityOfAllPixels(const std::multimap<char, double> &pixels) const {
        double total_pixel_probability = 0;

        for(std::pair<char, double> pixel_probability : pixels){
            total_pixel_probability += std::log10(pixel_probability.second);
        }
        
//        for (size_t i = 0; i < length_; i++) {
//            for (size_t j = 0; j < width_; j++) {
//                total_pixel_probability += 
//                        std::log10(CalculatePixelShadeProbability(i, j, classification, true));
//            }
//        }

        return total_pixel_probability;
    }

    double Classifier::CalculatePixelShadeProbability(const int x, const int y, const char classification, const bool shaded) const {
        double num_images_with_desired_pixel_at_spot = 0;
        double num_images_of_classification = 0;

        for (const Image &image : images_) {
            if (image.get_assigned_class() == classification) {
                num_images_of_classification++;

                if (image.get_image_pixels()[x][y].IsShaded() && shaded) {
                    num_images_with_desired_pixel_at_spot++;
                }

                if (!image.get_image_pixels()[x][y].IsShaded() && !shaded) {
                    num_images_with_desired_pixel_at_spot++;
                }
            }
        }
        
        return (lapace_k + num_images_with_desired_pixel_at_spot) / (2 * lapace_k + num_images_of_classification);
    }

    const std::vector<Image> &Classifier::get_images() const {
        return images_;
    }

    void Classifier::ReadFromModel(std::ifstream &ifstream) {
        std::map<char, double> read_label_probabilities;
        std::multimap<char, double> read_pixel_probabilities;
        bool is_reading_pixels;
        bool is_reading_labels;

        ReadDimensions(ifstream);
        while (!ifstream.eof() && trained_model_.size() != images_.size()) {
            double current_probability = 0;
            char current_character = 0;
            char dlimiter = 0;

            ifstream.get(current_character);
            ifstream >> current_probability;
            ifstream.get(dlimiter);

            is_reading_pixels = (current_character == kBlank || current_character == kGrey || current_character == kBlack);
            is_reading_labels = std::count(kClassifications.begin(), kClassifications.end(), current_character);

            if (is_reading_pixels) {
                read_pixel_probabilities.insert(std::pair<char, double>(current_character, current_probability));
            } else if (is_reading_labels) {
                read_label_probabilities.insert(std::pair<char, double>(current_character, current_probability));
            } else {
                throw std::runtime_error("Not a model file");
            }

            if (read_label_probabilities.size() == kClassifications.size() &&
                read_pixel_probabilities.size() == length_ * width_) {
                trained_model_.push_back(ImageModel(read_label_probabilities, read_pixel_probabilities));

                read_pixel_probabilities.clear();
                read_label_probabilities.clear();
            }
        }
    }

    void Classifier::ReadDimensions(std::ifstream &ifstream) {
        char current_dimension;
        ifstream >> length_;
        ifstream.get(current_dimension);
        ifstream >> width_;
        ifstream.get(current_dimension);
    }

    void Classifier::WriteDimensions(std::ofstream &ofstream) {
        ofstream << Classifier::length_ << " " << Classifier::width_ << " ";
    }

    const std::vector<ImageModel> &Classifier::get_trained_model() const {
        return trained_model_;
    }

    char Classifier::DetermineImageLabel(const Image &image) {
        std::map<char, double> given_image_label_probabilities = FindLikelyhoodScores(image);
        std::pair<char, double> max = {'0', given_image_label_probabilities.at('0')};

        for (std::pair<char, double> label_probability : given_image_label_probabilities) {
            if (label_probability.second < max.second) {
                max = label_probability;
            }
        }
        
        images_[images_.size()].set_assigned_class(max.first);
        return max.first;
        
    }
}  // namespace naivebayes
