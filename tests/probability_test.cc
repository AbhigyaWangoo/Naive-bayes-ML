//
// Created by Abhigya Wangoo on 10/13/20.
//

#include <catch2/catch.hpp>

#include <core/classifier.h>
#include <fstream>
#include <core/image_model.h>

TEST_CASE("Basic tests for probability calculations") {
    std::ifstream ifs_images;
    std::ifstream ifs_labels;

    ifs_images.open(
            "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages");
    ifs_labels.open(
            "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreelabels");

    naivebayes::Classifier classifier;

    ifs_images >> classifier;
    ifs_labels >> classifier;

    classifier.InitializeModel(
            "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/trainedthreebythreemodel");

    SECTION("All Models have been loaded") {
        REQUIRE(classifier.get_trained_model().size() == 3);
    }

    SECTION("Pixel probabilities are correct") {
        std::vector<std::multimap<char, double>> correct_pixels;
        std::multimap<char, double> pixels;
        
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>('+', 0.980769));;
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        correct_pixels.push_back(pixels);
        pixels.clear();

        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        correct_pixels.push_back(pixels);
        pixels.clear();

        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>(' ', 0.0192308));
        pixels.insert(std::pair<char, double>('+', 0.980769));
        correct_pixels.push_back(pixels);
        pixels.clear();
        
        bool is_proper = true;
        for (size_t i = 0; i < 3; i++) {
            if (classifier.get_trained_model()[i].get_pixel_probabilities() != correct_pixels[i]) {
                is_proper = false;
            }
        }
        REQUIRE(is_proper);
    }

    SECTION("Label probabilities are correct") {
        std::map<char, double> labels;
        
        labels.insert(std::pair<char, double>('0', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('1', 0.335526));
        labels.insert(std::pair<char, double>('2', 0.335526));
        labels.insert(std::pair<char, double>('3', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('4', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('5', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('6', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('7', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('8', 0.0065789500000000001));
        labels.insert(std::pair<char, double>('9', 0.335526));
        
        bool is_proper = true;
        for (size_t i = 0; i < 2; i++) {
            if (classifier.get_trained_model()[i].get_class_probabilities() != labels) {
                is_proper = false;
            }
        }
        
        REQUIRE(is_proper);
    }

    SECTION("Trained model file specified isn't a model") {
        try {
            classifier.InitializeModel(
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/notclassorimage");
        } catch (std::runtime_error &error) {
            REQUIRE(true);
        }
    }
}