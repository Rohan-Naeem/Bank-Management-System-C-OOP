

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;




void clearScreen() {
	system("cls");
}

void pauseScreen() {
	cout << endl;
	cout << "  +--------------------------------------------+" << endl;
	cout << "  |   Press ENTER to continue...              |" << endl;
	cout << "  +--------------------------------------------+" << endl;
	cin.ignore();
	cin.get();
}

void drawLine() {
	cout << "  ================================================" << endl;
}

void drawDash() {
	cout << "  ------------------------------------------------" << endl;
}

void showWelcomeScreen() {
	clearScreen();
	cout << endl;
	cout << "  *************************************************************" << endl;
	cout << "  *************************************************************" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **                    ||||||  |||||||                       **" << endl;
	cout << "  **                    ||   || ||   ||                      **" << endl;
	cout << "  **                    ||||||  ||||||                      **" << endl;
	cout << "  **                    ||   || ||   ||                      **" << endl;
	cout << "  **                    ||   || ||   ||                      **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  *************************************************************" << endl;
	cout << "  **    =================================================    **" << endl;
	cout << "  **        MRA BANK ACCOUNT MANAGEMENT SYSTEM               **" << endl;
	cout << "  **    =================================================    **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **                   Rohan Naeem                           **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **     ------------------------------------------------    **" << endl;
	cout << "  *************************************************************" << endl;
	cout << "  *************************************************************" << endl;
	cout << endl;
	cout << "          >> Press ENTER to Launch the System..." << endl;
	cout << endl;
	cin.get();
}


void showGoodbyeScreen() {
	clearScreen();
	cout << endl;
	cout << "  *************************************************************" << endl;
	cout << "  *************************************************************" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **        THANK YOU FOR USING OUR BANKING SYSTEM !         **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **   =================================================     **" << endl;
	cout << "  **       BANK ACCOUNT MANAGEMENT SYSTEM                    **" << endl;
	cout << "  **       Your data has been saved safely to file.          **" << endl;
	cout << "  **   =================================================     **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **             Have a wonderful day!  :)                   **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  **                                                         **" << endl;
	cout << "  *************************************************************" << endl;
	cout << "  *************************************************************" << endl;
	cout << endl;
}

void showHeader(string title) {
	clearScreen();
	cout << endl;
	cout << "  ================================================" << endl;
	cout << "  ||        MRA BANK MANAGEMENT SYSTEM         ||" << endl;
	cout << "  ================================================" << endl;
	cout << "  ||  " << left << setw(44) << title << "||" << endl;
	cout << "  ================================================" << endl;
	cout << endl;
}

class Account {
	protected:
		int    accountNumber;
		string fullName;
		string cnic;
		string phone;
		string pin;
		string accountType;
		double balance;
		bool   isLocked;
		int    wrongTries;

	public:
		Account() {
			accountNumber = 0;
			fullName      = "";
			cnic          = "";
			phone         = "";
			pin           = "";
			accountType   = "";
			balance       = 0.0;
			isLocked      = false;
			wrongTries    = 0;
		}

		int    getAccountNumber() {
			return accountNumber;
		}
		string getFullName()      {
			return fullName;
		}
		string getCNIC()          {
			return cnic;
		}
		string getPhone()         {
			return phone;
		}
		string getPin()           {
			return pin;
		}
		string getAccountType()   {
			return accountType;
		}
		double getBalance()       {
			return balance;
		}
		bool   getIsLocked()      {
			return isLocked;
		}
		int    getWrongTries()    {
			return wrongTries;
		}

		void setAccountNumber(int n)  {
			accountNumber = n;
		}
		void setFullName(string n)    {
			fullName = n;
		}
		void setCNIC(string c)        {
			cnic = c;
		}
		void setPhone(string p)       {
			phone = p;
		}
		void setPin(string p)         {
			pin = p;
		}
		void setBalance(double b)     {
			balance = b;
		}
		void setIsLocked(bool l)      {
			isLocked = l;
		}
		void setWrongTries(int w)     {
			wrongTries = w;
		}
		void setAccountType(string t) {
			accountType = t;
		}

