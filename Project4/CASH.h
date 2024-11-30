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
    Cash();
    ~Cash();

    unordered_map<int, int> getAvailableCash();
    int getValue() const;
    int getTotalAvailableCash() const;

    void addCash(int denomination, int count);
    void subCash(int denomination, int count);

    string printAvailableCash() const;
};

#endif CASH_H