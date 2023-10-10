#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <vector>

using namespace std;

// Define a structure for a node in the linked list
struct Node {
    string data;
    Node* prev;
    Node* next;

    Node(const string& val) : data(val), prev(nullptr), next(nullptr) {}
};

// Define a structure for history entries
struct HistoryEntry {
    string expression;
    double result;

    HistoryEntry(const string& exp, double res) : expression(exp), result(res) {}
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

// Function to prioritize operators in the linked list
double prioritizeOperators(Node* head) {
    stack<Node*> operatorStack;
    stack<double> valueStack;  // Stack to store operand values

    while (head) {
        Node* current = head;
        head = head->next;

        if (current->data == "(") {
            // Handle sub-expression within parentheses
            operatorStack.push(current);
        } else if (isdigit(current->data[0]) || (current->data[0] == '-' && isdigit(current->data[1]))) {
            // Handle operands (numbers)
            valueStack.push(stod(current->data));
        } else if (current->data == ")") {
            // Handle closing parenthesis
            while (!operatorStack.empty() && operatorStack.top()->data != "(") {
                // Process operators within parentheses
                Node* opNode = operatorStack.top();
                operatorStack.pop();
                double operand2 = valueStack.top();
                valueStack.pop();
                double operand1 = valueStack.top();
                valueStack.pop();
                double result;
                if (opNode->data == "+") {
                    result = operand1 + operand2;
                } else if (opNode->data == "-") {
                    result = operand1 - operand2;
                } else if (opNode->data == "*") {
                    result = operand1 * operand2;
                } else if (opNode->data == "/") {
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        cout << "Error: Division by zero." << endl;
                        return 0;
                    }
                } else if (opNode->data == "^") {
                    result = pow(operand1, operand2);
                }
                valueStack.push(result);
            }
            if (!operatorStack.empty() && operatorStack.top()->data == "(") {
                operatorStack.pop(); // Remove the opening parenthesis
            } else {
                cout << "Error: Unmatched closing parenthesis." << endl;
                return 0;
            }
        } else if (current->data == "+" || current->data == "-") {
            // Handle addition and subtraction operators
            while (!operatorStack.empty() &&
                   (operatorStack.top()->data == "+" || operatorStack.top()->data == "-" ||
                    operatorStack.top()->data == "*" || operatorStack.top()->data == "/")) {
                Node* opNode = operatorStack.top();
                operatorStack.pop();
                double operand2 = valueStack.top();
                valueStack.pop();
                double operand1 = valueStack.top();
                valueStack.pop();
                double result;
                if (opNode->data == "+") {
                    result = operand1 + operand2;
                } else if (opNode->data == "-") {
                    result = operand1 - operand2;
                } else if (opNode->data == "*") {
                    result = operand1 * operand2;
                } else if (opNode->data == "/") {
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        cout << "Error: Division by zero." << endl;
                        return 0;
                    }
                }
                valueStack.push(result);
            }
            operatorStack.push(current);
        } else if (current->data == "*" || current->data == "/" || current->data == "^") {
            // Handle operators with priority
            while (!operatorStack.empty() &&
                   ((operatorStack.top()->data == "*" || operatorStack.top()->data == "/"))) {
                Node* opNode = operatorStack.top();
                operatorStack.pop();
                double operand2 = valueStack.top();
                valueStack.pop();
                double operand1 = valueStack.top();
                valueStack.pop();
                double result;
                if (opNode->data == "*") {
                    result = operand1 * operand2;
                } else if (opNode->data == "/") {
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        cout << "Error: Division by zero." << endl;
                        return 0;
                    }
                } else if (opNode->data == "^") {
                    result = pow(operand1, operand2);
                }
                valueStack.push(result);
            }
            operatorStack.push(current);
        } else if (current->data == "sin" || current->data == "cos" || current->data == "tan" ||
                   current->data == "asin" || current->data == "acos" || current->data == "atan" ||
                   current->data == "sqrt" || current->data == "exp" || current->data == "log" ||
                   current->data == "ln" || current->data == "log2") {
            // Handle trigonometric functions and their inverses, sqrt, exp, log, ln, log2
            operatorStack.push(current);
        } else {
            // Handle other operators
            cout << "Invalid operator: " << current->data << endl;
            return 0;
        }
    }

    // Process any remaining operators in the stack
    while (!operatorStack.empty()) {
        Node* opNode = operatorStack.top();
        operatorStack.pop();
        if (opNode->data == "sin" || opNode->data == "cos" || opNode->data == "tan" ||
            opNode->data == "asin" || opNode->data == "acos" || opNode->data == "atan") {
            // Handle trigonometric functions and their inverses
            double operand = valueStack.top();
            valueStack.pop();
            double result;
            if (opNode->data == "sin") {
                result = sin(operand * M_PI / 180.0); // Convert degrees to radians
            } else if (opNode->data == "cos") {
                result = cos(operand * M_PI / 180.0); // Convert degrees to radians
            } else if (opNode->data == "tan") {
                result = tan(operand * M_PI / 180.0); // Convert degrees to radians
            } else if (opNode->data == "asin") {
                result = asin(operand) * 180.0 / M_PI; // Convert radians to degrees
            } else if (opNode->data == "acos") {
                result = acos(operand) * 180.0 / M_PI; // Convert radians to degrees
            } else if (opNode->data == "atan") {
                result = atan(operand) * 180.0 / M_PI; // Convert radians to degrees
            }
            valueStack.push(result);
        } else if (opNode->data == "sqrt") {
            // Handle square root
            double operand = valueStack.top();
            valueStack.pop();
            if (operand >= 0) {
                valueStack.push(sqrt(operand));
            } else {
                cout << "Error: Square root of a negative number." << endl;
                return 0;
            }
        } else if (opNode->data == "exp") {
            // Handle exponentiation
            double operand = valueStack.top();
            valueStack.pop();
            valueStack.push(exp(operand));
        } else if (opNode->data == "log") {
            // Handle logarithm (base 10)
            double operand = valueStack.top();
            valueStack.pop();
            if (operand > 0) {
                valueStack.push(log10(operand));
            } else {
                cout << "Error: Logarithm of a non-positive number." << endl;
                return 0;
            }
        } else if (opNode->data == "ln") {
            // Handle natural logarithm (base e)
            double operand = valueStack.top();
            valueStack.pop();
            if (operand > 0) {
                valueStack.push(log(operand));
            } else {
                cout << "Error: Natural logarithm of a non-positive number." << endl;
                return 0;
            }
        } else if (opNode->data == "log2") {
            // Handle logarithm base 2
            double operand = valueStack.top();
            valueStack.pop();
            if (operand > 0) {
                valueStack.push(log2(operand));
            } else {
                cout << "Error: Logarithm base 2 of a non-positive number." << endl;
                return 0;
            }
        } else {
            // Handle other operators
            double operand2 = valueStack.top();
            valueStack.pop();
            double operand1 = valueStack.top();
            valueStack.pop();
            double result;
            if (opNode->data == "+") {
                result = operand1 + operand2;
            } else if (opNode->data == "-") {
                result = operand1 - operand2;
            } else if (opNode->data == "*") {
                result = operand1 * operand2;
            } else if (opNode->data == "/") {
                if (operand2 != 0) {
                    result = operand1 / operand2;
                } else {
                    cout << "Error: Division by zero." << endl;
                    return 0;
                }
            }
            valueStack.push(result);
        }
    }

    if (!valueStack.empty()) {
        return valueStack.top();
    } else {
        cout << "Invalid expression." << endl;
        return 0;
    }
}

