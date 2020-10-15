#include <catch2/catch.hpp>

#include <core/classifier.h>
#include <fstream>

TEST_CASE("Data stream functionality") {
    naivebayes::Classifier classify;

    std::ifstream test_images;
    test_images.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourimage");

    std::ifstream test_classes;
    test_classes.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourlabel");

    test_images >> classify;
    test_classes >> classify;
    
    SECTION("Training Images have been loaded") {
        REQUIRE(classify.get_images().size() == 5000);
    }

    SECTION("Training Classes have been loaded") {
        std::vector<char> test_labels = {'5', '0'};
        REQUIRE(classify.get_images()[0].get_assigned_class() == '5');
    }

    std::vector<char> first_ten_values = {'5', '0', '4', '1', '9', '2', '1', '3', '1', '4'};
    bool fail = false;

    for(size_t i = 0; i < 10;i++ ) {
        if(first_ten_values[i] != classify.get_images()[i].get_assigned_class()) {
            fail = true;
        }
    SECTION("Training Classes and Images match") {
        REQUIRE_FALSE(fail);
        }
    }

    std::ifstream test_file;
    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/emptyfile");
    SECTION("File loaded was empty") {
        try{
            test_file >> classify;
        } catch (std::runtime_error &runtime_error) {
            REQUIRE_FALSE(true);
        }
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/notclassorimage");
    SECTION("File loaded had random values but correct dimension") {
        try{
            test_file >> classify;
        } catch (std::runtime_error &runtime_error) {
            REQUIRE_FALSE(true);
        }
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourimage");
    SECTION("File loaded was of a too large dimension for images") {
        try{
            test_file >> classify;
        } catch (std::runtime_error &runtime_error) {
            REQUIRE_FALSE(true);
        }
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/smalldimension");
    SECTION("File loaded was too small of a dimension for images") {
        try{
            test_file >> classify;
        } catch (std::runtime_error &runtime_error) {
            REQUIRE_FALSE(true);
        }
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/toomanylabels");
    SECTION("Too many labels for the given image list") {
        try{
            test_file >> classify;
        } catch (std::runtime_error &runtime_error) {
            REQUIRE_FALSE(true);
        }
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/toofewlabels");
    SECTION("Too few labels for the given image list") {
        try{
            test_file >> classify;
        } catch (std::runtime_error &runtime_error) {
            REQUIRE_FALSE(true);
        }
        test_file.close();
    }
}