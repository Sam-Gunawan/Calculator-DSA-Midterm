#ifndef HISTORYH
#define HISTORYH

#include <string>
#include <vector>

using namespace std;

class History {
    public:
        History();
        History(string expression, double result);
        
        void ShowHistory();
        void AddEntry(string expression, double result);
        void DeleteEntry(int entry);

    private:
        string expression;
        double result;
        vector<History> history;
};

#endif
