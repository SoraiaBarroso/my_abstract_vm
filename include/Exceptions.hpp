#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

    // exception classes inherit from std::exception
    #include <exception>
    #include <string>

    class DivisionByZero : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Division by zero.";
            }
    };

    class NoExitInstruction : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Missing 'exit' instruction";
            }
    };

    class InvalidFile : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Invalid file";
            }
    };

    // push, div...
    class InvalidInstruction : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Invalid Instruction Type encountered.";
            }
    };

    // int8 int32...
    class InvalidOperandType : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Invalid Operand Type encountered.";
            }
    };

    class Overflow : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Overflow occurred.";
            }
    };

    class Underflow : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Underflow occurred.";
            }
    };

    class EmptyStack : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Attempted to pop from an empty stack.";
            }
    };

    class LessThanTwoValues : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Less than two values on the stack for arithmetic operation.";
            }
    };

    class AssertError : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Error: Assertion failed.";
            }
    };
#endif