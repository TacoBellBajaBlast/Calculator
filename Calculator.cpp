#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <sstream>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to check if a character is a unary operator
bool isUnaryOperator(char c) {
    return c == '-';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '^') return 4;
    if (op == '*' || op == '/') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

// Function to apply an operator to two operands
double applyOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw invalid_argument("Division by zero");
        return a / b;
    case '^': return pow(a, b);
    default: throw invalid_argument("Invalid operator");
    }
}

// Function to validate the expression
bool validateExpression(const string& expression) {
    stack<char> parentheses;
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == '(') {
            parentheses.push(c);
        }
        else if (c == ')') {
            if (parentheses.empty() || parentheses.top() != '(') {
                return false; // Mismatched parenthesis
            }
            parentheses.pop();
        }
        // Check for invalid operator sequences
        if (isOperator(c) && i + 1 < expression.length() && isOperator(expression[i + 1])) {
            return false; // Two operators in a row
        }
    }
    return parentheses.empty(); // Ensure all parentheses are matched
}

// Function to evaluate a mathematical expression
double evaluateExpression(const string& expression) {
    stack<double> values;
    stack<char> operators;

    for (size_t i = 0; i < expression.length(); i++) {
        // Skip whitespace
        if (isspace(expression[i])) continue;

        // Handle numbers
        if (isdigit(expression[i]) || expression[i] == '.') {
            stringstream ss;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i++];
            }
            i--; // Move back one step after the loop
            double value;
            ss >> value;
            values.push(value);
        }
        // Handle opening parenthesis
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }
        // Handle closing parenthesis
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperation(a, b, op));
            }
            if (operators.empty()) {
                throw invalid_argument("Mismatched parentheses");
            }
            operators.pop(); // Remove the '(' from the stack
        }
        // Handle operators
        else if (isOperator(expression[i])) {
            // Handle unary minus
            if (expression[i] == '-' && (i == 0 || expression[i - 1] == '(' || isOperator(expression[i - 1]))) {
                values.push(0); // Push 0 to handle unary minus
            }
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(expression[i])) {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(expression[i]);
        }
        // Handle trigonometric and logarithmic functions
        else if (isalpha(expression[i])) {
            string func;
            while (i < expression.length() && isalpha(expression[i])) {
                func += expression[i++];
            }
            i--; // Move back one step after the loop

            // Expect an opening parenthesis after the function name
            if (expression[i + 1] != '(') {
                throw invalid_argument("Invalid function syntax");
            }

            // Evaluate the argument of the function
            i += 2; // Skip the function name and '('
            stringstream ss;
            while (i < expression.length() && expression[i] != ')') {
                ss << expression[i++];
            }
            double arg = evaluateExpression(ss.str());

            // Apply the function
            if (func == "sin") {
                values.push(sin(arg));
            }
            else if (func == "cos") {
                values.push(cos(arg));
            }
            else if (func == "tan") {
                values.push(tan(arg));
            }
            else if (func == "cot") {
                values.push(1.0 / tan(arg));
            }
            else if (func == "ln") {
                values.push(log(arg));
            }
            else if (func == "log10") {
                values.push(log10(arg));
            }
            else {
                throw invalid_argument("Unknown function");
            }
        }
    }

    // Evaluate remaining operators
    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw invalid_argument("Mismatched parentheses");
        }
        char op = operators.top();
        operators.pop();
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        values.push(applyOperation(a, b, op));
    }

    // The final result is the only value left in the stack
    if (values.size() != 1) {
        throw invalid_argument("Invalid expression");
    }
    return values.top();
}

int main() {
    string expression;
    while (true) {
        cout << "\nEnter a mathematical expression (or enter -1 to exit): ";
        getline(cin, expression);

        // Check if the user wants to exit
        if (expression == "-1") {
            cout << "Exiting the calculator. Goodbye!" << endl;
            break;
        }

        // Validate the expression before evaluating
        if (!validateExpression(expression)) {
            cerr << "Error: Invalid expression (mismatched parentheses or invalid operator placement)" << endl;
            continue;
        }

        try {
            double result = evaluateExpression(expression);
            cout << "Result: " << result << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}