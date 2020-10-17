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

    classifier.InitModel(
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
            if (classifier.get_trained_model()[i].getPixelProbabilities() != correct_pixels[i]) {
                is_proper = false;
            }
        }
        REQUIRE(is_proper);
    }

    SECTION("Label probabilities are correct") {
        std::vector<std::map<char, double>> correct_labels;
        std::map<char, double> labels;
        
        labels.insert(std::pair<char, double>('0', 3.13933e-13));
        labels.insert(std::pair<char, double>('1', 1.60106e-11));
        labels.insert(std::pair<char, double>('2', 1.60106e-11));
        labels.insert(std::pair<char, double>('3', 3.13933e-13));
        labels.insert(std::pair<char, double>('4', 3.13933e-13));
        labels.insert(std::pair<char, double>('5', 3.13933e-13));
        labels.insert(std::pair<char, double>('6', 3.13933e-13));
        labels.insert(std::pair<char, double>('7', 3.13933e-13));
        labels.insert(std::pair<char, double>('8', 3.13933e-13));
        labels.insert(std::pair<char, double>('9', 1.60106e-11));
        correct_labels.push_back(labels);
        labels.clear();
        
        labels.insert(std::pair<char, double>('0', 2.12382e-06));
        labels.insert(std::pair<char, double>('1', 0.000108315));
        labels.insert(std::pair<char, double>('2', 0.000108315));
        labels.insert(std::pair<char, double>('3', 2.12382e-06));
        labels.insert(std::pair<char, double>('4', 2.12382e-06));
        labels.insert(std::pair<char, double>('5', 2.12382e-06));
        labels.insert(std::pair<char, double>('6', 2.12382e-06));
        labels.insert(std::pair<char, double>('7', 2.12382e-06));
        labels.insert(std::pair<char, double>('8', 2.12382e-06));
        labels.insert(std::pair<char, double>('9', 0.000108315));
        correct_labels.push_back(labels);
        labels.clear();
        
        bool is_proper = true;
        for (size_t i = 0; i < 2; i++) {
            if (classifier.get_trained_model()[i].getClassProbabilities() != correct_labels[i]) {
                is_proper = false;
            }
        }
        REQUIRE(is_proper);
    }

    SECTION("Trained model file specified isn't a model") {
        try {
            classifier.InitModel(
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/notclassorimage");
        } catch (std::runtime_error &error) {
            REQUIRE(true);
        }
    }
}