# Advanced Software Engineering Lab 2: Calculator
This is a calculator software written in C++ that evaulates basic mathematical expressions. The use of parenthesis and curly brackets is supported as well as the use of real numbers. The calculator uses the Shunting-Yard Algorithm to handle operator precedence and expression evaluation.

## Features
- Supported Operations:
  - Arithmetic: `+`, `-`, `*`, `/`, `^` (exponentiation).
  - Trigonometric: `sin`, `cos`, `tan`, `cot`.
  - Logarithmic: `ln`, `log10`.
-  Grouping: Supports the use of parentheses `()` and curly brackets `{}`.
-  Error Handling: Detects and reports invalid expressions (e.g., mismatched brackets, invalid operator placement).
-  Continuous Input: Allows the user to enter multiple expressions until `-1` is entered to exit.

## How to Compile and Run
- Use a C++ compiler (e.g. g++) 
- Save the provided Calculator.cpp file to your machine
- Open the command prompt
- Navigate to the directory where you saved "Calculator.cpp"
- Run the following command to compile the code
  " g++ calculator.cpp -o calculator -lm "
    *This generates the needed executable file*
- Now enter the following command to run the executable
  " ./calculator "
- This should start up the executable and prompt you to enter an expression

  ## Examples of Valid Imputs
  - '2 + 3 * (4 - 1)' -> Result: '11'
  - '{2 + 5} * 4' -> Result: '28'
  - '2^3 + log10(100)' -> Result: '10'
 
  ## Examples of Invalid Inputs
  - '(2 - 3) + sin(45' -> Error: 'Invlaid expression (mismatched brackets or inlvaid operator placement)
  - '2 +/ 3' -> Error: 'Invlaid expression (mismatched brackets or inlvaid operator placement)
  - 'ln(-1)' -> Error: 'Invlaid expression (mismatched brackets or inlvaid operator placement)

  ## Author
  - Jamie Almeida
