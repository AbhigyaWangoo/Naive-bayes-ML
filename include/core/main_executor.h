//
// Created by Abhigya Wangoo on 10/15/20.
//

#ifndef NAIVE_BAYES_MAIN_EXECUTOR_H
#define NAIVE_BAYES_MAIN_EXECUTOR_H

#include <iostream>
#include <fstream>
#include <map>
#include <core/classifier.h>
namespace naivebayes {
    /**
     * Main function parser
     */
    class MainExecutor {
    public:
        const std::string kTrain = "train";
        const std::string kSave = "save";
        
        /**
         * Determine action to take based on command line arguments
         * 
         * @param argc for the size of arguments 
         * @param argv for the arguments
         */
        void DetermineCommand(int argc, char **argv);
    };   
}


#endif //NAIVE_BAYES_MAIN_EXECUTOR_H
