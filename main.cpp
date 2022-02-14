#include <iostream>

void wordleUtilController(std::string filename);

/*
 * Entry point for Wordle solver program.
 * Starts up by calling the controller with the filename given on the
 * commandline. If the wrong number of arguments are given prints a usage message.
 */
int main (int argc, char * argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./wordle-util filename\n";
        return 1;
    }

    wordleUtilController(std::string(argv[1]));
}