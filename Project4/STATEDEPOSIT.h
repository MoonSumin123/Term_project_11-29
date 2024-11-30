#ifndef STATEDEPOSIT_H
#define STATEDEPOSIT_H

#include "STATE.h"

class state_deposit : public State {
private:
public:
	state_deposit(Account& account, ATM& atm, bool primary, Language& lang) : State(account, atm, primary, lang) { s_name = "Deposit State"; };
	~state_deposit() {};
	void stateAction() override;
};

#endif STATEDEPOSIT_H
