#include "SNAPSHOT.h"

void snapshot() {
	ostringstream oss;
	for (ATM* vec : atms) {
		oss << "ATM [SN: " << vec->getSerialNumber() << "] "
			<< "Type: " << vec->getATMtype() << ", "
			<< "Language: " << vec->getLanguage() << ", "
			<< "remaining cash: " << vec->getTotalAvailableCash()
			<< " { " << vec->printAvailableCash() << " }\n";
	}
	for (Bank* vec : banks) {
		for (auto& pair : vec->getAccounts()) {
			oss << "Account [Bank: " << pair.second->getBankName() << ", "
				<< "No: " << pair.second->getAccountNumber() << ", "
				<< "Owner: " << pair.second->getUserName() << "] "
				<< "Balance: " << pair.second->getFund() << "\n";
		}
	}
	cout << oss.str();
}