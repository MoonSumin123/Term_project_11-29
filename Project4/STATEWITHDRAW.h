#ifndef STATEWITHDRAW_H
#define STATEWITHDRAW_H

#include "STATE.h"

class state_withdraw : public State {
private:
	int& withdrawal_count;
public:
	state_withdraw(Account& account, ATM& atm, bool primary, Language& lang,int& withdrawal_count) : State(account, atm, primary, lang), withdrawal_count(withdrawal_count) { s_name = "Withdraw State"; };
	~state_withdraw() {};
	void stateAction() override;
};


#endif STATEWITHDRAW_H
