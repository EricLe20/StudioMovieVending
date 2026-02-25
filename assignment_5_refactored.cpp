#include <iostream>
#include <stack>
#include <queue>

class Transaction {
public:
    enum Type { DEPOSIT, WITHDRAW };
    Transaction(Type type, double amount) : type(type), amount(amount) {}
    Type type;
    double amount;
};

class Account {
public:
    void deposit(double amount) {
        transactions.push(new Transaction(Transaction::DEPOSIT, amount));
    }

    void withdraw(double amount) {
        transactions.push(new Transaction(Transaction::WITHDRAW, amount));
    }

    void processTransactions() {
        while (!transactions.empty()) {
            Transaction* transaction = transactions.top();
            transactions.pop();
            std::cout << "Processing transaction: " << (transaction->type == Transaction::DEPOSIT ? "Deposit " : "Withdraw ") << transaction->amount << '\n';
            delete transaction;
        }
    }
private:
    std::stack<Transaction*> transactions;
};

class Customer {
public:
    void addAccount(Account* account) {
        accounts.push(account);
    }

    void processAccounts() {
        while (!accounts.empty()) {
            Account* account = accounts.front();
            accounts.pop();
            std::cout << "Processing account..." << '\n';
            account->processTransactions();
            delete account;
        }
    }
private:
    std::queue<Account*> accounts;
};

int main() {
    Customer customer;
    Account* account1 = new Account();
    account1->deposit(100);
    account1->withdraw(50);
    customer.addAccount(account1);

    Account* account2 = new Account();
    account2->deposit(200);
    customer.addAccount(account2);

    customer.processAccounts();
    return 0;
}