		bool checkPin(string enteredPin) {
			if (isLocked) {
				cout << "\n  >> Account is LOCKED!" << endl;
				cout << "  >> Contact admin to unlock." << endl;
				return false;
			}

			if (enteredPin == pin) {
				wrongTries = 0;
				return true;
			} else {
				wrongTries++;
				int left = 3 - wrongTries;

				if (left > 0)
					cout << "\n  >> Wrong PIN! " << left << " attempt(s) left." << endl;

				if (wrongTries >= 3) {
					isLocked = true;
					cout << "\n  >> Account LOCKED! Too many wrong attempts." << endl;
					cout << "  >> Ask admin to unlock your account." << endl;
				}
				return false;
			}
		}

		virtual void deposit(double amount)  = 0;
		virtual void withdraw(double amount) = 0;
		virtual void showInfo()              = 0;
		virtual void monthlyProcess()        = 0;
		virtual ~Account() {}
};

class SavingsAccount : public Account {
	private:
		bool isActive;
		int  withdrawCount;

	public:

		SavingsAccount() {
			accountType   = "SAVINGS";
			isActive      = true;
			withdrawCount = 0;
		}

		bool getIsActive()         {
			return isActive;
		}
		int  getWithdrawCount()    {
			return withdrawCount;
		}
		void setIsActive(bool a)   {
			isActive = a;
		}
		void setWithdrawCount(int w) {
			withdrawCount = w;
		}

		void updateStatus() {
			if (balance >= 25.0)
				isActive = true;
			else
				isActive = false;
		}
		void deposit(double amount) {
			if (amount <= 0)
				throw string("Deposit must be greater than zero.");

			balance += amount;
			updateStatus();

			cout << "\n  >> Deposit successful!" << endl;
			cout << "  >> Amount  : $" << fixed << setprecision(2) << amount  << endl;
			cout << "  >> Balance : $" << fixed << setprecision(2) << balance << endl;

			if (isActive)
				cout << "  >> Status  : ACTIVE" << endl;
			else
				cout << "  >> Status  : INACTIVE (below $25)" << endl;
		}
		void withdraw(double amount) {
			if (amount <= 0)
				throw string("Withdrawal must be greater than zero.");

			if (!isActive)
				throw string("Account is INACTIVE. Deposit to go above $25 first.");

			if (amount > balance)
				throw string("Not enough balance.");

			balance -= amount;
			withdrawCount++;

			if (withdrawCount > 4) {
				balance -= 1.0;
				cout << "\n  >> Note: $1.00 extra charge (over 4 withdrawals)." << endl;
			}

			updateStatus();

			cout << "\n  >> Withdrawal successful!" << endl;
			cout << "  >> Amount  : $" << fixed << setprecision(2) << amount  << endl;
			cout << "  >> Balance : $" << fixed << setprecision(2) << balance << endl;

			if (!isActive)
				cout << "  >> Warning: Balance below $25. Account now INACTIVE." << endl;
		}
		void monthlyProcess() {
			double interest = (0.04 / 12.0) * balance;
			balance += interest;
			withdrawCount = 0;
			updateStatus();

			cout << "\n  >> Savings Monthly Process Done." << endl;
			cout << "  >> Interest Added : $" << fixed << setprecision(2) << interest << endl;
			cout << "  >> New Balance    : $" << fixed << setprecision(2) << balance  << endl;
		}

		void showInfo() {
			drawLine();
			cout << "  ||    SAVINGS ACCOUNT - INFORMATION                ||" << endl;
			drawDash();
			cout << "  Account No  : " << accountNumber << endl;
			cout << "  Name        : " << fullName      << endl;
			cout << "  CNIC        : " << cnic          << endl;
			cout << "  Phone       : " << phone         << endl;
			cout << "  Type        : SAVINGS ACCOUNT"   << endl;
			cout << "  Status      : " << (isActive ? "ACTIVE" : "INACTIVE") << endl;
			cout << "  Balance     : $" << fixed << setprecision(2) << balance << endl;
			cout << "  Interest    : 4% per year"       << endl;
			cout << "  Withdrawals : " << withdrawCount << " this month" << endl;
			drawLine();
		}
};

class CurrentAccount : public Account {
	private:
		int withdrawCount;

	public:

		CurrentAccount() {
			accountType   = "CURRENT";
			withdrawCount = 0;
		}

		int  getWithdrawCount()    {
			return withdrawCount;
		}
		void setWithdrawCount(int w) {
			withdrawCount = w;
		}

