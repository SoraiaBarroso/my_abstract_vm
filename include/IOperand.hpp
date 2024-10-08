#ifndef IO_OPERAND_H
#define IO_OPERAND_H

    #include <string.h>
    #include <iostream>
    #include <math.h>
    #include <limits>
    #include "./Exceptions.hpp"

    enum eOperandType { Int8, Int16, Int32, Float, Double };

    // Each of the operand classes implement the following IOperand interface
    class IOperand {
        public:
            //  virtual is a member function that is declared within a base class and is re-defined (overridden) by a derived class
            virtual std::string const&    toString() const = 0;

            virtual int                   getPrecision() const = 0;
            virtual eOperandType          getType() const = 0;

            virtual IOperand*             operator+(const IOperand &rhs) const = 0;
            virtual IOperand*             operator-(const IOperand &rhs) const = 0;
            virtual IOperand*             operator*(const IOperand &rhs) const = 0;
            virtual IOperand*             operator/(const IOperand &rhs) const = 0;
            virtual IOperand*             operator%(const IOperand &rhs) const = 0;

            virtual                       ~IOperand() {}
    };

    class Int8 : public IOperand
    {
        public:
            Int8() : _value(0) {};

            ~Int8() {};

            Int8(std::string& value) {
                int parsed = std::stoi(value);

                if (parsed < std::numeric_limits<int8_t>::min()) {
                    throw Underflow();
                } else if ( parsed > std::numeric_limits<int8_t>::max() ) {
                    throw Overflow();
                }

                _value = static_cast<int8_t>(parsed);
                _strValue = value;
            };

            IOperand* operator+(const IOperand& rhs) const override {
                int resultValue = _value + static_cast<int8_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int8_t>::min() || std::numeric_limits<int8_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int8(resultStr);
            }

            IOperand* operator-(const IOperand& rhs) const override {
                int resultValue = _value - static_cast<int8_t>(std::stoi(rhs.toString()));

                 // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int8_t>::min() || std::numeric_limits<int8_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int8(resultStr);
            }

            IOperand* operator/(const IOperand& rhs) const override {
                int resultValue = _value / static_cast<int8_t>(std::stoi(rhs.toString()));

                 // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int8_t>::min() || std::numeric_limits<int8_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int8(resultStr);
            }

            IOperand* operator%(const IOperand& rhs) const override {
                int resultValue = _value % static_cast<int8_t>(std::stoi(rhs.toString()));

                 // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int8_t>::min() || std::numeric_limits<int8_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int8(resultStr);
            }

            IOperand* operator*(const IOperand& rhs) const override {
                int resultValue = _value * static_cast<int8_t>(std::stoi(rhs.toString()));

                 // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int8_t>::min() || std::numeric_limits<int8_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int8(resultStr);
            };

            std::string getValue() {
                return this->_strValue;
            }

        private:
            std::string           _strValue;
            int8_t                _value;
            std::string const&    toString(void) const override { return _strValue; }
            eOperandType          getType(void) const override { return eOperandType::Int8; }

            /*
                The method pure getPrecision of the interface IOperand
                allows to get the precision of an operand. When an operation use two operands
                from two different types, the comparison of theirs precisions allows to figure out
                the result type of the operation.
            */
            int                   getPrecision(void) const override { return eOperandType::Int8; }
    };


    class Int16 : public IOperand
    {
        public:
            Int16() : _value(0) {};

            ~Int16() {};

            Int16(std::string& value) {
                try {
                    _value = static_cast<int16_t>(std::stoi(value));
                    _strValue = value;
                } catch (const std::out_of_range &ex) {
                    throw Overflow();
                } 
            };

            IOperand* operator+(const IOperand& rhs) const override {

                int resultValue = _value + static_cast<int16_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int16_t>::min() || std::numeric_limits<int16_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int16(resultStr);
            }

            IOperand* operator-(const IOperand& rhs) const override {
                int resultValue = _value - static_cast<int16_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int16_t>::min() || std::numeric_limits<int16_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int16(resultStr);
            }

            IOperand* operator/(const IOperand& rhs) const override {
                int resultValue = _value / static_cast<int16_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int16_t>::min() || std::numeric_limits<int16_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int16(resultStr);
            }

            IOperand* operator%(const IOperand& rhs) const override {
                 int resultValue = _value % static_cast<int16_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int16_t>::min() || std::numeric_limits<int16_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int16(resultStr);
            }

            IOperand* operator*(const IOperand& rhs) const override {
                int resultValue = _value * static_cast<int16_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int16_t>::min() || std::numeric_limits<int16_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int16(resultStr);
            };

            std::string getValue() {
                return this->_strValue;
            }

        private:
            std::string           _strValue;
            int16_t               _value;
            std::string const&    toString(void) const override { return _strValue; }
            eOperandType          getType(void) const override { return eOperandType::Int16; }

            int                   getPrecision(void) const override { return eOperandType::Int16; }
    };

    class Int32 : public IOperand
    {
        public:
            Int32() : _value(0) {};

            ~Int32() {};

            Int32(std::string& value) {
                try {
                    _value = static_cast<int32_t>(std::stol(value));
                    _strValue = value;
                } catch (const std::out_of_range &ex) {
                    throw Overflow();
                } 
            };

            IOperand* operator+(const IOperand& rhs) const override {
                int resultValue = _value + static_cast<int32_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int32_t>::min() || std::numeric_limits<int32_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int32(resultStr);
            }

            IOperand* operator-(const IOperand& rhs) const override {
                int resultValue = _value - static_cast<int32_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int32_t>::min() || std::numeric_limits<int32_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int32(resultStr);
            }

            IOperand* operator/(const IOperand& rhs) const override {
                 int resultValue = _value / static_cast<int32_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int32_t>::min() || std::numeric_limits<int32_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int32(resultStr);
            }

            IOperand* operator%(const IOperand& rhs) const override {
                int resultValue = _value % static_cast<int32_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int32_t>::min() || std::numeric_limits<int32_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int32(resultStr);
            }

            IOperand* operator*(const IOperand& rhs) const override {
                int resultValue = _value * static_cast<int32_t>(std::stoi(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<int32_t>::min() || std::numeric_limits<int32_t>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Int32(resultStr);
            };

            std::string getValue() {
                return this->_strValue;
            }

        private:
            std::string           _strValue;
            int32_t               _value;
            std::string const&    toString(void) const override { return _strValue; }
            eOperandType          getType(void) const override { return eOperandType::Int32; }

            int                   getPrecision(void) const override { return eOperandType::Int32; }
    };

    class Float : public IOperand
    {
        public:
            Float() : _value(0) {};

            ~Float() {};

            Float(std::string& value) {
                try {
                    _value = static_cast<float_t>(std::stof(value));
                    _strValue = value;

                } catch (const std::out_of_range &ex) {
                    throw Overflow();
                } 
            };

            IOperand* operator+(const IOperand& rhs) const override {
                float resultValue = _value + static_cast<float_t>(std::stof(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<float>::min() || std::numeric_limits<float>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Float(resultStr);
            }

            IOperand* operator-(const IOperand& rhs) const override {
                float resultValue = _value - static_cast<float_t>(std::stof(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<float>::min() || std::numeric_limits<float>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Float(resultStr);
            }

            IOperand* operator/(const IOperand& rhs) const override {
                float resultValue = _value / static_cast<float_t>(std::stof(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<float>::min() || std::numeric_limits<float>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Float(resultStr);
            }

            IOperand* operator%(const IOperand& rhs) const override {
                // Computes the floating-point remainder of the division
                float resultValue = std::fmod(_value, static_cast<float>(std::stof(rhs.toString())));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<float>::min() || std::numeric_limits<float>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Float(resultStr);
            }

            IOperand* operator*(const IOperand& rhs) const override {
                float resultValue = _value * static_cast<float_t>(std::stof(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<float>::min() || std::numeric_limits<float>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Float(resultStr);
            };

            std::string getValue() {
                return this->_strValue;
            }

        private:
            std::string           _strValue;
            float_t               _value;
            std::string const&    toString(void) const override { return _strValue; }
            eOperandType          getType(void) const override { return eOperandType::Float; }

            int                   getPrecision(void) const override { return eOperandType::Float; }
    };

    class Double : public IOperand
    {
        public:
            Double() : _value(0) {};

            ~Double() {};

            explicit Double(std::string& value) {
                try {
                    _value = static_cast<double_t>(std::stod(value));
                    _strValue = value;
                } catch (const std::out_of_range &ex) {
                    throw Overflow();
                } 
            };

            IOperand* operator+(const IOperand& rhs) const override {
                double resultValue = _value + static_cast<double_t>(std::stod(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<double>::min() || std::numeric_limits<double>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Double(resultStr);
            }

            IOperand* operator-(const IOperand& rhs) const override {
                double resultValue = _value - static_cast<double_t>(std::stod(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<double>::min() || std::numeric_limits<double>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Double(resultStr);
            }

            IOperand* operator/(const IOperand& rhs) const override {
                double resultValue = _value / static_cast<double_t>(std::stod(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<double>::min() || std::numeric_limits<double>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Double(resultStr);
            }

            IOperand* operator%(const IOperand& rhs) const override {
                // Computes the floating-point remainder of the division
                double resultValue = std::fmod(_value, static_cast<double>(std::stod(rhs.toString())));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<double>::min() || std::numeric_limits<double>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Double(resultStr);
            }

            IOperand* operator*(const IOperand& rhs) const override {
                double resultValue = _value * static_cast<double_t>(std::stod(rhs.toString()));

                // Check for overflow/underflow
                if (resultValue < std::numeric_limits<double>::min() || std::numeric_limits<double>::max() < resultValue) {
                    throw Overflow();
                }

                std::string resultStr = std::to_string(resultValue);
                return new Double(resultStr);
            };

            std::string getValue() {
                return this->_strValue;
            }

        private:
            std::string           _strValue;
            double_t              _value;
            std::string const&    toString(void) const override { return _strValue; }
            eOperandType          getType(void) const override { return eOperandType::Double; }

            int                   getPrecision(void) const override { return eOperandType::Double; }
    };
#endif
