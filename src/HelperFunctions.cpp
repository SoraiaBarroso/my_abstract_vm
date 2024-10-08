#include "../include/MyAbstractVm.hpp"

bool MyAbstractVM::isSamePrecision(IOperand* type1, IOperand* type2) const {
    return type1->getPrecision() == type2->getPrecision();
}

IOperand* MyAbstractVM::getLowerPrecision(IOperand* type1, IOperand* type2) const {
    if (type1->getPrecision() > type2->getPrecision()) {
        return type2;
    } else {
        return type1;
    }
}

bool MyAbstractVM::checkStackSize() {
    if (stack.size() >= 2) {
        return true;
    }
    throw LessThanTwoValues();
    return false;
}

/* If operand are not the same precision compare them, change them and perform the operation */
IOperand* MyAbstractVM::handlePrecisionAndConvert(IOperand* operand1, IOperand* operand2, OperationFunc operation) {
    IOperand* result = nullptr;

    const IOperand* higherPrecisionOperand;
    const IOperand* lowerPrecisionOperand;

    if (operand1->getPrecision() > operand2->getPrecision()) {
        higherPrecisionOperand = operand1;
        lowerPrecisionOperand = operand2;
    } else {
        higherPrecisionOperand = operand2;
        lowerPrecisionOperand = operand1;
    }

    std::string lowerPrecisionValue = lowerPrecisionOperand->toString();
    IOperand* convertedOperand = factory.createOperand(higherPrecisionOperand->getType(), lowerPrecisionValue);

    result = operation(*higherPrecisionOperand, *convertedOperand);
    delete convertedOperand;

    return result;
}

IOperand* MyAbstractVM::createHigherPrecisionZero(IOperand* operand1, IOperand* operand2) {
    const IOperand* higherPrecisionOperand = operand1->getPrecision() > operand2->getPrecision() ? operand1 : operand2;
    return factory.createOperand(higherPrecisionOperand->getType(), (std::string &) "0");
}

IOperand* MyAbstractVM::addOperands(const IOperand& op1, const IOperand& op2) {
    return op1 + op2;
}

IOperand* MyAbstractVM::subOperands(const IOperand& op1, const IOperand& op2) {
    return op1 - op2;
}

IOperand* MyAbstractVM::mulOperands(const IOperand& op1, const IOperand& op2) {
    return op1 * op2;
}

IOperand* MyAbstractVM::divOperands(const IOperand& op1, const IOperand& op2) {
    return op1 / op2;
}

IOperand* MyAbstractVM::modOperands(const IOperand& op1, const IOperand& op2) {
    return op1 % op2;
}
