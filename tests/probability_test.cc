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
        bool is_proper = true;
        for (size_t i = 0; i < 3; i++) {
            if (classifier.get_trained_model()[i].get_pixel_probabilities().find(' ')->second == 0.666667) {
                if (classifier.get_trained_model()[i].get_pixel_probabilities().find('+')->second == 0.666667) {
                    is_proper = true;
                }
            }
        }
        REQUIRE(is_proper);
    }

    SECTION("Label probabilities are correct") {
        std::map<char, double> labels;
        
        labels.insert(std::pair<char, double>('0', 0.2));
        labels.insert(std::pair<char, double>('1', 0.4));
        labels.insert(std::pair<char, double>('2', 0.4));
        labels.insert(std::pair<char, double>('3', 0.2));
        labels.insert(std::pair<char, double>('4', 0.2));
        labels.insert(std::pair<char, double>('5', 0.2));
        labels.insert(std::pair<char, double>('6', 0.2));
        labels.insert(std::pair<char, double>('7', 0.2));
        labels.insert(std::pair<char, double>('8', 0.2));
        labels.insert(std::pair<char, double>('9', 0.4));
        
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