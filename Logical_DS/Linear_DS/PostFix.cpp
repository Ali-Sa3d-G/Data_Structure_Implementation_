#include<iostream>
#include<stack>
#include<cmath>      // For pow() function
#include<cctype>     // For isdigit()
#include<string>

using namespace std;

// ======================== HELPER FUNCTIONS ========================

/**
 * Returns the precedence level of an operator
 * Higher number = higher precedence
 */
int getPrecedence(char op) {
    if (op == '^') return 3;      // Exponentiation (highest)
    if (op == '*' || op == '/') return 2;  // Multiplication/Division
    if (op == '+' || op == '-') return 1;  // Addition/Subtraction (lowest)
    return 0;  // Not an operator
}

/**
 * Checks if a character is a valid mathematical operator
 */
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// ======================== CONVERSION FUNCTION ========================

/**
 * Converts an infix expression (like "3+4") to postfix notation (like "3 4 +")
 *
 * Algorithm:
 * 1. If we see a number → add it to output
 * 2. If we see an operator → pop operators with higher or equal precedence from stack to output
 * 3. If we see '(' → push to stack
 * 4. If we see ')' → pop operators until '('
 */
string infixToPostfix(const string& infix) {
    string postfix = "";           // The result we'll build
    stack<char> operatorStack;     // Holds operators and parentheses

    for (char character : infix) {

        // Skip spaces completely
        if (character == ' ') continue;

        // CASE 1: Number (operand) - add directly to output
        if (isdigit(character)) {
            postfix += character;
            postfix += ' ';        // Add space to separate numbers
        }

        // CASE 2: Operator - handle precedence
        else if (isOperator(character)) {
            // Pop operators with HIGHER or EQUAL precedence from stack
            // EXCEPTION: '^' is right-associative, so we don't pop equal precedence
            while (!operatorStack.empty() &&
                operatorStack.top() != '(' &&
                getPrecedence(operatorStack.top()) >= getPrecedence(character) &&
                character != '^') {

                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            // Push the new operator onto stack
            operatorStack.push(character);
        }

        // CASE 3: Parentheses
        else {
            // Left parenthesis - push to stack
            if (character == '(') {
                operatorStack.push(character);
            }
            // Right parenthesis - pop until matching '('
            else if (character == ')') {
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    postfix += ' ';
                    operatorStack.pop();
                }
                // Pop the '(' itself (but don't add to output)
                if (!operatorStack.empty()) {
                    operatorStack.pop();
                }
            }
        }
    }

    // Pop any remaining operators from stack
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
    }

    return postfix;
}

// ======================== EVALUATION FUNCTION ========================

/**
 * Evaluates a postfix expression and returns the result
 *
 * Algorithm:
 * 1. Read tokens from left to right
 * 2. If token is a number → push onto stack
 * 3. If token is an operator → pop 2 numbers, apply operator, push result
 * 4. At the end, stack contains the final result
 */
double evaluatePostfix(string& postfix) {
    stack<double> valueStack;

    for (int i = 0; i < (int)postfix.size(); i++) {
        char currentChar = postfix[i];

        // Skip spaces
        if (currentChar == ' ')
            continue;

        // ===== CASE 1: Number =====
        if (isdigit(currentChar)) {
            double number = 0;

            // Read the complete number (handles multi-digit numbers)
            while (i < (int)postfix.size() && isdigit(postfix[i])) {
                number = number * 10 + (postfix[i] - '0');
                i++;
            }

            valueStack.push(number);
            i--;  // Adjust index because the loop incremented past the number
        }

        // ===== CASE 2: Operator =====
        else if (isOperator(currentChar)) {
            // Pop two numbers (order matters!)
            double rightOperand = valueStack.top(); valueStack.pop();
            double leftOperand = valueStack.top(); valueStack.pop();

            // Perform the operation
            double result;
            if (currentChar == '+') result = leftOperand + rightOperand;
            else if (currentChar == '-') result = leftOperand - rightOperand;
            else if (currentChar == '*') result = leftOperand * rightOperand;
            else if (currentChar == '/') result = leftOperand / rightOperand;
            else if (currentChar == '^') result = pow(leftOperand, rightOperand);

            // Push result back to stack
            valueStack.push(result);
        }
    }

    // Final result is the only item left in stack
    return valueStack.top();
}

// ======================== MAIN FUNCTION ========================

int main() {
    // Test cases covering various scenarios
    string testExpressions[] = {
        "3+4",                    // Simple addition
        "10-2*3",                 // Operator precedence: multiplication before subtraction
        "(1+2)*3",                // Parentheses override precedence
        "2^3^2",                  // Right-associative exponentiation: 2^(3^2) = 512
        "12+34",                  // Multi-digit numbers
        "(2+3)*(4+5)"             // Nested parentheses
    };

    cout << "=== INFIX TO POSTFIX CONVERTER & CALCULATOR ===\n\n";

    for (const string& infix : testExpressions) {
        string postfix = infixToPostfix(infix);
        double result = evaluatePostfix(postfix);

        cout << "Infix:   " << infix << endl;
        cout << "Postfix: " << postfix << endl;
        cout << "Result:  " << result << endl;
        cout << "----------------------------" << endl;
    }

    return 0;
}