		void deposit(double amount) {
			if (amount <= 0)
				throw string("Deposit must be greater than zero.");

			balance += amount;

			cout << "\n  >> Deposit successful!" << endl;
			cout << "  >> Amount  : $" << fixed << setprecision(2) << amount  << endl;
			cout << "  >> Balance : $" << fixed << setprecision(2) << balance << endl;
		}
		void withdraw(double amount) {
			if (amount <= 0)
				throw string("Withdrawal must be greater than zero.");

			if (amount > balance) {
				balance -= 15.0;
				cout << "\n  >> Withdrawal REJECTED (not enough balance)." << endl;
				cout << "  >> $15.00 overdraft penalty charged."            << endl;
				cout << "  >> New Balance : $" << fixed << setprecision(2) << balance << endl;
				return;
			}

			balance -= amount;
			withdrawCount++;

			cout << "\n  >> Withdrawal successful!" << endl;
			cout << "  >> Amount  : $" << fixed << setprecision(2) << amount  << endl;
			cout << "  >> Balance : $" << fixed << setprecision(2) << balance << endl;
		}
		void monthlyProcess() {
			double fee      = 5.0 + (withdrawCount * 0.10);
			double interest = (0.02 / 12.0) * balance;

			balance -= fee;
			balance += interest;
			withdrawCount = 0;

			cout << "\n  >> Current Monthly Process Done." << endl;
			cout << "  >> Fee Deducted   : $" << fixed << setprecision(2) << fee      << endl;
			cout << "  >> Interest Added : $" << fixed << setprecision(2) << interest << endl;
			cout << "  >> New Balance    : $" << fixed << setprecision(2) << balance  << endl;
		}
		void showInfo() {
			drawLine();
			cout << "  ||    CURRENT ACCOUNT - INFORMATION                ||" << endl;
			drawDash();
			cout << "  Account No  : " << accountNumber << endl;
			cout << "  Name        : " << fullName      << endl;
			cout << "  CNIC        : " << cnic          << endl;
			cout << "  Phone       : " << phone         << endl;
			cout << "  Type        : CURRENT ACCOUNT"   << endl;
			cout << "  Balance     : $" << fixed << setprecision(2) << balance << endl;
			cout << "  Interest    : 2% per year"       << endl;
			cout << "  Monthly Fee : $5 + $0.10 per withdrawal" << endl;
			cout << "  Withdrawals : " << withdrawCount << " this month" << endl;
			drawLine();
		}
};

const int max_account = 50;
Account*  accounts[max_account];
int       totalAccounts = 0;

void saveToFile() {
	ofstream file("mra_bank.txt");

	if (!file)
		throw string("Cannot open file for saving!");

	for (int i = 0; i < totalAccounts; i++) {
		file << "TYPE:"       << accounts[i]->getAccountType()   << endl;
		file << "NUMBER:"     << accounts[i]->getAccountNumber() << endl;
		file << "NAME:"       << accounts[i]->getFullName()      << endl;
		file << "CNIC:"       << accounts[i]->getCNIC()          << endl;
		file << "PHONE:"      << accounts[i]->getPhone()         << endl;
		file << "PIN:"        << accounts[i]->getPin()           << endl;
		file << "BALANCE:"    << accounts[i]->getBalance()       << endl;
		file << "LOCKED:"     << accounts[i]->getIsLocked()      << endl;
		file << "WRONGTRIES:" << accounts[i]->getWrongTries()    << endl;

		if (accounts[i]->getAccountType() == "SAVINGS") {
			SavingsAccount* s = (SavingsAccount*) accounts[i];
			file << "WITHDRAWCOUNT:" << s->getWithdrawCount() << endl;
			file << "ACTIVE:"        << s->getIsActive()      << endl;
		} else {
			CurrentAccount* c = (CurrentAccount*) accounts[i];
			file << "WITHDRAWCOUNT:" << c->getWithdrawCount() << endl;
		}
		

		file << "END" << endl;
		file << "====================================" << endl;
	}

	file.close();
	cout << "\n  >> Data saved to file successfully." << endl;
}

