#include "CARD.h"

Card::Card(Account* account, Bank* bank, const string& card_num) : card_account(account), card_bank(bank), card_number(card_num) {}
Card::~Card() {}