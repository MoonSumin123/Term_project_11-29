#include "CARD.h"

Card::Card(string card_num) : card_number(card_num) {}

Card::~Card() {
	cout << "[Destructor] Card: " << card_number << endl;
}
