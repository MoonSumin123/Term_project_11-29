#include "CASH.h"

using namespace std;

Cash::Cash() : cash_value(0) {}
Cash::~Cash() {
    cout << "[Destructor] Cash" << endl;
}

int Cash::getValue() const { return cash_value; };//총 금액 반환 cash_value를 변동이 있을때마다 매번 업데이트해야 함

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
    cash_value += denomination * count; // 총 금액 업데이트
}
void Cash::subCash(int denomination, int count) {
    cash_available[denomination] -= count;
    cash_value -= denomination * count; // 총 금액 업데이트
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
