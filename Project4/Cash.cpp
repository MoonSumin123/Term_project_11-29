#include "CASH.h"

using namespace std;

Cash::Cash() : cash_value(0) {}
Cash::~Cash() {
    cout << "[Destructor] Cash" << endl;
}

int Cash::getValue() const { return cash_value; };//�� �ݾ� ��ȯ cash_value�� ������ ���������� �Ź� ������Ʈ�ؾ� ��

unordered_map<int, int> Cash::getAvailableCash() {
    return cash_available;
}

int Cash::getTotalAvailableCash() const { // �� ���� ������ ����ϴ� �޼���
    int total = 0;
    for (const auto& pair : cash_available) {
        total += pair.first * pair.second; // ���� * ����
    }
    return total;
}


void Cash::addCash(int denomination, int count) {
    cash_available[denomination] += count;
    cash_value += denomination * count; // �� �ݾ� ������Ʈ
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