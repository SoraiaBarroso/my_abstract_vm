#ifndef INSTRUCTION_PARSER_HPP
#define INSTRUCTION_PARSER_HPP

    #include "./MyAbstractVm.hpp"
    #include <string>
    #include <vector>
    #include <map>

    class InstructionParser {
    public:
        InstructionParser();

        std::vector<std::string> parseInstructions(const std::string& str);

        void divideOperand();

        void validateInstruction();

        void printInstructions() const;

        eOperandType getOperandType() const;

        eInstructionType getInstructionType() const;

        bool isValidOperandValue(const std::string& value) const;
        
        void processLine(std::string& line, InstructionParser& parser, MyAbstractVM& vm);
        
        bool hasInstructionExit(std::string& fileName) const;
    private:
        std::vector<std::string> instructions;
        std::map<std::string, eInstructionType> instructionTypeMap;
    };
#endif