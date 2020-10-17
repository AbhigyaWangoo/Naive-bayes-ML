//
// Created by Abhigya Wangoo on 10/15/20.
//

#include <core/main_executor.h>

namespace naivebayes {
    void MainExecutor::DetermineCommand(int argc, char **argv) {
        if (argc != 6) {
            throw std::runtime_error("Oops! You inputted too many or too few arguments");
        }
        std::string command = argv[1];
        std::string save_command = argv[4];
        
        if (command != kTrain || save_command != kSave) {
            throw std::runtime_error("Oops! You inputted an incorrect command");
        } else {
            std::string executable = argv[0];
            std::string file_image = argv[2];
            std::string file_label = argv[3];
            std::string file_save = argv[5];

            transform(command.begin(), command.end(), command.begin(), ::toupper);
            transform(save_command.begin(), save_command.end(), save_command.begin(), ::toupper);

            try {
                std::ifstream ifs_images;
                std::ifstream ifs_labels;

                ifs_images.open(file_image);
                ifs_labels.open(file_label);

                naivebayes::Classifier classifier;

                ifs_images >> classifier;
                ifs_labels >> classifier;

                classifier.InitializeModel(file_save);
            } catch (std::runtime_error error) {
                throw std::runtime_error("Oops! Invalid file or formatting");
            }
        }
    }
}