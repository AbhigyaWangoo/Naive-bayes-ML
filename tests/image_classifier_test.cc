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

    SECTION("Test test classifications of validation data images") {
        double correct_classifications = 0;
        size_t i = 0;
        
        while(i < 40) {
            if (classifier.DetermineImageLabel(classifier.get_images()[i]) == classifier.get_images()[i].get_assigned_class()) {
                correct_classifications++;
            }
            i++;
        }
        
        REQUIRE(correct_classifications / i > .7);
    }
    
    SECTION("Test 4x4 classification success rate") {
        double correct_classifications = 0;
        size_t i = 0;

        while(i < 20) {
            if (classifier.DetermineImageLabel(classifier.get_images()[i]) == classifier.get_images()[i].get_assigned_class()) {
                correct_classifications++;
            }
            i++;
        }
        
        REQUIRE(correct_classifications / i > .5);
    }
}