void loadFromFile() {
	ifstream file("mra_bank.txt");

	if (!file) {
		cout << "\n  >> No saved data found. Starting fresh." << endl;
		return;
	}

	string line;
	totalAccounts = 0;

	while (getline(file, line) && totalAccounts < max_account) {
		if (line.substr(0, 5) != "TYPE:") continue;

		string type = line.substr(5);

		string numStr    = "0";
		string name      = "";
		string cnic      = "";
		string phone     = "";
		string pin       = "";
		string balStr    = "0";
		string lockedStr = "0";
		string wrongStr  = "0";
		string wdStr     = "0";
		string activeStr = "1";

		while (getline(file, line) && line != "END") {
			int colon = line.find(':');
			if (colon == (int)string::npos) continue;

			string key = line.substr(0, colon);
			string val = line.substr(colon + 1);

			if      (key == "NUMBER")        numStr    = val;
			else if (key == "NAME")          name      = val;
			else if (key == "CNIC")          cnic      = val;
			else if (key == "PHONE")         phone     = val;
			else if (key == "PIN")           pin       = val;
			else if (key == "BALANCE")       balStr    = val;
			else if (key == "LOCKED")        lockedStr = val;
			else if (key == "WRONGTRIES")    wrongStr  = val;
			else if (key == "WITHDRAWCOUNT") wdStr     = val;
			else if (key == "ACTIVE")        activeStr = val;
		}
		Account* acc = nullptr;
		if (type == "SAVINGS") {
			SavingsAccount* s = new SavingsAccount();
			s->setWithdrawCount(atoi(wdStr.c_str()));
			s->setIsActive(activeStr == "1");
			acc = s;
		} else {
			CurrentAccount* c = new CurrentAccount();
			c->setWithdrawCount(atoi(wdStr.c_str()));
			acc = c;
		}

		acc->setAccountNumber(atoi(numStr.c_str()));
		acc->setFullName(name);
		acc->setCNIC(cnic);
		acc->setPhone(phone);
		acc->setPin(pin);
		acc->setBalance(atof(balStr.c_str()));
		acc->setIsLocked(lockedStr == "1");
		acc->setWrongTries(atoi(wrongStr.c_str()));

		accounts[totalAccounts] = acc;
		totalAccounts++;
	}

	file.close();
	cout << "\n  >> " << totalAccounts << " account(s) loaded successfully." << endl;
}

int findAccount(int accNum) {
	for (int i = 0; i < totalAccounts; i++)
		if (accounts[i]->getAccountNumber() == accNum)
			return i;
	return -1;
}

int nextAccountNumber() {
	int maxNum = 1000;
	for (int i = 0; i < totalAccounts; i++)
		if (accounts[i]->getAccountNumber() > maxNum)
			maxNum = accounts[i]->getAccountNumber();
	return maxNum + 1;
}


void createAccount() {
	showHeader("CREATE NEW ACCOUNT");

	if (totalAccounts >= max_account) {
		cout << "  >> Bank is full. Cannot add more accounts." << endl;
		pauseScreen();
		return;
	}

	string name, cnic, phone, pin, confirm, typeChoice;
	double openBalance;

	cin.ignore();

	cout << "  Full Name       : ";
	getline(cin, name);

	cout << "  CNIC            : ";
	getline(cin, cnic);

	cout << "  Phone Number    : ";
	getline(cin, phone);

	cout << endl;
	cout << "  Account Type:" << endl;
	cout << "  [1] Savings Account  (4% interest)" << endl;
	cout << "  [2] Current Account  (2% interest)" << endl;
	cout << "  Choose (1 or 2): ";
	getline(cin, typeChoice);

	cout << endl;
	cout << "  Opening Balance ($): ";
	cin  >> openBalance;

	if (openBalance < 0) {
		cout << "\n  >> Balance cannot be negative." << endl;
		pauseScreen();
		return;
	}

	cout << endl;
	cout << "  Set PIN (4 digits): ";
	cin  >> pin;

	cout << "  Confirm PIN       : ";
	cin  >> confirm;

	if (pin != confirm) {
		cout << "\n  >> PINs do not match. Account not created." << endl;
		pauseScreen();
		return;
	}

	if (pin.length() < 4) {
		cout << "\n  >> PIN must be at least 4 digits." << endl;
		pauseScreen();
		return;
	}

	Account* newAcc = nullptr;

	if (typeChoice == "1")
		newAcc = new SavingsAccount();
	else
		newAcc = new CurrentAccount();

	int newNum = nextAccountNumber();

	newAcc->setAccountNumber(newNum);
	newAcc->setFullName(name);
	newAcc->setCNIC(cnic);
	newAcc->setPhone(phone);
	newAcc->setPin(pin);
	newAcc->setBalance(openBalance);

	accounts[totalAccounts] = newAcc;
	totalAccounts++;

	try {
		saveToFile();
	} catch (string e) {
		cout << "\n  >> Warning: " << e << endl;
	}

	cout << endl;
	drawLine();
	cout << "  >>  ACCOUNT CREATED SUCCESSFULLY!" << endl;
	drawDash();
	cout << "  Account Number : " << newNum                    << endl;
	cout << "  Name           : " << name                      << endl;
	cout << "  Type           : " << newAcc->getAccountType()  << endl;
	cout << "  Balance        : $" << fixed << setprecision(2) << openBalance << endl;
	cout << "  >> Remember your Account Number: " << newNum    << endl;
	drawLine();

	pauseScreen();
}

