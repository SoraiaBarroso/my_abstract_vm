#include "../include/MyAbstractVm.hpp"
#include "../include/InstructionParser.hpp"

int main(int argc, char* argv[]) {
    InstructionParser parser;
    MyAbstractVM vm;

    std::string line;

    try {
        // File given as argument
        if (argc > 1) {
            std::string fileName = argv[1];

            std::ifstream infile(argv[1]);
            if (!infile) {
                throw InvalidFile();
            }

            if (!parser.hasInstructionExit(fileName)) {
                throw NoExitInstruction();
            }

            while (std::getline(infile, line)) {
                parser.processLine(line, parser, vm);
            }
        } 
        // Handle standard input (stdin)
        else {
            while (true) {
                if (!std::getline(std::cin, line)) break;
                parser.processLine(line, parser, vm);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS;
}