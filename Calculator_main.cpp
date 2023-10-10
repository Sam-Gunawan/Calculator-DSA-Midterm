#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <vector>
#include "History.h"

using namespace std;

// Define a structure for a node in the linked list
struct Node {
    string data;
    Node* prev;
    Node* next;

    Node(const string& val) : data(val), prev(nullptr), next(nullptr) {}
};

// Function to insert a new node at the end of the linked list
void insertAtEnd(Node*& head, Node*& tail, const string& val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Function to evaluate a binary operator
double evaluateBinaryOperator(const string& op, double operand1, double operand2) {
    if (op == "+") {
        return operand1 + operand2;
    } else if (op == "-") {
        return operand1 - operand2;
    } else if (op == "*") {
        return operand1 * operand2;
    } else if (op == "/") {
        if (operand2 != 0) {
            return operand1 / operand2;
        } else {
            cout << "Error: Division by zero." << endl;
            return 0;
        }
    } else if (op == "^") {
        return pow(operand1, operand2);
    } else {
        cout << "Invalid operator: " << op << endl;
        return 0;
    }
}

// Function to prioritize operators in the linked list
double prioritizeOperators(Node* head, int* flag_ptr) {
    stack<string> operatorStack;
    stack<double> valueStack;  // Stack to store operand values

    while (head) {
        Node* current = head;
        head = head->next;

        if (current->data == "(") {
            operatorStack.push(current->data);
        } else if (isdigit(current->data[0])) {
            valueStack.push(stod(current->data));
        } else if (current->data == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                string op = operatorStack.top();
                operatorStack.pop();
                if (op == "sqrt" || op == "exp" || op == "log" || op == "ln" ||
                    op == "sin" || op == "cos" || op == "tan" ||
                    op == "asin" || op == "acos" || op == "atan") {
                    double operand2 = valueStack.top();
                    valueStack.pop();
                    double result;
                    if (op == "sqrt") {
                        if (operand2 >= 0) {
                            result = sqrt(operand2);
                        } else {
                            cout << "Error: Square root of a negative number." << endl;
                            return 0;
                        }
                    } else if (op == "exp") {
                        result = exp(operand2);
                    } else if (op == "log") {
                        if (operand2 > 0) {
                            result = log10(operand2);
                        } else {
                            cout << "Error: Logarithm of a non-positive number." << endl;
                            return 0;
                        }
                    } else if (op == "ln") {
                        if (operand2 > 0) {
                            result = log(operand2);
                        } else {
                            cout << "Error: Natural logarithm of a non-positive number." << endl;
                            return 0;
                        }
                    } else if (op == "sin") {
                        result = sin(operand2 * M_PI / 180.0); // Convert degrees to radians
                    } else if (op == "cos") {
                        result = cos(operand2 * M_PI / 180.0); // Convert degrees to radians
                    } else if (op == "tan") {
                        result = tan(operand2 * M_PI / 180.0); // Convert degrees to radians
                    } else if (op == "asin") {
                        result = asin(operand2) * 180.0 / M_PI; // Convert radians to degrees
                    } else if (op == "acos") {
                        result = acos(operand2) * 180.0 / M_PI; // Convert radians to degrees
                    } else if (op == "atan") {
                        result = atan(operand2) * 180.0 / M_PI; // Convert radians to degrees
                    }
                    valueStack.push(result);
                } else {
                    if (valueStack.size() < 2) {
                        cout << "Error: Insufficient operands for operator " << op << endl;
                        return 0;
                    }
                    double operand2 = valueStack.top();
                    valueStack.pop();
                    double operand1 = valueStack.top();
                    valueStack.pop();
                    double result = evaluateBinaryOperator(op, operand1, operand2);
                    valueStack.push(result);
                }
            }
            if (!operatorStack.empty() && operatorStack.top() == "(") {
                operatorStack.pop();
            } else {
                cout << "Error: Unmatched closing parenthesis." << endl;
                return 0;
            }
        } else if (current->data == "+" || current->data == "-" || current->data == "*" ||
                   current->data == "/" || current->data == "^" || current->data == "sqrt" ||
                   current->data == "exp" || current->data == "log" || current->data == "ln" ||
                   current->data == "sin" || current->data == "cos" || current->data == "tan" ||
                   current->data == "asin" || current->data == "acos" || current->data == "atan") {
            while (!operatorStack.empty() &&
                   (operatorStack.top() == "+" || operatorStack.top() == "-" || operatorStack.top() == "*" ||
                    operatorStack.top() == "/" || operatorStack.top() == "^" || operatorStack.top() == "sqrt" ||
                    operatorStack.top() == "exp" || operatorStack.top() == "log" || operatorStack.top() == "ln" ||
                    operatorStack.top() == "sin" || operatorStack.top() == "cos" || operatorStack.top() == "tan" ||
                    operatorStack.top() == "asin" || operatorStack.top() == "acos" || operatorStack.top() == "atan")) {
                string op = operatorStack.top();
                operatorStack.pop();
                if (op == "sqrt" || op == "exp" || op == "log" || op == "ln" ||
                    op == "sin" || op == "cos" || op == "tan" ||
                    op == "asin" || op == "acos" || op == "atan") {
                    double operand2 = valueStack.top();
                    valueStack.pop();
                    double result;
                    if (op == "sqrt") {
                        if (operand2 >= 0) {
                            result = sqrt(operand2);
                        } else {
                            cout << "Error: Square root of a negative number." << endl;
                            return 0;
                        }
                    } else if (op == "exp") {
                        result = exp(operand2);
                    } else if (op == "log") {
                        if (operand2 > 0) {
                            result = log10(operand2);
                        } else {
                            cout << "Error: Logarithm of a non-positive number." << endl;
                            return 0;
                        }
                    } else if (op == "ln") {
                        if (operand2 > 0) {
                            result = log(operand2);
                        } else {
                            cout << "Error: Natural logarithm of a non-positive number." << endl;
                            return 0;
                        }
                    } else if (op == "sin") {
                        result = sin(operand2 * M_PI / 180.0); // Convert degrees to radians
                    } else if (op == "cos") {
                        result = cos(operand2 * M_PI / 180.0); // Convert degrees to radians
                    } else if (op == "tan") {
                        result = tan(operand2 * M_PI / 180.0); // Convert degrees to radians
                    } else if (op == "asin") {
                        result = asin(operand2) * 180.0 / M_PI; // Convert radians to degrees
                    } else if (op == "acos") {
                        result = acos(operand2) * 180.0 / M_PI; // Convert radians to degrees
                    } else if (op == "atan") {
                        result = atan(operand2) * 180.0 / M_PI; // Convert radians to degrees
                    }
                    valueStack.push(result);
                } else {
                    if (valueStack.size() < 2) {
                        cout << "Error: Insufficient operands for operator " << op << endl;
                        return 0;
                    }
                    double operand2 = valueStack.top();
                    valueStack.pop();
                    double operand1 = valueStack.top();
                    valueStack.pop();
                    double result = evaluateBinaryOperator(op, operand1, operand2);
                    valueStack.push(result);
                }
            }
            operatorStack.push(current->data);
        } else {
            cout << "Invalid operator: " << current->data << endl;
            *flag_ptr = 1;
            return 0;
        }
    }

    while (!operatorStack.empty()) {
        string op = operatorStack.top();
        operatorStack.pop();
        if (op == "sqrt" || op == "exp" || op == "log" || op == "ln" ||
            op == "sin" || op == "cos" || op == "tan" ||
            op == "asin" || op == "acos" || op == "atan") {
            double operand2 = valueStack.top();
            valueStack.pop();
            double result;
            if (op == "sqrt") {
                if (operand2 >= 0) {
                    result = sqrt(operand2);
                } else {
                    cout << "Error: Square root of a negative number." << endl;
                    return 0;
                }
            } else if (op == "exp") {
                result = exp(operand2);
            } else if (op == "log") {
                if (operand2 > 0) {
                    result = log10(operand2);
                } else {
                    cout << "Error: Logarithm of a non-positive number." << endl;
                    return 0;
                }
            } else if (op == "ln") {
                if (operand2 > 0) {
                    result = log(operand2);
                } else {
                    cout << "Error: Natural logarithm of a non-positive number." << endl;
                    return 0;
                }
            } else if (op == "sin") {
                result = sin(operand2 * M_PI / 180.0); // Convert degrees to radians
            } else if (op == "cos") {
                result = cos(operand2 * M_PI / 180.0); // Convert degrees to radians
            } else if (op == "tan") {
                result = tan(operand2 * M_PI / 180.0); // Convert degrees to radians
            } else if (op == "asin") {
                result = asin(operand2) * 180.0 / M_PI; // Convert radians to degrees
            } else if (op == "acos") {
                result = acos(operand2) * 180.0 / M_PI; // Convert radians to degrees
            } else if (op == "atan") {
                result = atan(operand2) * 180.0 / M_PI; // Convert radians to degrees
            }
            valueStack.push(result);
        } else {
            // if (valueStack.size() < 2) {
            //     cout << "Error: Insufficient operands for operator " << op << endl;
            //     return 0;
            // }
            double operand2 = valueStack.top();
            valueStack.pop();
            double operand1 = valueStack.top();
            valueStack.pop();
            double result = evaluateBinaryOperator(op, operand1, operand2);
            valueStack.push(result);
        }
    }

    if (!valueStack.empty()) {
        return valueStack.top();
    } else {
        cout << "Invalid expression." << endl;
        *flag_ptr = 1;
        return 0;
    }
}

