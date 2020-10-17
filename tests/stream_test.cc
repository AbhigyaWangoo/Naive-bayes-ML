#include <catch2/catch.hpp>

#include <core/classifier.h>
#include <fstream>

TEST_CASE("Data stream functionality") {
    SECTION("Test new Image dimensions of 3 by 3") {
        naivebayes::Classifier classify_3_images;

        std::ifstream test_3_images;
        std::ifstream test_3_labels;

        test_3_images.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages");
        test_3_labels.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreelabels");

        test_3_images >> classify_3_images;
        test_3_labels >> classify_3_images;

        SECTION("All images have been loaded in with labels") {
            bool succeed = classify_3_images.get_images().size() == 3 && classify_3_images.length_ == 3 && classify_3_images.width_ == 3;
            REQUIRE(succeed);
        }

        SECTION("All Images have correct Pixel values") {
            std::ifstream file;
            char c;
            file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages");

            for(const naivebayes::Image& current_image : classify_3_images.get_images()) {
                for(size_t i = 0; i < current_image.get_image_pixels().size(); i++) {
                    for(size_t j = 0; j < current_image.get_image_pixels()[i].size(); j++) {
                        file.get(c);

                        if(c == '\n'){
                            j--;
                            continue;
                        }
                        if(current_image.get_image_pixels()[i][j].getKPixelValue() != c) {
                            REQUIRE(false);
                        }
                    }
                }
            }

            REQUIRE(true);
        }

        SECTION("All Images have correct label values") {
            std::ifstream file;
            char c;
            file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreelabels");

            for(const naivebayes::Image& current_image : classify_3_images.get_images()) {
                file.get(c);
                if(c == '\n') {
                    file.get(c);
                }
                if(c != current_image.get_assigned_class()){
                    REQUIRE(false);
                }
            }

            REQUIRE(true);
        }
    }

    SECTION("Test new Image dimensions of 4 by 4") {

        naivebayes::Classifier classify_4_images;

        std::ifstream test_4_images;
        std::ifstream test_4_labels;

        test_4_images.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourimages");
        test_4_labels.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourlabels");

        test_4_images >> classify_4_images;
        test_4_labels >> classify_4_images;

        SECTION("All images have been loaded in with labels") {
            bool succeed = classify_4_images.get_images().size() == 4 && classify_4_images.length_ == 4 && classify_4_images.width_ == 4;
            
            REQUIRE(succeed);
        }

        SECTION("All Images have correct Pixel values") {
            std::ifstream file;
            char c;
            file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourimages");

            for(const naivebayes::Image& current_image : classify_4_images.get_images()) {
                for(size_t i = 0; i < current_image.get_image_pixels().size(); i++) {
                    for(size_t j = 0; j < current_image.get_image_pixels()[i].size(); j++) {
                        file.get(c);

                        if(c == '\n'){
                            file.get(c);
                        }
                        if(current_image.get_image_pixels()[i][j].getKPixelValue() != c) {
                            REQUIRE(false);
                        }
                    }
                }
            }

            REQUIRE(true);
        }

        SECTION("All Images have correct label values") {
            std::ifstream file;
            char c;
            file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourlabels");

            for(const naivebayes::Image& current_image : classify_4_images.get_images()) {
                file.get(c);
                if(c == '\n') {
                    file.get(c);
                }
                if(c != current_image.get_assigned_class()){
                    REQUIRE(false);
                }
            }

            REQUIRE(true);
        }
    }
    
    SECTION("File-facing errors") {
        naivebayes::Classifier classify;
        std::ifstream test_file;
        
        test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/emptyfile");
        SECTION("File loaded was empty") {
            try{
                test_file >> classify;
            } catch (std::runtime_error &runtime_error) {
                REQUIRE(true);
            }
            test_file.close();
        }

        test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/notclassorimage");
        SECTION("File loaded had random values but correct dimension") {
            try{
                test_file >> classify;
            } catch (std::runtime_error &runtime_error) {
                REQUIRE(true);
            }
            test_file.close();
        }

        test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/fourbyfourimages");
        SECTION("File loaded was of a too large dimension for images") {
            try{
                test_file >> classify;
            } catch (std::runtime_error &runtime_error) {
                REQUIRE(true);
            }
            test_file.close();
        }

        test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/smalldimension");
        SECTION("File loaded was too small of a dimension for images") {
            try{
                test_file >> classify;
            } catch (std::runtime_error &runtime_error) {
                REQUIRE(true);
            }
            test_file.close();
        }

        test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/toomanylabels");
        SECTION("Too many labels for the given image list") {
            try{
                test_file >> classify;
            } catch (std::runtime_error &runtime_error) {
                REQUIRE(true);
            }
            test_file.close();
        }

        test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/toofewlabels");
        SECTION("Too few labels for the given image list") {
            try{
                test_file >> classify;
            } catch (std::runtime_error &runtime_error) {
                REQUIRE(true);
            }
            test_file.close();
        }   
    }
}