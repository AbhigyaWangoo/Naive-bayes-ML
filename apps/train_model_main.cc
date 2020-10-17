#include <core/main_executor.h>

int main(int argc, char *argv[]) {
    naivebayes::MainExecutor mainExecutor;
    
    mainExecutor.DetermineCommand(argc, argv);
    
    return 0;
}
