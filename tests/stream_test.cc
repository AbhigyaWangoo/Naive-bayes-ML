#include <catch2/catch.hpp>

#include <core/classify.h>
#include <fstream>

TEST_CASE("Data stream functionality") {
    naivebayes::Classify classify;
    //std::ifstream test_classifications ("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/testclassifications", std::istream::in);

    std::ifstream test_images;
    test_images.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatatraining/trainingimages");

    std::ifstream test_classes;
    test_classes.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatatraining/traininglabels");

    test_images >> classify;
    test_classes >> classify;

    SECTION("Training Images have been loaded") {
        REQUIRE(classify.getTrainedImages().size() == 5000);
    }

    SECTION("Training Classes have been loaded") {
        REQUIRE(true); // TODO implement
    }

    SECTION("Training Classes and Images match") {
        REQUIRE(true); // Todo implement
    }

    std::ifstream test_file;

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/emptyfile");
    SECTION("File loaded was empty") {
        REQUIRE_THROWS_AS(test_file >> classify, std::runtime_error);
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/notclassorimage");
    SECTION("File loaded had random values but correct dimension") {
        REQUIRE_THROWS_AS(test_file >> classify, std::runtime_error);
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/largedimension");
    SECTION("File loaded was of a too large dimension for images") {
        REQUIRE_THROWS_AS(test_file >> classify, std::runtime_error);
        test_file.close();
    }

    test_file.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/smalldimension");
    SECTION("File loaded was too small of a dimension for images") {
        REQUIRE_THROWS_AS(test_file >> classify, std::runtime_error);
        test_file.close();
    }

    SECTION("Too many labels for the given image list") { // TODO implement
        REQUIRE_THROWS_AS(test_file >> classify, std::runtime_error);
        test_file.close();
    }

    SECTION("Too few labels for the given image list") { // TODO implement
        REQUIRE_THROWS_AS(test_file >> classify, std::runtime_error);
        test_file.close();
    }
}

/*
 * TODO delete me
You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.
*/
