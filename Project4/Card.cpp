#include "CARD.h"

Card::Card(Account* account, Bank* bank, int card_num) : card_account(account), card_bank(bank), card_number(card_num) {}
Card::~Card() {}