int main() {
    string input;
    vector<HistoryEntry> history;  // Store calculation history

    while (true) {
        cout << "Enter a mathematical expression (or 'history', 'delete', or 'exit'): ";
        getline(cin, input);

        if (input == "exit") {
            break;
        } else if (input == "history") {
            // Show calculation history
            for (size_t i = 0; i < history.size(); ++i) {
                cout << i + 1 << ": " << history[i].expression << " = " << history[i].result << endl;
            }
            continue;
        } else if (input == "delete") {
            // Delete a specific entry from history
            int entryToDelete;
            cout << "Enter the entry number to delete: ";
            cin >> entryToDelete;
            cin.ignore();  // Consume the newline character

            if (entryToDelete >= 1 && entryToDelete <= static_cast<int>(history.size())) {
                history.erase(history.begin() + entryToDelete - 1);
                cout << "Entry " << entryToDelete << " deleted from history." << endl;
            } else {
                cout << "Invalid entry number." << endl;
            }

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
            } else if (isdigit(c) || c == '.' || c == '-') {
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

        // Prioritize operators in the linked list and evaluate the expression
        double result = prioritizeOperators(head);
        if (result != 0) {
            cout << "Result: " << result << endl;
            history.emplace_back(input, result);  // Add to history
        }
    }

    // Clean up the linked list (free memory) if necessary

    return 0;
}
