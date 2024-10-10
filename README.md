# Welcome to My Abstract Vm
***

## Task
The challenge was to develop a virtual machine that can compute simple arithmetic expressions using a custom assembly language. The assembly language must support various data types, handle errors gracefully, and perform operations based on a stack structure.

## Description
To solve this problem, I created a virtual machine called **My Abstract VM**. It performs arithmetic operations, and manages a stack of operands. The virtual machine interprets a series of commands, ensuring that all operations respect the rules of type precision and stack management. The project includes robust error handling for invalid instructions, division by zero, doing operations without enough values on the stack, poping on empty stack, and stack underflows, ensuring that the machine operates without crashing. <br>

- **Data Types**: Supports various operand types, including:
  - `int8(n)`: 8-bit signed integers.
  - `int16(n)`: 16-bit signed integers.
  - `int32(n)`: 32-bit signed integers.
  - `float(z)`: Single-precision floating-point numbers.
  - `double(z)`: Double-precision floating-point numbers.


- **Stack Operations**: 
  - **push v**: Pushes a value onto the stack.
  - **pop**: Removes the top value from the stack (with error handling for empty stack).
  - **dump**: Displays the current stack contents without altering the stack.


- **Arithmetic Operations**: Supports basic arithmetic operations:
  - **add**: Adds the top two values on the stack.
  - **sub**: Subtracts the second top value from the top value.
  - **mul**: Multiplies the top two values.
  - **div**: Divides the second top value by the top value, with error handling for division by zero.
  - **mod**: Calculates the modulus of the second top value by the top value, also with division by zero error handling.


- **Assertions and Error Handling**:
  - **assert v**: Checks if the top value of the stack matches the provided value, raising an error if it does not.
  - **exit**: Terminates the program; if omitted, the program raises an error.


- **Comments**: Supports comments starting with `;`, which can be placed on their own lines or at the end of instructions.


- **Error Management**: Robust error handling is implemented for various edge cases:
  - Lexical and syntactical errors in the assembly code.
  - Division or modulo by zero.
  - Popping from an empty stack.
  - Performing arithmetic operations with fewer than two values on the stack.
  - Assertions that fail.

## Installation
Run `Make` and execute with `./my_abstract_vm`

## Usage
```
>./my_abstract_vm
push int32(42)
push int32(33)
add
assert int32(75)
pop
exit
```

```
>cat operation_1.avm
; -------------
; operation_1.avm -
; -------------

push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit
>./avm  ./operation_1.avm
42
42.42
3341.25
```
### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