int userLogin() {
	showHeader("USER LOGIN");

	int accNum;
	cout << "  Enter Account Number : ";
	cin  >> accNum;

	int idx = findAccount(accNum);

	if (idx == -1) {
		cout << "\n  >> Account not found." << endl;
		pauseScreen();
		return -1;
	}

	if (accounts[idx]->getIsLocked()) {
		cout << "\n  >> This account is LOCKED." << endl;
		cout << "  >> Contact admin to unlock it." << endl;
		pauseScreen();
		return -1;
	}

	string enteredPin;
	cout << "  Enter PIN            : ";
	cin  >> enteredPin;

	if (accounts[idx]->checkPin(enteredPin)) {
		try {
			saveToFile();
		} catch (...) {}
		cout << "\n  >> Login successful!" << endl;
		cout << "  >> Welcome, " << accounts[idx]->getFullName() << "!" << endl;
		pauseScreen();
		return idx;
	} else {
		try {
			saveToFile();
		} catch (...) {}
		pauseScreen();
		return -1;
	}
}

void userMenu(int idx) {
	int choice;

	do {
		clearScreen();
		cout << endl;
		drawLine();
		cout << "  ||       MRA BANK - USER DASHBOARD                 ||" << endl;
		drawDash();
		cout << "  ||  Name    : " << left << setw(35) << accounts[idx]->getFullName()      << "||" << endl;
		cout << "  ||  Acc No  : " << left << setw(35) << accounts[idx]->getAccountNumber() << "||" << endl;
		cout << "  ||  Type    : " << left << setw(35) << accounts[idx]->getAccountType()   << "||" << endl;
		cout << "  ||  Balance : $" << left << setw(34) << fixed << setprecision(2) << accounts[idx]->getBalance() << "||" << endl;
		drawLine();
		cout << "  ||  [1]  Deposit Money                             ||" << endl;
		cout << "  ||  [2]  Withdraw Money                            ||" << endl;
		cout << "  ||  [3]  Transfer to Another Account               ||" << endl;
		cout << "  ||  [4]  Check Balance                             ||" << endl;
		cout << "  ||  [5]  View Account Information                  ||" << endl;
		cout << "  ||  [6]  Update My Information                     ||" << endl;
		cout << "  ||  [7]  Change PIN                                ||" << endl;
		cout << "  ||  [0]  Logout                                    ||" << endl;
		drawLine();
		cout << endl;
		cout << "  Enter choice: ";
		cin  >> choice;

		double amount;

		switch (choice) {
			case 1:
				showHeader("DEPOSIT MONEY");
				cout << "  Current Balance : $" << fixed << setprecision(2)
				     << accounts[idx]->getBalance() << endl << endl;
				cout << "  Enter deposit amount: $";
				cin  >> amount;
				try {
					accounts[idx]->deposit(amount);   // Polymorphism
					saveToFile();
				} catch (string e) {
					cout << "\n  >> Error: " << e << endl;
				} catch (...)      {
					cout << "\n  >> Something went wrong."  << endl;
				}
				pauseScreen();
				break;
			case 2:
				showHeader("WITHDRAW MONEY");
				cout << "  Current Balance : $" << fixed << setprecision(2)
				     << accounts[idx]->getBalance() << endl << endl;
				cout << "  Enter withdrawal amount: $";
				cin  >> amount;
				try {
					accounts[idx]->withdraw(amount);  // Polymorphism
					saveToFile();
				} catch (string e) {
					cout << "\n  >> Error: " << e << endl;
				} catch (...)      {
					cout << "\n  >> Something went wrong."  << endl;
				}
				pauseScreen();
				break;
			case 3: {
				showHeader("TRANSFER MONEY");
				cout << "  Your Balance : $" << fixed << setprecision(2)
				     << accounts[idx]->getBalance() << endl << endl;

				int toNum;
				cout << "  Enter recipient Account Number: ";
				cin  >> toNum;

				if (toNum == accounts[idx]->getAccountNumber()) {
					cout << "\n  >> Cannot transfer to your own account." << endl;
					pauseScreen();
					break;
				}

				int toIdx = findAccount(toNum);
				if (toIdx == -1) {
					cout << "\n  >> Recipient account not found." << endl;
					pauseScreen();
					break;
				}

				cout << "  Recipient Name : " << accounts[toIdx]->getFullName() << endl;
				cout << "  Enter amount   : $";
				cin  >> amount;

				if (amount <= 0) {
					cout << "\n  >> Amount must be greater than zero." << endl;
					pauseScreen();
					break;
				}

				if (amount > accounts[idx]->getBalance()) {
					cout << "\n  >> Not enough balance for transfer." << endl;
					pauseScreen();
					break;
				}

				cout << "\n  Confirm transfer of $" << fixed << setprecision(2)
				     << amount << " to " << accounts[toIdx]->getFullName()
				     << " ? (y/n): ";
				char confirm;
				cin  >> confirm;

				if (confirm == 'y' || confirm == 'Y') {
					accounts[idx]->setBalance(accounts[idx]->getBalance() - amount);
					accounts[toIdx]->setBalance(accounts[toIdx]->getBalance() + amount);
					saveToFile();

					cout << "\n  >> Transfer successful!"    << endl;
					cout << "  >> Sent to : " << accounts[toIdx]->getFullName() << endl;
					cout << "  >> Amount  : $" << fixed << setprecision(2) << amount << endl;
					cout << "  >> Your new Balance : $" << accounts[idx]->getBalance() << endl;
				} else {
					cout << "\n  >> Transfer cancelled." << endl;
				}

				pauseScreen();
				break;
			}

			case 4:
				showHeader("CHECK BALANCE");
				cout << "  Account No   : " << accounts[idx]->getAccountNumber() << endl;
				cout << "  Name         : " << accounts[idx]->getFullName()       << endl;
				cout << "  Account Type : " << accounts[idx]->getAccountType()    << endl;
				cout << "  Balance      : $" << fixed << setprecision(2)
				     << accounts[idx]->getBalance() << endl;
				pauseScreen();
				break;

			case 5:
				showHeader("ACCOUNT INFORMATION");
				accounts[idx]->showInfo();
				pauseScreen();
				break;

			case 6: {
				showHeader("UPDATE MY INFORMATION");
				cout << "  What to update?" << endl;
				cout << "  [1] Full Name"   << endl;
				cout << "  [2] Phone Number" << endl;
				cout << "  [0] Cancel"      << endl;
				cout << "\n  Choice: ";

				int upChoice;
				cin >> upChoice;
				cin.ignore();

				if (upChoice == 1) {
					string newName;
					cout << "  Current Name : " << accounts[idx]->getFullName() << endl;
					cout << "  New Name     : ";
					getline(cin, newName);
					accounts[idx]->setFullName(newName);
					saveToFile();
					cout << "\n  >> Name updated successfully!" << endl;
				} else if (upChoice == 2) {
					string newPhone;
					cout << "  Current Phone : " << accounts[idx]->getPhone() << endl;
					cout << "  New Phone     : ";
					getline(cin, newPhone);
					accounts[idx]->setPhone(newPhone);
					saveToFile();
					cout << "\n  >> Phone updated successfully!" << endl;
				} else {
					cout << "\n  >> Cancelled." << endl;
				}

				pauseScreen();
				break;
			}

			case 7: {
				showHeader("CHANGE PIN");

				string oldPin;
				cout << "  Enter current PIN : ";
				cin  >> oldPin;

				if (!accounts[idx]->checkPin(oldPin)) {
					saveToFile();
					pauseScreen();
					break;
				}

				string newPin, confirmPin;
				cout << "  Enter new PIN     : ";
				cin  >> newPin;

				cout << "  Confirm new PIN   : ";
				cin  >> confirmPin;

				if (newPin != confirmPin) {
					cout << "\n  >> PINs do not match. Not changed." << endl;
				} else if (newPin.length() < 4) {
					cout << "\n  >> PIN must be at least 4 digits." << endl;
				} else {
					accounts[idx]->setPin(newPin);
					saveToFile();
					cout << "\n  >> PIN changed successfully!" << endl;
				}
				pauseScreen();
				break;
			}
			case 0:
				cout << "\n  >> Logged out. Goodbye, "
				     << accounts[idx]->getFullName() << "!" << endl;
				pauseScreen();
				break;

			default:
				cout << "\n  >> Invalid choice. Try again." << endl;
				pauseScreen();
		}

	} while (choice != 0);
}



