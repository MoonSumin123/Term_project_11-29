#include "CASH.h"

using namespace std;

Cash::Cash() {}
Cash::~Cash() {
    cout << "[Destructor] Cash" << endl;
}

unordered_map<int, int>& Cash::getAvailableCash() {
    return cash_available;
}

int Cash::getTotalAvailableCash() const { // 총 가용 현금을 계산하는 메서드
    int total = 0;
    for (const auto& pair : cash_available) {
        total += pair.first * pair.second; // 권종 * 수량
    }
    return total;
}


void Cash::addCash(int denomination, int count) {
    cash_available[denomination] += count;
}
void Cash::subCash(int denomination, int count) {
    cash_available[denomination] -= count;
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
