#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <core/main_executor.h>

TEST_CASE("Testing CLI") {
    naivebayes::MainExecutor mainExecutor;
    std::vector<std::string> command;

    SECTION("Ensure command is properly followed") {
        command = {
                "train",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreelabels",
                "save",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/newtestfile"
        };

        SECTION("Create model in new file") {
            try {
                mainExecutor.DetermineCommand(command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                std::cout << error.what();
                REQUIRE(false);
            }
        }

        SECTION("Create model from existing file") {
            try {
                mainExecutor.DetermineCommand(command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                std::cout << error.what();
                REQUIRE(false);
            }
        }

        command = {
                "train",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreelabels",
                "test",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages"
        };
        SECTION("Create model from existing file and test it") {
            try {
                mainExecutor.DetermineCommand(command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                std::cout << error.what();
                REQUIRE(false);
            }
        }

        command = {
                "train",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreelabels",
                "save",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/newtestfile",
                "test",
                "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages"
        };
        SECTION("Create model from new file and test it") {
            try {
                mainExecutor.DetermineCommand(command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                std::cout << error.what();
                REQUIRE(false);
            }
        }

        SECTION("Command to check case insensitivity ") {
            command = {
                    "tRAIN",
                    "/Users/abhigyawangoo/CLionProjects/CINDer/my-projects/naivebayes-AbhiWangoo/DATa/testingdata/threebythreeimages",
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreemodels",
                    "SAVE",
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/NEWtestfile"};
            try {
                mainExecutor.DetermineCommand(command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                std::cout << error.what();
                REQUIRE(false);
            }
        }
    }

    SECTION("Failed command inputs") {
        SECTION("Not putting in a file for images") {
            try {
                command = {
                        "train",
                        "a",
                        "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreemodels",
                        "save",
                        "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/newtestfile"};

                mainExecutor.DetermineCommand(command);
            } catch (std::runtime_error error) {
                REQUIRE(true);
            }
        }

        SECTION("Not putting in a file for labels") {
            try {
                command = {
                        "train",
                        "/Users/abhigyawangoo/CLionProjects/CINDer/my-projects/naivebayes-AbhiWangoo/DATa/testingdata/threebythreeimages ",
                        "/Users/abhigyawangoo/CLionProjects/Cinder/",
                        "save",
                        "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/newtestfile"};

                mainExecutor.DetermineCommand(command);
            } catch (std::runtime_error error) {
                REQUIRE(true);
            }
        }

        SECTION("Not putting in a train command") {
            try {
                command = {"a",
                           "/Users/abhigyawangoo/CLionProjects/CINDer/my-projects/naivebayes-AbhiWangoo/DATa/testingdata/threebythreeimages",
                           "/Users/abhigyawangoo/CLionProjects/Cinder/ ",
                           "save",
                           "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/newtestfile"};

                mainExecutor.DetermineCommand(command);
            } catch (std::runtime_error error) {
                REQUIRE(true);
            }
        }

        SECTION("Not putting in a save command") {
            command = {
                    "train",
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreeimages",
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreemodels",
                    "s",
                    "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/newtestfile"};
            std::ifstream ifs;
            SECTION("Create model in new file") {
                try {
                    mainExecutor.DetermineCommand(command);
                } catch (std::runtime_error error) {
                    REQUIRE(true);
                }
            }
        }

        SECTION("Not putting in a properly formatted command") {
            command = {"./executetrain/threebythreeimages/threebythreemodelssave/newtestfile"};
            SECTION("Create model in new file") {
                try {
                    mainExecutor.DetermineCommand(command);
                } catch (std::runtime_error error) {
                    REQUIRE(true);
                }
            }
        }

    }
}