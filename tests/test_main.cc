#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <core/main_executor.h>

TEST_CASE("Testing CLI") {
    naivebayes::MainExecutor mainExecutor;

    SECTION("Ensure command is properly followed") {
        char **command = (char **) "./execute train /Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-"
                                   "AbhiWangoo/data/testingdata/threebythreeimages /Users/abhigyawangoo/CLionProjects/"
                                   "Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreemodels save "
                                   "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data"
                                   "/testingdata/newtestfile";

        SECTION("Create model in new file") {
            try {
                mainExecutor.DetermineCommand(6, command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                REQUIRE(false);
            }
        }

        SECTION("Create model from existing file") {
            try {
                mainExecutor.DetermineCommand(6, command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                REQUIRE(false);
            }
        }

        SECTION("Command is of not all lowercase") {
            char **invalid_format_command = (char **) "./execute tRAIN /Users/abhigyawangoo/CLionProjects/CINDer/my-projects/naivebayes-"
                                                      "AbhiWangoo/DATa/testingdata/threebythreeimages /Users/abhigyawangoo/CLionProjects/"
                                                      "Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreemodels SAVE "
                                                      "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data"
                                                      "/testingdata/NEWtestfile";
            try {
                mainExecutor.DetermineCommand(6, invalid_format_command);
                REQUIRE(true);
            } catch (std::runtime_error error) {
                REQUIRE(false);
            }
        }
    }

    SECTION("Failed command inputs") {
        SECTION("Not putting in a file for images") {
            try {
                char **command = (char **) "train a /Users/abhigyawangoo/CLionProjects/Cinder/"
                                           "my-projects/naivebayes-AbhiWangoo/data/testingdata/"
                                           "threebythreemodels save /Users/abhigyawangoo/CLionProjects/"
                                           "Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/"
                                           "newtestfile";

                mainExecutor.DetermineCommand(6, command);
            } catch (std::runtime_error error) {
                REQUIRE(true);
            }
        }

        SECTION("Not putting in a file for labels") {
            try {
                char **command = (char **) "train /Users/abhigyawangoo/CLionProjects/CINDer"
                                           "/my-projects/naivebayes-AbhiWangoo/DATa/testingdata/"
                                           "threebythreeimages /Users/abhigyawangoo/CLionProjects/Cinder/"
                                           "save /Users/abhigyawangoo/CLionProjects/Cinder/my-projects"
                                           "/naivebayes-AbhiWangoo/data/testingdata/newtestfile";

                mainExecutor.DetermineCommand(6, command);
            } catch (std::runtime_error error) {
                REQUIRE(true);
            }
        }

        SECTION("Not putting in a train command") {
            try {
                char **command = (char **) "a /Users/abhigyawangoo/CLionProjects/CINDer"
                                           "/my-projects/naivebayes-AbhiWangoo/DATa/testingdata/"
                                           "threebythreeimages /Users/abhigyawangoo/CLionProjects/Cinder/"
                                           "save /Users/abhigyawangoo/CLionProjects/Cinder/my-projects"
                                           "/naivebayes-AbhiWangoo/data/testingdata/newtestfile";

                mainExecutor.DetermineCommand(6, command);
            } catch (std::runtime_error error) {
                REQUIRE(true);
            }
        }

        SECTION("Not putting in a save command") {
            char **command = (char **) "./execute train /Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-"
                                       "AbhiWangoo/data/testingdata/threebythreeimages /Users/abhigyawangoo/CLionProjects/"
                                       "Cinder/my-projects/naivebayes-AbhiWangoo/data/testingdata/threebythreemodels s "
                                       "/Users/abhigyawangoo/CLionProjects/Cinder/my-projects/naivebayes-AbhiWangoo/data"
                                       "/testingdata/newtestfile";
            std::ifstream ifs;
            SECTION("Create model in new file") {
                try {
                    mainExecutor.DetermineCommand(6, command);
                } catch (std::runtime_error error) {
                    REQUIRE(true);
                }
            }
        }

        SECTION("Not putting in a properly formatted command") {
            char **command = (char **) "./executetrain/threebythreeimages/threebythreemodelssave/newtestfile";
            std::ifstream ifs;
            SECTION("Create model in new file") {
                try {
                    mainExecutor.DetermineCommand(6, command);
                } catch (std::runtime_error error) {
                    REQUIRE(true);
                }
            }
        }

    }
}