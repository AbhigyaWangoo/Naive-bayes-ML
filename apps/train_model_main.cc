#include <core/main_executor.h>

std::vector<std::string> ArgsToVector(int size, char *argv[]) {
    std::vector<std::string> converted_args;

    for(size_t i = 1; i < size;i++){
        converted_args.push_back(argv[i]);
    }

    return converted_args;
}

int main(int argc, char *argv[]) {
    naivebayes::MainExecutor mainExecutor;

    mainExecutor.DetermineCommand(ArgsToVector(argc, argv));
    
    return 0;
}