#ifndef STATESNAPSHOT_H
#define STATESNAPSHOT_H

#include "STATE.h"

class state_snapshot : public State {
private:
public:
	state_snapshot(Account& account, ATM& atm, bool primary) : State(account, atm, primary) { s_name = "Snapshot State"; };
	~state_snapshot() {};
	void stateAction() override;
};


#endif STATESNAPSHOT_H
