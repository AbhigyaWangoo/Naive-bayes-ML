//
// Created by Abhigya Wangoo on 10/15/20.
//

#include <core/main_executor.h>

namespace naivebayes {
    void MainExecutor::DetermineCommand(std::vector<std::string> argv) {
        if (argv.size() == 5 || argv.size() == 7) {
            std::string command = argv[0];
            std::string second_command = argv[3];

            transform(command.begin(), command.end(), command.begin(), ::toupper);
            transform(second_command.begin(), second_command.end(), second_command.begin(), ::toupper);

            if (command == kTrain && second_command == kSave) {
                std::string file_image = argv[1];
                std::string file_label = argv[2];
                std::string file_save = argv[4];
                try {
                    std::ifstream ifs_images;
                    std::ifstream ifs_labels;

                    ifs_images.open(file_image);
                    ifs_labels.open(file_label);

                    naivebayes::Classifier classifier;

                    ifs_images >> classifier;
                    ifs_labels >> classifier;

                    classifier.InitializeModel(file_save);

                    if (argv.size() == 7 && argv[6] == kTest) {
                        PrintSuccessRate(classifier);
                    }
                } catch (std::runtime_error &) {
                    throw std::runtime_error("Oops! Invalid file or formatting");
                }
            } else if (command == kTrain && second_command == kTest) {
                std::string file_image = argv[1];
                std::string file_label = argv[2];
                std::string file_to_classify = argv[4];

                try {
                    std::ifstream ifs_images;
                    std::ifstream ifs_labels;

                    ifs_images.open(file_image);
                    ifs_labels.open(file_label);

                    naivebayes::Classifier classifier;

                    ifs_images >> classifier;
                    ifs_labels >> classifier;

                    PrintSuccessRate(classifier);
                } catch (std::runtime_error error) {
                    std::cout << error.what() << std::endl;
                }
            } else {
                throw std::runtime_error("Oops! You inputted an incorrect command");
            }
        } else {
            throw std::runtime_error("Oops! You inputted too many or too few arguments");
        }
    }

    void MainExecutor::PrintSuccessRate(Classifier &classifier) const {
        double total_events = 0;
        double correct_classifications = 0;

        for (const Image &image : classifier.get_images()) {
            if (classifier.DetermineImageLabel(image) == image.get_assigned_class()) {
                correct_classifications++;
            }
            total_events++;
        }

        std::cout << (correct_classifications / total_events) << std::endl;
    }
}