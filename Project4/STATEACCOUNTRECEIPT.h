#ifndef STATEACCOUNTRECEIPT_H
#define STATEACCOUNTRECEIPT_H

#include "STATE.h"

class state_account_receipt : public State {
private:
public:
	state_account_receipt(Account& account, ATM& atm, bool primary, Language& lang) : State(account, atm, primary, lang) { s_name = "Account Receipt State"; };
	~state_account_receipt() {};
	//void stateAction() override;
};


#endif STATEACCOUNTRECEIPT_H