// ADMIN PANEL
// Admin login: username = admin, password = admin123

void adminPanel() {
	showHeader("ADMIN LOGIN");

	string user, pass;
	cout << "  Admin Username : ";
	cin  >> user;

	cout << "  Admin Password : ";
	cin  >> pass;

	if (user != "admin" || pass != "admin123") {
		cout << "\n  >> Wrong admin credentials!" << endl;
		pauseScreen();
		return;
	}

	cout << "\n  >> Admin login successful!" << endl;
	pauseScreen();

	int choice;
	do {
		clearScreen();
		cout << endl;
		drawLine();
		cout << "  ||        MRA BANK - ADMIN PANEL                   ||" << endl;
		drawLine();
		cout << "  ||  [1]  View All Accounts                         ||" << endl;
		cout << "  ||  [2]  Search Account by Number                  ||" << endl;
		cout << "  ||  [3]  Delete Account                            ||" << endl;
		cout << "  ||  [4]  Unlock Locked Account                     ||" << endl;
		cout << "  ||  [5]  Run Monthly Process (All Accounts)        ||" << endl;
		cout << "  ||  [6]  Bank Summary                              ||" << endl;
		cout << "  ||  [0]  Logout Admin                              ||" << endl;
		drawLine();
		cout << "\n  Enter choice: ";
		cin  >> choice;

		switch (choice) {

			case 1: {
				showHeader("ALL ACCOUNTS");

				if (totalAccounts == 0) {
					cout << "  >> No accounts exist yet." << endl;
				} else {
					cout << left;
					cout << "  No  | Acc No | Name                     | Type     | Balance" << endl;
					drawDash();
					for (int i = 0; i < totalAccounts; i++) {
						cout << "  " << setw(4) << (i + 1) << "| " << setw(7) << accounts[i]->getAccountNumber() << "| " << setw(25) << accounts[i]->getFullName() << "| " << setw(9) << accounts[i]->getAccountType() << "| $" << fixed << setprecision(2) << accounts[i]->getBalance() << endl;
					}

					drawDash();
					cout << "  Total Accounts: " << totalAccounts << endl;
				}

				pauseScreen();
				break;
			}
			case 2: {
				showHeader("SEARCH ACCOUNT");
				int accNum;
				cout << "  Enter Account Number: ";
				cin  >> accNum;

				int idx = findAccount(accNum);
				if (idx == -1)
					cout << "\n  >> Account not found." << endl;
				else {
					cout << endl;
					accounts[idx]->showInfo();
				}
				pauseScreen();
				break;
			}

			case 3: {
				showHeader("DELETE ACCOUNT");
				int accNum;
				cout << "  Enter Account Number to delete: ";
				cin  >> accNum;

				int idx = findAccount(accNum);
				if (idx == -1) {
					cout << "\n  >> Account not found." << endl;
					pauseScreen();
					break;
				}

				cout << "\n  Account : " << accounts[idx]->getFullName() << endl;
				cout << "  Balance : $" << fixed << setprecision(2)
				     << accounts[idx]->getBalance() << endl;
				cout << "\n  Type YES to confirm delete: ";
				string confirm;
				cin  >> confirm;

				if (confirm == "Yes" || confirm == "yes") {
					delete accounts[idx];

					for (int i = idx; i < totalAccounts - 1; i++)
						accounts[i] = accounts[i + 1];

					accounts[totalAccounts - 1] = nullptr;
					totalAccounts--;

					try {
						saveToFile();
					} catch (string e) {
						cout << "  >> Warning: " << e << endl;
					}

					cout << "\n  >> Account deleted successfully." << endl;
				} else {
					cout << "\n  >> Deletion cancelled." << endl;
				}
				pauseScreen();
				break;
			}

			case 4: {
				showHeader("UNLOCK ACCOUNT");
				int accNum;
				cout << "  Enter Account Number to unlock: ";
				cin  >> accNum;

				int idx = findAccount(accNum);
				if (idx == -1) {
					cout << "\n  >> Account not found." << endl;
				} else {
					accounts[idx]->setIsLocked(false);
					accounts[idx]->setWrongTries(0);
					saveToFile();
					cout << "\n  >> Account " << accNum
					     << " (" << accounts[idx]->getFullName()
					     << ") is now UNLOCKED." << endl;
				}
				pauseScreen();
				break;
			}

			case 5: {
				showHeader("MONTHLY PROCESS - ALL ACCOUNTS");
				if (totalAccounts == 0) {
					cout << "  >> No accounts to process." << endl;
				} else {
					for (int i = 0; i < totalAccounts; i++) {
						cout << "\n  Processing: " << accounts[i]->getFullName()
						     << "  (Acc " << accounts[i]->getAccountNumber() << ")" << endl;
						accounts[i]->monthlyProcess();   // Polymorphism
					}
					saveToFile();
					cout << "\n  >> All accounts processed successfully." << endl;
				}
				pauseScreen();
				break;
			}

			case 6: {
				showHeader("BANK SUMMARY");

				int    savCount = 0, curCount = 0;
				double savTotal = 0, curTotal = 0;

				for (int i = 0; i < totalAccounts; i++) {
					if (accounts[i]->getAccountType() == "SAVINGS") {
						savCount++;
						savTotal += accounts[i]->getBalance();
					} else {
						curCount++;
						curTotal += accounts[i]->getBalance();
					}
				}

				drawLine();
				cout << "  Total Accounts   : " << totalAccounts << endl;
				cout << "  Savings Accounts : " << savCount      << endl;
				cout << "  Current Accounts : " << curCount      << endl;
				drawDash();
				cout << "  Savings Funds    : $" << fixed << setprecision(2) << savTotal              << endl;
				cout << "  Current Funds    : $" << fixed << setprecision(2) << curTotal              << endl;
				cout << "  Total Bank Funds : $" << fixed << setprecision(2) << (savTotal + curTotal) << endl;
				drawLine();
				pauseScreen();
				break;
			}

			case 0:
				cout << "\n  >> Admin logged out." << endl;
				pauseScreen();
				break;

			default:
				cout << "\n  >> Invalid choice." << endl;
				pauseScreen();
		}

	} while (choice != 0);
}

