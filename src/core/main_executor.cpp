//
// Created by Abhigya Wangoo on 10/15/20.
//

#include <core/main_executor.h>

namespace naivebayes {
    void MainExecutor::DetermineCommand(std::vector<std::string> argv) {
//        if(argv.size() == 5) {
//            LoadImagesAndCreateModel(argv);
//        } else if(argv.size() == 7) {
//            LoadImagesAndCreateModel(argv);
//            ClassifyImage(argv);
//        } else if(argv.size() == 2) {
//            ClassifyImage(argv);
//        }
//
//        

        if (argv.size() == 5) {
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
                } catch (std::runtime_error &) {
                    throw std::runtime_error("Oops! Invalid file or formatting");
                }
            } else if(command == kTrain && second_command == kTest) {
                std::string file_image = argv[1];
                std::string file_label = argv[2];
                std::string file_to_classify = argv[4];
                
                try{
                    std::ifstream ifs_images;
                    std::ifstream ifs_labels;
                    
                    ifs_images.open(file_image);
                    ifs_labels.open(file_label);

                    naivebayes::Classifier classifier;

                    ifs_images >> classifier;
                    ifs_labels >> classifier;
                    
                    double i = 0;
                    double correct_classifications = 0;
                    
                    for (const Image &image : classifier.get_images()) {
                        if(classifier.DetermineImageLabel(image) == image.get_assigned_class()){
                            correct_classifications++;
                        }
                        i++;
                    }
                    
                    std::cout << (correct_classifications / i) << std::endl;
                } catch(std::runtime_error error){
                    std::cout << error.what() << std::endl;
                    
                }
            } 
            else {
                throw std::runtime_error("Oops! You inputted an incorrect command");
            }
        }
        else if (argv.size() == 7) {
            
        }
        else {
            throw std::runtime_error("Oops! You inputted too many or too few arguments");
        }


//        Last week, you added functionality to parse command line arguments. This week, you will be extending your 
//        functionality to allow the user to choose whether to test their model.
//
//        Note that this means that the command line parsing you implemented last week must still work and that you 
//        must consider logical combinations of the options provided: for example, you need to handle the following cases 
//        (note that this isn’t a complete list of all the cases you must handle):
//


//        Allow the user to train the model only (logically, they would need to then save the model to a file or there 
//        wouldn’t be any point in training the model -- but we will leave how to handle cases like this to you)
//        
//        Allow the user to test a model they’ve loaded in
//        
//        Allow the user to train a model and test it
    }
}