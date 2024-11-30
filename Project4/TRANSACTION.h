
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ATM.h"
#include "ACCOUNT.h"
#include <string>


class Transaction {
private:
    int id;                      // �ŷ� ID
    string cardNumber;     // ī�� ��ȣ
    string type;           // �ŷ� ���� (��: "Deposit", "Withdraw", "Transfer")
    int amount;              // �ŷ� �ݾ�
    string details;        // �ŷ� ���� ����
public:
    Transaction(int id, const string& cardNumber, const string& type, int amount, const string& details);
};


#endif TRANSACTION_H