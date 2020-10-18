//
// Created by Abhigya Wangoo on 10/11/20.
//
#include "core/classifier.h"

namespace naivebayes {
    int Classifier::length_ = 0;
    int Classifier::width_ = 0;

    std::map<char, double> Classifier::FindLikelyhoodScore(const Image &image) const {
        std::map<char, double> classifications;
        double current_class_probability;
        double pixels_shade_probability;

        for (char c: kClassifications) {
            current_class_probability = CalculatePriorProbabilitiesOfModel().at(c);
            pixels_shade_probability = CalculateShadedProbabilityOfAllPixels(image);

            classifications.insert(std::pair<char, double>(c, std::log10(current_class_probability) + pixels_shade_probability));
        }

        return classifications;
    }

    std::multimap<char, double> Classifier::FindPixelShadeProbabilities(const Image &image, const char label) const {
        std::multimap<char, double> image_pixel_probabilities;
        double current_probability;

        for (size_t i = 0; i < image.get_image_pixels().size(); i++) {
            for (size_t j = 0; j < image.get_image_pixels()[i].size(); j++) {
                current_probability = CalculateProbabilityPixelIsShaded(i, j, label);

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
                std::multimap<char, double> pixel_probabilities = FindPixelShadeProbabilities(image, image.get_assigned_class());
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
        char c;
        size_t image_index = 0;
        size_t image_characters_read = 0;
        Image current_image;
        std::vector<Pixel> current_row = {};
        bool is_image_file = true;
        size_t total_read = 0;

        while (ifs.get(c) && !ifs.eof()) {
            if (std::count(kClassifications.begin(), kClassifications.end(), c)) {
                is_image_file = false;
                classify.images_[image_index].set_assigned_class(c);
                image_index++;
            } else if ((c == naivebayes::kBlack || c == naivebayes::kBlank || c == naivebayes::kGrey || c == '\n') &&
                       is_image_file) {

                if (c == '\n') {
                    current_image.AddPixel(current_row);
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
                    current_row.push_back(Pixel(c));
                }


            } else if (c == '\n') {
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
        
        for(const char k : kClassifications) {
            for (const Image &img : images_) {
                if (k == img.get_assigned_class()) {
                    class_count++;
                }
            }
            image_class_probabilites.insert(std::pair<char, double>(k, (lapace_k + class_count) / (2 * lapace_k + images_.size())));
            class_count = 0;
        }
        
        return image_class_probabilites;
    }

    double Classifier::CalculateShadedProbabilityOfAllPixels(const Image &image) const {
        double total_pixel_probability = 0;

        for (size_t i = 0; i < image.get_image_pixels().size(); i++) {
            for (size_t j = 0; j < image.get_image_pixels()[i].size(); j++) {
//                if (total_pixel_probability == 0) {
//                } else {
//                    total_pixel_probability *= CalculateProbabilityPixelIsShaded(i, j, image.get_assigned_class());
//                }
                total_pixel_probability += std::log10(CalculateProbabilityPixelIsShaded(i, j, image.get_assigned_class()));
            }
        }

        return total_pixel_probability;
    }

    double Classifier::CalculateProbabilityPixelIsShaded(const int x, const int y, const char classification) const {
        double num_images_with_shaded_pixel_at_spot = 0;
        double num_images_of_classification = 0;

        for (const Image &image : images_) {
            if (image.get_assigned_class() == classification) {
                num_images_of_classification++;
                
                if (image.get_image_pixels()[x][y].IsShaded()) {
                    num_images_with_shaded_pixel_at_spot++;
                }
            }
        }

        return (lapace_k + num_images_with_shaded_pixel_at_spot) / (2 * lapace_k + num_images_of_classification);
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
            double d = 0;
            char c = 0;
            char dlimiter = 0;

            ifstream.get(c);
            ifstream >> d;
            ifstream.get(dlimiter);

            is_reading_pixels = (c == kBlank || c == kGrey || c == kBlack);
            is_reading_labels = std::count(kClassifications.begin(), kClassifications.end(), c);

            if (is_reading_pixels) {
                read_pixel_probabilities.insert(std::pair<char, double>(c, d));
            } else if (is_reading_labels) {
                read_label_probabilities.insert(std::pair<char, double>(c, d));
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
        char c;
        ifstream >> length_;
        ifstream.get(c);
        ifstream >> width_;
        ifstream.get(c);
    }

    void Classifier::WriteDimensions(std::ofstream &ofstream) {
        ofstream << Classifier::length_ << " " << Classifier::width_ << " ";
    }

    const std::vector<ImageModel> &Classifier::get_trained_model() const {
        return trained_model_;
    }
}  // namespace naivebayes
