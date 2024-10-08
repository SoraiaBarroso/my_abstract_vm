#include "../include/MyAbstractVm.hpp"
#include "../include/InstructionParser.hpp"
#include "../include/IOperand.hpp"
#include "../include/Exceptions.hpp"

// map of available instructions
InstructionParser::InstructionParser() {
    instructionTypeMap = {
        {"push", Push}, {"pop", Pop}, {"dump", Dump}, 
        {"assert", Assert}, {"add", Add}, {"sub", Sub}, 
        {"mul", Mul}, {"div", Div}, {"mod", Mod},
        {"print", Print}, {"exit", Exit}, {";", Nil},
    };
}

// divide input into tokens = ['push', 'int8(42)']
std::vector<std::string> InstructionParser::parseInstructions(const std::string& str) {
    try {
        instructions.clear();

        size_t start = 0;
        size_t end = str.find(' ');

        // get instruction
        while (end != std::string::npos) {
            instructions.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(' ', start);
        }

        instructions.push_back(str.substr(start, end));

        validateInstruction();

        if (instructions.size() > 1) {
            divideOperand();
        }

        return instructions;
    } catch (const std::exception& e) {
        throw;  // Rethrow exception to be caught at a higher level (in main)
    }
}

bool InstructionParser::hasInstructionExit(std::string &fileName) const {
    std::ifstream infile(fileName);
    std::string line;

    while (std::getline(infile, line)) {
        line = line.substr(0, line.find(";"));

        if (line.find("exit") != std::string::npos) {
            return true;
        }   
    }

    return false;
}

bool InstructionParser::isValidOperandValue(const std::string& value) const {
    if (value.empty()) {
        return false;
    }

    bool hasDot = false;

    // Check each character in the value
    for (size_t j = 0; j < value.length(); j++) {
        if (j == 0 && value[j] == '-') {
            continue;
        }
        // decimal values
        if (value[j] == '.') {
            if (hasDot) {
                return false; 
            }
            hasDot = true;
        } else if (!isdigit(value[j])) {
            return false;
        }
    }

    return true;
}

// divide operant in type and value = ['int8', '42']
void InstructionParser::divideOperand() {
    std::string operand = instructions.at(1);
    size_t i;

    for (i = 0; i < operand.size(); i++) {
        if (operand.at(i) == '(') {
            instructions.at(1) = operand.substr(0, i);
            break;
        }
    }

    size_t endPos = operand.find(')', i);
    // Extract the value (e.g., '32')
    if (endPos != std::string::npos) {
        std::string value = operand.substr(i + 1, endPos - i - 1); 
        instructions.push_back(value); 

        // Validate the extracted value
        if (!isValidOperandValue(value)) {
            throw InvalidOperandType();
        }
    } else {
        throw InvalidOperandType(); 
    }
}

void InstructionParser::validateInstruction() {
    if (instructions.empty()) {
        std::cerr << "Unable to parse the input" << std::endl;
        return;
    }

    // treat empty input as a comment
    if (instructions.at(0).empty()) {
        instructions.clear();
        instructions.push_back(";");
        return;
    }

    // when input starts with a semicolon...
    if (instructions.at(0).at(0) == ';') {
        // and the next symbol is a semicolon as well, treat as exit
        if (instructions.at(0).size() > 1 && instructions.at(0).at(1) == ';') {
            instructions.clear();
            instructions.push_back("exit");
        }
        // disregard the rest, treat as a comment
        else {
            instructions.clear();
            instructions.push_back(";");
        }
        return;
    }

    if (instructionTypeMap.find(instructions.at(0)) == instructionTypeMap.end()) {
        throw InvalidInstruction();
    }
}

void InstructionParser::printInstructions() const {
    for (const auto& instruction : instructions) {
        std::clog << instruction << std::endl;
    }
}

// return enum values to use it as index for creating the right operand
eOperandType InstructionParser::getOperandType() const {
    if (instructions.at(1) == "int8") {
        return Int8; // 0
    } else if (instructions.at(1) == "int16") {
        return Int16; // 1
    } else if (instructions.at(1) == "int32") {
        return Int32; // 2
    } else if (instructions.at(1) == "float") {
        return Float; // 3
    } else if (instructions.at(1) == "double") {
        return Double; // 4
    } else {
        throw InvalidOperandType();
    }
}


eInstructionType InstructionParser::getInstructionType() const {
    auto it = instructionTypeMap.find(instructions.at(0));

    if (it != instructionTypeMap.end()) {
        return it->second;
    } else {
        throw InvalidInstruction();
    }
}

void InstructionParser::processLine(std::string& line, InstructionParser& parser, MyAbstractVM& vm) {
    try {
        std::vector<std::string> instructionsParsed = parser.parseInstructions(line);

        eOperandType opType;
        eInstructionType instruction;

        // get instruction type, e.g., Push
        instruction = parser.getInstructionType();

        // get operand type, e.g., Int8
        if (instructionsParsed.size() > 1) {
            opType = parser.getOperandType();
        }

        // Process the instruction
        switch (instruction) {
            case Push:
                vm.push(instructionsParsed.at(2), opType);
                break;
            case Dump:
                vm.dump();
                break;
            case Pop:
                vm.pop();
                break;
            case Assert:
                vm.assert(opType, instructionsParsed.at(2));
                break;
            case Exit:
                vm.exitProgram();
                break;
            case Add:
                vm.add();
                break;
            case Sub:
                vm.sub();
                break;
            case Mul:
                vm.mul();
                break;
            case Div:
                vm.div();
                break;
            case Mod:
                vm.mod();
                break;
            case Print:
                vm.print();
                break;
            default:
                break;
        }
    } catch (const std::exception& e) {
        throw;  
    }
}