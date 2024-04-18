#include <iostream>
#include <vector>

using namespace std;

class bank_account {
private:
    int account_number_;
    double balance_;
    double interest_rate_;

public:
    bank_account(const int acc_number, const double initial_balance) {
        this -> account_number_ = acc_number;
        this -> balance_ = initial_balance;
        this -> interest_rate_ = 0.0;
    }

    void deposit(const double amount) {
        if (amount > 0) {
            balance_ += amount;
            cout << "Deposit of $" << amount << " successful." << '\n';
        } else {
            cout << "Invalid deposit amount." << '\n';
        }
    }

    void withdraw(const double amount) {
        if (amount > 0 && amount <= balance_) {
            balance_ -= amount;
            cout << "Withdrawal of $" << amount << " successful." << '\n';
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << '\n';
        }
    }

    double get_interest() const {
        return balance_ * interest_rate_ / 12;
    }

    double get_balance() const {
        return balance_;
    }

    void set_interest_rate(const double rate) {
        interest_rate_ = rate;
    }

    int get_account_number() const {
        return account_number_;
    }

    friend bool transfer(bank_account& from, bank_account& to, double amount);
};

bool transfer(bank_account& from, bank_account& to, const double amount) {
    if (amount > 0 && amount <= from.balance_) {
        from.balance_ -= amount;
        to.balance_ += amount;
        cout << "Transfer of $" << amount << " successful." << '\n';
        return true;
    }
    cout << "Invalid transfer amount or insufficient funds." << '\n';
    return false;
}

vector<bank_account>::iterator find_account_by_number(vector<bank_account>& accounts, int account_number) {
    for (auto current_account = accounts.begin();
    current_account != accounts.end(); ++current_account) {
        if (current_account->get_account_number() == account_number) {
            return current_account;
        }
    }
    return accounts.end();
}

void bank_account_interface(bank_account& account, vector<bank_account>& accounts) {
    int choice;
    double amount;

    cout << "Choose an action:" << '\n';
    cout << "1. Deposit funds" << '\n';
    cout << "2. Withdraw funds" << '\n';
    cout << "3. Get balance" << '\n';
    cout << "4. Get interest rate" << '\n';
    cout << "5. Set interest rate" << '\n';
    cout << "6. Transfer funds" << '\n';
    cout << "0. Exit" << '\n';
    cout << "Your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter amount to deposit: $";
            cin >> amount;
            account.deposit(amount);
            break;

        case 2:
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            account.withdraw(amount);
            break;

        case 3:
            cout << "Current balance: $" << account.get_balance() << '\n';
            break;

        case 4:
            cout << "Current balance: $" << account.get_interest() << '\n';
            break;

        case 5:
            cout << "Enter new interest rate: ";
            cin >> amount;
            account.set_interest_rate(amount);
            break;

        case 6: {
            int to_account_number;
            cout << "Enter account number to transfer to: ";
            cin >> to_account_number;
            cout << "Enter amount to transfer: $";
            cin >> amount;

            auto current_account
            = find_account_by_number(accounts, to_account_number);

            if (current_account != accounts.end()) {
                transfer(account, *current_account, amount);
            } else {
                cout << "Recipient account not found." << '\n';
            }
            break;
        }

        case 0:
            cout << "Goodbye!" << '\n';
            return;

        default:
            cout << "Invalid choice." << '\n';
            break;
    }
    bank_account_interface(account, accounts);
}

int main() {

    cout << "Welcome to the bank!" << '\n';

    vector<bank_account> accounts;

    const bank_account default_account1(111111, 100.0);
    const bank_account default_account2(222222, 200.0);

    accounts.push_back(default_account1);
    accounts.push_back(default_account2);

    while (true) {
        cout << "Choose an action:" << '\n';
        cout << "1. Add new account" << '\n';
        cout << "2. Use existing account" << '\n';
        cout << "3. Exit" << '\n';
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        if (choice == 3 || choice == 0){
            return 0;
        }
        else if (choice == 1) {
            int acc_number;
            double initial_balance;
            cout << "Enter account number: ";
            cin >> acc_number;
            cout << "Enter initial balance: $";
            cin >> initial_balance;
            accounts.emplace_back(acc_number, initial_balance);
            cout << "Account created successfully!" << '\n';
        }
        else if (choice == 2) {

            if (accounts.empty()) {
                cout << "No existing accounts. Please create a new account first." << '\n';
            }

            cout << "Choose account to perform actions on (1-" << accounts.size() << "): ";
            cin >> choice;

            if (choice >= 1 && static_cast<size_t>(choice) <= accounts.size()) {
                cout << "For account " << choice << ":" << '\n';
                bank_account_interface(accounts[choice - 1], accounts);
            }
            else {
                cout << "Invalid account choice." << '\n';
            }
        } else {
            cout << "Invalid choice." << '\n';
        }
    }
}