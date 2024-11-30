#ifndef STATEATMRECEIPT_H
#define STATEATMRECEIPT_H

#include "STATE.h"

class state_ATM_receipt : public State {
private:
public:
	state_ATM_receipt(Account& account, ATM& atm, bool primary) : State(account, atm, primary) { s_name = "ATM Receipt State"; };
	~state_ATM_receipt() {};
	void stateAction() override;
};

#endif STATEATMRECEIPT_H