void showMainMenu() {
	clearScreen();
	cout << endl;
	drawLine();
	cout << "  ||        MRA BANK MANAGEMENT SYSTEM               ||" << endl;
	cout << "  ||    Secure  |  Simple  |  Reliable               ||" << endl;
	drawLine();
	cout << "  ||  [1]  Create New Account                        ||" << endl;
	cout << "  ||  [2]  User Login                                ||" << endl;
	cout << "  ||  [3]  Admin Panel                               ||" << endl;
	cout << "  ||  [0]  Exit                                      ||" << endl;
	drawLine();
	cout << "  ||  Total Accounts : " << setw(3) << totalAccounts
	     << "                           ||" << endl;
	drawLine();
	cout << endl;
	cout << "  Enter your choice: ";
}

int main() {
	showWelcomeScreen();
	showHeader("LOADING DATA...");
	try {
		loadFromFile();
	} catch (string e) {
		cout << "  >> File error: " << e << endl;
	}
	pauseScreen();

	int choice;

	do {
		showMainMenu();
		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n  >> Please enter a number." << endl;
			pauseScreen();
			continue;
		}

		switch (choice) {
			case 1:
				createAccount();
				break;

			case 2: {
				int idx = userLogin();
				if (idx != -1)
					userMenu(idx);
				break;
			}

			case 3:
				adminPanel();
				break;

			case 0:
				try {
					saveToFile();
				} catch (string e) {
					cout << "  >> " << e << endl;
				}
				showGoodbyeScreen();
				break;

			default:
				cout << "\n  >> Invalid choice." << endl;
				pauseScreen();
		}

	} while (choice != 0);
	for (int i = 0; i < totalAccounts; i++) {
		delete accounts[i];
		accounts[i] = NULL;
	}

	return 0;
}
