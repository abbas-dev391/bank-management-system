#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Account {
protected:
    int accountNumber;
    string ownerName;
    double balance;

public:
    Account(int accNo, string name, double bal) {
        accountNumber = accNo;
        ownerName = name;
        balance = bal;
    }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Amount deposited! New balance: " << balance << endl;
    }

    virtual void withdraw(double amount) {
        if(amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Amount withdrawn! New balance: " << balance << endl;
        }
    }

    virtual void display() {
        cout << "\n--- Account Info ---" << endl;
        cout << "Account No: " << accountNumber << endl;
        cout << "Owner: " << ownerName << endl;
        cout << "Balance: Rs." << balance << endl;
    }

    int getAccNo() { return accountNumber; }
    double getBalance() { return balance; }
    string getName() { return ownerName; }
};

class SavingsAccount : public Account {
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal) {
        interestRate = 0.05;
    }

    void addInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Interest added: Rs." << interest << endl;
    }

    void display() override {
        Account::display();
        cout << "Type: Savings Account" << endl;
        cout << "Interest Rate: 5%" << endl;
    }
};

class CurrentAccount : public Account {
    double overdraftLimit;

public:
    CurrentAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal) {
        overdraftLimit = 10000;
    }

    void withdraw(double amount) override {
        if(amount > balance + overdraftLimit) {
            cout << "Overdraft limit exceeded!" << endl;
        } else {
            balance -= amount;
            cout << "Amount withdrawn! New balance: Rs." << balance << endl;
        }
    }

    void display() override {
        Account::display();
        cout << "Type: Current Account" << endl;
        cout << "Overdraft Limit: Rs." << overdraftLimit << endl;
    }
};

class Bank {
    Account* accounts[100];
    int count;

public:
    Bank() { count = 0; }

    void createSavings() {
        int accNo; string name; double bal;
        cout << "Enter Account No: "; cin >> accNo;
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Initial Balance: "; cin >> bal;
        accounts[count++] = new SavingsAccount(accNo, name, bal);
        cout << "Savings Account Created!" << endl;
    }

    void createCurrent() {
        int accNo; string name; double bal;
        cout << "Enter Account No: "; cin >> accNo;
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Initial Balance: "; cin >> bal;
        accounts[count++] = new CurrentAccount(accNo, name, bal);
        cout << "Current Account Created!" << endl;
    }

    Account* findAccount(int accNo) {
        for(int i = 0; i < count; i++) {
            if(accounts[i]->getAccNo() == accNo)
                return accounts[i];
        }
        return nullptr;
    }

    void depositMoney() {
        int accNo; double amount;
        cout << "Enter Account No: "; cin >> accNo;
        Account* acc = findAccount(accNo);
        if(acc) {
            cout << "Enter Amount: "; cin >> amount;
            acc->deposit(amount);
        } else cout << "Account not found!" << endl;
    }

    void withdrawMoney() {
        int accNo; double amount;
        cout << "Enter Account No: "; cin >> accNo;
        Account* acc = findAccount(accNo);
        if(acc) {
            cout << "Enter Amount: "; cin >> amount;
            acc->withdraw(amount);
        } else cout << "Account not found!" << endl;
    }

    void displayAll() {
        if(count == 0) { cout << "No accounts found!" << endl; return; }
        for(int i = 0; i < count; i++)
            accounts[i]->display();
    }

    void transfer() {
        int from, to; double amount;
        cout << "From Account No: "; cin >> from;
        cout << "To Account No: "; cin >> to;
        cout << "Amount: "; cin >> amount;
        Account* a1 = findAccount(from);
        Account* a2 = findAccount(to);
        if(a1 && a2) {
            a1->withdraw(amount);
            a2->deposit(amount);
            cout << "Transfer successful!" << endl;
        } else cout << "Account(s) not found!" << endl;
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Current Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. Display All Accounts" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: "; cin >> choice;

        switch(choice) {
            case 1: bank.createSavings(); break;
            case 2: bank.createCurrent(); break;
            case 3: bank.depositMoney(); break;
            case 4: bank.withdrawMoney(); break;
            case 5: bank.transfer(); break;
            case 6: bank.displayAll(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while(choice != 0);

    return 0;
}
