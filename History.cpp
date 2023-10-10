#include "History.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

History::History() {
    expression = "Empty";
    result = -1;
}

History::History(string expression, double result) {
    this -> expression = expression;
    this -> result = result;
}

void History::ShowHistory() {
    for (int i = 0; i < history.size(); ++i) {
        cout << i + 1 << ": " << history[i].expression << " = " << history[i].result << endl;
    }
}

void History::AddEntry(string expression, double result) {
    history.emplace_back(expression, result);  // Add to history
}

void History::DeleteEntry(int entry) {
    if (entry >= 1 && entry <= static_cast<int>(history.size())) {
        history.erase(history.begin() + entry - 1);
        cout << "Entry " << entry << " deleted from history." << endl;
    } else {
        cout << "Invalid entry number." << endl;
    }
}