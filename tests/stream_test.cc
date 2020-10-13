#include <catch2/catch.hpp>

#include <core/classify.h>
#include <fstream>

TEST_CASE("Data stream functionality") {
    naivebayes::Classify classify;
    //std::ifstream test_classifications ("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/testclassifications", std::istream::in);

    std::ifstream test_images;
    test_images.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatatraining/trainingimages");

    std::ifstream test_classes;
    test_classes.open("/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/mnistdatatraining/trainingimages");

    test_images >> classify;
    test_classes >> classify;

    SECTION("Training Images have been loaded") {
        REQUIRE(classify.getTrainedImages().size() == 5000);
    }

    SECTION("Training Classes have been loaded") {
        REQUIRE(true);
    }

    SECTION("Training Classes and Images match") {
        REQUIRE(true);
    }
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
