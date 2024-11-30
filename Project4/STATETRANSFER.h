#ifndef STATETRANSFER_H
#define STATETRANSFER_H

#include "STATE.h"

class state_transfer : public State {
private:
public:
	state_transfer(Account& account, ATM& atm, bool primary, Language& lang) : State(account, atm, primary, lang) { s_name = "Transfer State"; };
	~state_transfer() {};
	void stateAction() override;
};

#endif STATETRANSFER_H
