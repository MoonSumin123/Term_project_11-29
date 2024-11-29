#ifndef CASH_H
#define CASH_H

#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

class Cash {
private:
    unordered_map<int, int> cash_available;
    int cash_value;
public:
    Cash() : cash_value(0) {}
    int getValue() const { return cash_value; };//�� �ݾ� ��ȯ cash_value�� ������ ���������� �Ź� ������Ʈ�ؾ� ��
    unordered_map<int, int> getAvailableCash() {
        return cash_available;
    }

    int getTotalAvailableCash() const { // �� ���� ������ ����ϴ� �޼���
        int total = 0;
        for (const auto& pair : cash_available) {
            total += pair.first * pair.second; // ���� * ����
        }
        return total;
    }
    void addCash(int denomination, int count);
    string printAvailableCash() const;
    void subCash(int denomination, int count);
};

#endif CASH_H