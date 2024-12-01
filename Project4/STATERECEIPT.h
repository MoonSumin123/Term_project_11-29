#ifndef STATERECEIPT_H
#define STATERECEIPT_H

#include "STATE.h"

class state_receipt : public State {
private:
public:
	state_receipt(Account& account, ATM& atm, bool primary, Language& lang) : State(account, atm, primary, lang) { s_name = "Receipt Print State"; };
	~state_receipt() {};
	void stateAction() override;
};


#endif STATERECEIPT_H