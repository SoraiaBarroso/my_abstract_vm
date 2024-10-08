#ifndef MY_ABSTRACT_VM_H
#define MY_ABSTRACT_VM_H

    #include "./IOperand.hpp"
    #include "./Exceptions.hpp"
    #include <iostream>
    #include <stack>
    #include <stdio.h>
    #include <vector>
    #include <string.h>
    #include <map>
    #include <float.h>
    #include <math.h>
    #include <functional>
    #include <fstream>
    #include <exception>
    
    // Instructions that we can use to create the different variables
    enum eInstructionType { Push, Pop, Dump, Assert, Add, Sub, Mul, Div, Mod, Print, Exit, Nil };

    // Class to create the operands
    class OperandFactory {
        public:
            IOperand* createOperand(eOperandType type, std::string& value) {
                return (this->*createFuncs[type])(value);
            }

            IOperand* createInt8(std::string& value) {
                return new class Int8(value);
            }

            IOperand* createInt16(std::string& value) {
                return new class Int16(value);
            };

            IOperand* createInt32(std::string& value){
                return new class Int32(value);
            };

            IOperand* createFloat(std::string& value){
                return new class Float(value);
            };

            IOperand* createDouble(std::string& value){
                return new class Double(value);
            };

        private:
            // In order to choose the right member function for the creation of the new IOperand, you MUST create and use an array of pointers on member functions with enum values as index.
            using CreateOperand = IOperand* (OperandFactory::*)(std::string&);

            // Array indices point (or jump) to the functions assigned to them.
            CreateOperand createFuncs[5] = {
                &OperandFactory::createInt8,
                &OperandFactory::createInt16,
                &OperandFactory::createInt32,
                &OperandFactory::createFloat,
                &OperandFactory::createDouble,
            };
    };

    // Class that implement a stack and use the different math operations to create, store and use the different variables that we can now create
    class MyAbstractVM {
        public:
            MyAbstractVM() {}

            void push(std::string& value, eOperandType type) {
                stack.push(factory.createOperand(type, value));
            };

            void pop() {
                if (stack.empty()) {
                    throw EmptyStack();
                } else {
                    stack.pop();
                }
            }

            /*
                Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack.
                Each value is separated from the next one by a newline.
            */
            void dump() const {
                std::stack<IOperand*> temp = stack;

                while(!temp.empty()) {
                    IOperand* value = temp.top();
                    std::cout << value->toString() << std::endl;
                    temp.pop();
                }
            }

            /*
                Verifies that the value at the top of the stack is equal to the one passed as parameter for this instruction.
                If it is not the case, the program execution must stop with an error.
            */
            void assert(eOperandType opType, std::string& value) const {
                std::stack<IOperand*> temp = stack;
                IOperand* topValue = temp.top();
                const std::string strValue = topValue->toString();

                if (!(value == strValue) && !(opType == topValue->getType())) {
                    throw AssertError();
                } 
            }

            /*
                Unstacks the first two values on the stack, adds them together and stacks the result.
                If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
            */
            void add() {
                // Check if there's enough values in stack
                if (!checkStackSize()) {
                    throw LessThanTwoValues();
                }

                // Get the top two elements
                IOperand* operand1 = stack.top();
                stack.pop();
                IOperand* operand2 = stack.top();
                stack.pop();

                IOperand* result = nullptr;

                try {
                    if (isSamePrecision(operand1, operand2)) {
                        result = *operand1 + *operand2;
                    } else {
                        result = handlePrecisionAndConvert(operand1, operand2, addOperands);
                    }
                } catch (const std::overflow_error &ex) {
                    delete operand1;
                    delete operand2;
                    throw Overflow();
                }

                stack.push(result);
                delete operand1;
                delete operand2;
            }

            /* Unstacks the first two values on the stack, subtracts them, then stacks the result */
            void sub() {
                if (!checkStackSize()) {
                    throw LessThanTwoValues();
                }

                // Get the top two elements
                IOperand* operand1 = stack.top();
                stack.pop();
                IOperand* operand2 = stack.top();
                stack.pop();

                IOperand* result = nullptr;

                try {
                    if (isSamePrecision(operand1, operand2)) {
                        result = *operand1 - *operand2;
                    } else {
                        result = handlePrecisionAndConvert(operand1, operand2, subOperands);
                    }
                } catch (const std::overflow_error &ex) {
                    delete operand1;
                    delete operand2;
                    throw Overflow();
                }

                stack.push(result);
                delete operand1;
                delete operand2;
            }

            void mul() {
                if (!checkStackSize()) {
                    throw LessThanTwoValues();
                }

                // Get the top two elements
                IOperand* operand1 = stack.top();
                stack.pop();
                IOperand* operand2 = stack.top();
                stack.pop();

                IOperand* result = nullptr;

                try {
                    if (operand1->toString() == "0" || operand2->toString() == "0") {
                        result = createHigherPrecisionZero(operand1, operand2);
                    } else if (isSamePrecision(operand1, operand2)) {
                        result = *operand1 * *operand2;
                    } else {
                        result = handlePrecisionAndConvert(operand1, operand2, mulOperands);
                    }
                } catch (const std::overflow_error &ex) {
                    delete operand1;
                    delete operand2;
                    throw Overflow();
                }

                stack.push(result);
                delete operand1;
                delete operand2;
            };

            void div() {
                if (!checkStackSize()) {
                    throw LessThanTwoValues();
                }

                // Get the top two elements
                IOperand* operand1 = stack.top();
                stack.pop();
                IOperand* operand2 = stack.top();
                stack.pop();

                if (operand2->toString() == "0" || operand1->toString() == "0") {
                    delete operand1;
                    delete operand2;
                    throw DivisionByZero();
                }

                IOperand* result = nullptr;

                try {
                    if (operand1->toString() == "0") {
                        result = createHigherPrecisionZero(operand1, operand2);
                    } else if (isSamePrecision(operand1, operand2)) {
                        result = *operand1 / *operand2;
                    } else {
                        result = handlePrecisionAndConvert(operand1, operand2, divOperands);
                    }
                } catch (const std::overflow_error &ex) {
                    delete operand1;
                    delete operand2;
                    throw Overflow();
                }

                stack.push(result);
                delete operand1;
                delete operand2;
            };

            void mod() {
                if (!checkStackSize()) {
                    throw LessThanTwoValues();
                }

                // Get the top two elements
                IOperand* operand1 = stack.top();
                stack.pop();
                IOperand* operand2 = stack.top();
                stack.pop();

                if (operand2->toString() == "0") {
                    delete operand1;
                    delete operand2;
                    throw DivisionByZero();
                }

                IOperand* result = nullptr;

                try {
                    if (isSamePrecision(operand1, operand2)) {
                        result = *operand1 % *operand2;
                    } else {
                        result = handlePrecisionAndConvert(operand1, operand2, modOperands);
                    }
                } catch (const std::overflow_error &ex) {
                    delete operand1;
                    delete operand2;
                    throw Overflow();
                }

                stack.push(result);
                delete operand1;
                delete operand2;
            }

            void print() const {
                if (stack.empty()) {
                    throw EmptyStack();
                }

                IOperand* operand = stack.top();
                int value = std::stoi(operand->toString());

                if (value <= std::numeric_limits<int8_t>::min() && value >= std::numeric_limits<int8_t>::max()) {
                    std::cerr << "Value out of range for 8-bit integer" << std::endl;
                    return;
                }

                int8_t int8Value = static_cast<int8_t>(value);
                std::cout << static_cast<char>(int8Value) << std::endl;
            }

            void exitProgram() const {
                std::cout << "Exiting program..." << std::endl;
                exit(0);
            }

        private:
            // Must contain ONLY pointers on the abstract type IOperand
            std::stack<IOperand*> stack;
            OperandFactory factory;

            // Functions for type of operations
            using OperationFunc = std::function<IOperand*(const IOperand&, const IOperand&)>;
            static IOperand* addOperands(const IOperand& op1, const IOperand& op2);
            static IOperand* subOperands(const IOperand& op1, const IOperand& op2);
            static IOperand* mulOperands(const IOperand& op1, const IOperand& op2);
            static IOperand* divOperands(const IOperand& op1, const IOperand& op2);
            static IOperand* modOperands(const IOperand& op1, const IOperand& op2);

            // Precision related functions
            IOperand*   getLowerPrecision(IOperand* type1, IOperand* type2) const;
            IOperand*   handlePrecisionAndConvert(IOperand* operand1, IOperand* operand2, OperationFunc operation);
            IOperand*   createHigherPrecisionZero(IOperand* operand1, IOperand* operand2);
            bool        isSamePrecision(IOperand* type1, IOperand* type2) const;

            // Helper
            bool        checkStackSize();
    };
#endif