//
// Created by Abhigya Wangoo on 10/17/20.
//

#include <catch2/catch.hpp>
#include <core/classifier.h>

TEST_CASE("Test basic classification") {
    naivebayes::Classifier classifier;
    
    std::ifstream training_images;
    std::ifstream training_labels;
    
    training_images.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatavalidation/testimages");
    training_labels.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatavalidation/testlabels");
    
    training_images >> classifier;
    training_labels >> classifier;
    
    classifier.InitializeModel("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatavalidation/trainedmodel");
    SECTION("Test test classifications of mnistdatavalidation") {
        char c;
        SECTION("Identify 0 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[1]);
            REQUIRE(c == '0');
        }
        SECTION("Identify 1 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[4]);
            REQUIRE(c == '1');
        }
        SECTION("Identify 2 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[2]);
            REQUIRE(c == '2');
        }
        SECTION("Identify 3 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[20]);
            REQUIRE(c == '3');
        }
        SECTION("Identify 4 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[10]);
            REQUIRE(c == '4');
        }
        SECTION("Identify 5 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[3]);
            REQUIRE(c == '5');
        }
        SECTION("Identify 6 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[14]); 
            REQUIRE(c == '6');
        }
        SECTION("Identify 7 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[6]);
            REQUIRE(c == '7');
        }
        SECTION("Identify 8 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[7]);
            REQUIRE(c == '8');
        }
        SECTION("Identify 9 correctly") {
            c = classifier.DetermineImageLabel(classifier.get_images()[5]);
            REQUIRE(c == '9');
        }
    }
    SECTION("Test Success rate") {
        double correct_classifications = 0;
        naivebayes::Classifier images_to_classify;
        size_t i = 0;
        
        while(i < 1) {
            if (images_to_classify.DetermineImageLabel(classifier.get_images()[i]) == classifier.get_images()[i].get_assigned_class()) {
                correct_classifications++;
            }
            i++;
        }
        
        REQUIRE(correct_classifications / i > .7);
    }
    
    SECTION("Test 4x4 classifications of new images") {
        SECTION("Identify 0 correctly") {

        }
        SECTION("Identify 1 correctly") {

        }
        SECTION("Identify 2 correctly") {

        }
        SECTION("Identify 3 correctly") {

        }
        SECTION("Identify 4 correctly") {

        }
        SECTION("Identify 5 correctly") {

        }
        SECTION("Identify 6 correctly") {

        }
        SECTION("Identify 7 correctly") {

        }
        SECTION("Identify 8 correctly") {

        }
        SECTION("Identify 9 correctly") {

        }
        REQUIRE(true);
    }
    
    SECTION("Mathematics calculations"){
        // TODO implement
        REQUIRE(true);
    }
}