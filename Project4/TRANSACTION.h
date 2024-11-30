
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ATM.h"
#include "ACCOUNT.h"
#include <string>


class Transaction {
private:
    int id;                      // 거래 ID
    string cardNumber;     // 카드 번호
    string type;           // 거래 유형 (예: "Deposit", "Withdraw", "Transfer")
    int amount;              // 거래 금액
    string details;        // 거래 세부 정보
public:
    Transaction(int id, const string& cardNumber, const string& type, int amount, const string& details);
};


#endif TRANSACTION_H