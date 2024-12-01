#include "CASH.h"

using namespace std;

Cash::Cash() {}

Cash::~Cash() {
    cout << "[Destructor] Cash" << endl;
}



void Cash::addCash(int denomination, int count) {
    cash_available[denomination] += count;
}

void Cash::subCash(int denomination, int count) {
    cash_available[denomination] -= count;
}



int Cash::getTotalAvailableCash() const { 
    int total = 0;
    for (const auto& pair : cash_available) {
        total += pair.first * pair.second;
    }
    return total;
}

unordered_map<int, int>& Cash::getAvailableCash() {
    return cash_available;
}

string Cash::printAvailableCash() const {
    ostringstream oss;
    string sep = "";
    for (const auto& cash : cash_available) {
        oss << sep << "KRW " << cash.first << ": " << cash.second << " bills";
        sep = ", ";
    }
    return oss.str();
}
