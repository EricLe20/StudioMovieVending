#include <string>
#include <vector>
#include <iostream>

enum class AccountStatus { ACTIVE, FROZEN, CLOSED };
enum class AccountType { CHECKING, SAVINGS };

class Transaction {
protected:
    std::string transactionId;
    double amount;
public:
    Transaction(std::string id, double amt) : transactionId(id), amount(amt) {}
    virtual ~Transaction() = default;
    virtual void post() = 0;
};

class TransferTransaction : public Transaction {
private:
    std::string fromAccountNo, toAccountNo;
public:
    TransferTransaction(std::string id, double amt, std::string from, std::string to)
        : Transaction(id, amt), fromAccountNo(from), toAccountNo(to) {}
    void post() override { std::cout << "Transfer posted\n"; }
};

class Account {
protected:
    std::string accountNo;
    double balance;
    AccountStatus status;
    std::vector<Transaction*> transactions;
public:
    Account(std::string accNo, double initBal = 0.0)
        : accountNo(accNo), balance(initBal), status(AccountStatus::ACTIVE) {}
    virtual ~Account() { for (auto t : transactions) delete t; }
    
    std::string getAccountNo() const { return accountNo; }
    double getBalance() const { return balance; }
    AccountStatus getStatus() const { return status; }
    void setStatus(AccountStatus s) { status = s; }
    virtual void deposit(double amount) = 0;
    void addTransaction(Transaction* t) { transactions.push_back(t); }
};

class CheckingAccount : public Account {
private:
    double overdraftLimit;
public:
    CheckingAccount(std::string accNo, double initBal = 0.0, double limit = 500.0)
        : Account(accNo, initBal), overdraftLimit(limit) {}
    
    bool canWithdraw(double amount) const { return (balance + overdraftLimit) >= amount; }
    void deposit(double amount) override { if (amount > 0) balance += amount; }
    double getOverdraftLimit() const { return overdraftLimit; }
};

class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(std::string accNo, double initBal = 0.0, double rate = 0.02)
        : Account(accNo, initBal), interestRate(rate) {}
    
    void applyInterest() { balance += balance * interestRate; }
    void deposit(double amount) override { if (amount > 0) balance += amount; }
    double getInterestRate() const { return interestRate; }
};

class UserCredentials {
private:
    std::string username, passwordHash;
public:
    UserCredentials(std::string user, std::string pwd)
        : username(user), passwordHash(pwd) {}
    
    std::string getUsername() const { return username; }
    bool verifyPassword(std::string pwd) const { return pwd == passwordHash; }
};

class Customer {
private:
    int customerId;
    std::string fullName;
    UserCredentials* credentials;
    std::vector<Account*> accounts;
public:
    Customer(int id, std::string name, UserCredentials* creds)
        : customerId(id), fullName(name), credentials(creds) {}
    ~Customer() { delete credentials; for (auto a : accounts) delete a; }
    
    int getCustomerId() const { return customerId; }
    std::string getFullName() const { return fullName; }
    void addAccount(Account* account) { accounts.push_back(account); }
    std::vector<Account*> getAccounts() const { return accounts; }
};

class AuthService {
public:
    bool login(std::string username, std::string password) {
        return !username.empty() && !password.empty();
    }
};

class Bank {
private:
    std::string name, routingNumber;
    std::vector<Customer*> customers;
    std::vector<Account*> accounts;
public:
    Bank(std::string bankName, std::string routing)
        : name(bankName), routingNumber(routing) {}
    ~Bank() { for (auto c : customers) delete c; for (auto a : accounts) delete a; }
    
    std::string getName() const { return name; }
    void addCustomer(Customer* customer) { customers.push_back(customer); }
    void addAccount(Account* account) { accounts.push_back(account); }
    std::vector<Customer*> getCustomers() const { return customers; }
    std::vector<Account*> getAccounts() const { return accounts; }
};

int main() {
    Bank bank("Simple Bank", "123456");
    
    UserCredentials* creds = new UserCredentials("john_doe", "pass123");
    Customer* customer = new Customer(1, "John Doe", creds);
    
    CheckingAccount* checking = new CheckingAccount("CHK001", 1000, 500);
    SavingsAccount* savings = new SavingsAccount("SAV001", 5000, 0.03);
    
    customer->addAccount(checking);
    customer->addAccount(savings);
    
    bank.addCustomer(customer);
    bank.addAccount(checking);
    bank.addAccount(savings);
    
    checking->deposit(500);
    savings->deposit(1000);
    savings->applyInterest();
    
    TransferTransaction* transfer = new TransferTransaction("TXN001", 250, "CHK001", "SAV001");
    transfer->post();
    checking->addTransaction(transfer);
    
    std::cout << "Bank: " << bank.getName() << std::endl;
    std::cout << "Customer: " << customer->getFullName() << std::endl;
    std::cout << "Checking Balance: " << checking->getBalance() << std::endl;
    std::cout << "Savings Balance: " << savings->getBalance() << std::endl;
    
    return 0;
}