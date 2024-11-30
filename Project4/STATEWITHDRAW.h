#ifndef STATEWITHDRAW_H
#define STATEWITHDRAW_H

#include "STATE.h"

class state_withdraw : public State {
private:
	int& withdrawal_count;
	bool endSession;
public:
	state_withdraw(Account& account, ATM& atm, bool primary, int& withdrawal_count, bool& endSession) : State(account, atm, primary), withdrawal_count(withdrawal_count), endSession(endSession){ s_name = "Withdraw State"; };
	~state_withdraw() {};
	void stateAction() override;
};


#endif STATEWITHDRAW_H
