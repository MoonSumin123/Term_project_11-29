#include "CASH.h"

using namespace std;

void Cash::addCash(int denomination, int count) {
    cash_available[denomination] += count;
    cash_value += denomination * count; // 총 금액 업데이트
}
void Cash::subCash(int denomination, int count) {
    if (cash_available[denomination] >= count) {
        cash_available[denomination] -= count;
    }
}
string Cash::printAvailableCash() const {
    ostringstream oss;
    for (const auto& cash : cash_available) {
        oss << "KRW " << cash.first << ": " << cash.second << " bills\n";
    }
    return oss.str();
}