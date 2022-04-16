#include "init_program.h"

/**
 * @brief The main of the project.
 * @param argc Number of arguments when starting the program.
 * @param argv The arguments when starting the program.
 * @return Status of the program if it was executed successfully.
 */
int main(int argc, char *argv[]){
    InitProgram::start(argc, argv);
    return 0;
}