int main() {
    string input;
    History history;  // Store calculation history
    int flag = 0;
    int* flag_ptr = &flag;

    cout << "Welcome to our Scientific Calculator!" << endl;
    cout << "=====================================" << endl;
    cout << "Some functions that we can calculate besides basic operations are:" << endl;
    cout << "1. sin(), cos(), tan()" << endl;
    cout << "2. asin(), acos(), atan()" << endl;
    cout << "3. log(), ln()" << endl;
    cout << "4. Exponentials using carat symbol (^)" << endl;
    cout << "Note: please use parentheses for prioritizing certain operations" << endl;

    while (true) {
        cout << "Enter a mathematical expression (or 'history', 'delete', or 'exit'): ";
        getline(cin, input);

        if (input == "exit") {
            break;
        } else if (input == "history") {
            // Show calculation history
            history.ShowHistory();
            continue;
        } else if (input == "delete") {
            // Delete a specific entry from history
            int entryToDelete;
            cout << "Enter the entry number to delete: ";
            cin >> entryToDelete;
            cin.ignore();  // Consume the newline character

            history.DeleteEntry(entryToDelete);

            continue;
        }

        Node* head = nullptr;
        Node* tail = nullptr;

        // Create the doubly linked list from the input
        string currentToken;
        for (char c : input) {
            if (isspace(c)) {
                // Skip whitespace
                continue;
            } else if (isdigit(c) || c == '.') {
                // Accumulate digits, dots, and minus sign to form a number
                currentToken += c;
            } else if (isalpha(c)) {
                // Accumulate letters to identify functions
                currentToken += c;
            } else {
                if (!currentToken.empty()) {
                    insertAtEnd(head, tail, currentToken);
                    currentToken.clear();
                }
                // Handle operators, parentheses, and other characters
                currentToken += c;
                insertAtEnd(head, tail, currentToken);
                currentToken.clear();
            }
        }
        if (!currentToken.empty()) {
            insertAtEnd(head, tail, currentToken);
        }

        flag = 0; // reset flag

        // Prioritize operators in the linked list and evaluate the expression
        double result = prioritizeOperators(head, flag_ptr);
        if (!flag) {
            cout << "Result: " << result << endl;
            history.AddEntry(input, result);  // Add to history
        }
    }

    // Clean up the linked list (free memory) if necessary

    return 0;
}
