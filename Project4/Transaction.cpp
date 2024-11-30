#include "TRANSACTION.h"

Transaction::Transaction(int id, const string& cardNumber, const string& type, int amount, const string& details)
    : id(id), cardNumber(cardNumber), type(type), amount(amount), details(details) {}