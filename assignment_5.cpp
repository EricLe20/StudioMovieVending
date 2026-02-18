#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

enum class AccountType {
    CHECKING,
    SAVINGS
};

#endif

#ifndef ACCOUNTSTATUS_H
#define ACCOUNTSTATUS_H

enum class AccountStatus {
    ACTIVE,
    FROZEN,
    CLOSED
};

#endif

#include <string>
#include <vector>
#include <ctime>

// ==================== Transaction ====================
class Transaction {
protected:
    std::string transactionId;
    double amount;

public:
    Transaction(std::string id, double amt)
        : transactionId(id), amount(amt) {}
    virtual ~Transaction() = default;
    
    std::string getTransactionId() const {
        return transactionId;
    }
    
    double getAmount() const {
        return amount;
    }
    
    virtual void post() = 0;
};

// ==================== TransferTransaction ====================
class TransferTransaction : public Transaction {
private:
    std::string fromAccountNo;
    std::string toAccountNo;

public:
    TransferTransaction(std::string id, double amt, std::string from, std::string to)
        : Transaction(id, amt), fromAccountNo(from), toAccountNo(to) {}
    
    std::string getFromAccountNo() const {
        return fromAccountNo;
    }
    
    std::string getToAccountNo() const {
        return toAccountNo;
    }
    
    void post() override {
        // Implementation for posting transfer transaction
    }
};

// ==================== UserCredentials ====================
class UserCredentials {
private:
    std::string username;
    std::string passwordHash;
    time_t lastLogin;

public:
    UserCredentials(std::string user, std::string pwd)
        : username(user), passwordHash(pwd), lastLogin(0) {}
    
    std::string getUsername() const {
        return username;
    }
    
    std::string getPasswordHash() const {
        return passwordHash;
    }
    
    time_t getLastLogin() const {
        return lastLogin;
    }
    
    void setLastLogin(time_t login) {
        lastLogin = login;
    }
    
    bool verifyPassword(std::string pwd) const {
        return pwd == passwordHash;
    }
};

// ==================== Account ====================
class Account {
protected:
    std::string accountNo;
    double balance;
    AccountStatus status;
    std::vector<Transaction*> transactions;

public:
    Account(std::string accNo, double initialBalance = 0.0)
        : accountNo(accNo), balance(initialBalance), status(AccountStatus::ACTIVE) {}
    
    virtual ~Account() {
        for (auto trans : transactions) {
            delete trans;
        }
    }
    
    std::string getAccountNo() const {
        return accountNo;
    }
    
    double getBalance() const {
        return balance;
    }
    
    AccountStatus getStatus() const {
        return status;
    }
    
    void setStatus(AccountStatus s) {
        status = s;
    }
    
    virtual void deposit(double amount) = 0;
    virtual double getBalanceVirtual() = 0;
    
    void addTransaction(Transaction* transaction) {
        transactions.push_back(transaction);
    }
    
    std::vector<Transaction*> getTransactions() const {
        return transactions;
    }
};

// ==================== CheckingAccount ====================
class CheckingAccount : public Account {
protected:
    double overdraftLimit;

public:
    CheckingAccount(std::string accNo, double initialBalance = 0.0, double limit = 500.0)
        : Account(accNo, initialBalance), overdraftLimit(limit) {}
    
    double getOverdraftLimit() const {
        return overdraftLimit;
    }
    
    void setOverdraftLimit(double limit) {
        overdraftLimit = limit;
    }
    
    bool canWithdraw(double amount) const {
        return (balance + overdraftLimit) >= amount;
    }
    
    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalanceVirtual() override {
        return balance;
    }
};

// ==================== SavingsAccount ====================
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(std::string accNo, double initialBalance = 0.0, double rate = 0.02)
        : Account(accNo, initialBalance), interestRate(rate) {}
    
    double getInterestRate() const {
        return interestRate;
    }
    
    void setInterestRate(double rate) {
        interestRate = rate;
    }
    
    void applyInterest() {
        balance += balance * interestRate;
    }
    
    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalanceVirtual() override {
        return balance;
    }
};

// ==================== InterestAccount ====================
class InterestAccount : public CheckingAccount {
public:
    InterestAccount(std::string accNo, double initialBalance = 0.0)
        : CheckingAccount(accNo, initialBalance) {}
    
    Transaction* depositWithTransaction(double accountNo, double amount) {
        // Implementation for deposit with transaction tracking
        return nullptr;
    }
};

// ==================== Customer ====================
class Customer {
private:
    int customerId;
    std::string fullName;
    UserCredentials* credentials;
    std::vector<Account*> accounts;

public:
    Customer(int id, std::string name, UserCredentials* creds)
        : customerId(id), fullName(name), credentials(creds) {}
    
    ~Customer() {
        delete credentials;
        for (auto acc : accounts) {
            delete acc;
        }
    }
    
    int getCustomerId() const {
        return customerId;
    }
    
    std::string getFullName() const {
        return fullName;
    }
    
    UserCredentials* getCredentials() const {
        return credentials;
    }
    
    void addAccount(Account* account) {
        accounts.push_back(account);
    }
    
    std::vector<Account*> getAccounts() const {
        return accounts;
    }
};

// ==================== AuthService ====================
class AuthService {
public:
    Customer* login(std::string username, std::string password) {
        // Implementation for login
        return nullptr;
    }
    
    void logout() {
        // Implementation for logout
    }
    
    bool verifyCredentials(std::string username, std::string password) {
        // Implementation for credential verification
        return false;
    }
};

// ==================== Bank ====================
class Bank {
private:
    std::string name;
    std::string routingNumber;
    std::vector<Customer*> customers;
    std::vector<Account*> accounts;

public:
    Bank(std::string bankName, std::string routing)
        : name(bankName), routingNumber(routing) {}
    
    ~Bank() {
        for (auto cust : customers) {
            delete cust;
        }
        for (auto acc : accounts) {
            delete acc;
        }
    }
    
    std::string getName() const {
        return name;
    }
    
    std::string getRoutingNumber() const {
        return routingNumber;
    }
    
    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }
    
    void addAccount(Account* account) {
        accounts.push_back(account);
    }
    
    std::vector<Customer*> getCustomers() const {
        return customers;
    }
    
    std::vector<Account*> getAccounts() const {
        return accounts;
    }
};

// ==================== Main Function ====================
int main() {
    // Example usage of the banking application
    
    // Create a bank
    Bank myBank("Simple Bank", "123456789");
    
    // Create customer with credentials
    UserCredentials* creds = new UserCredentials("john_doe", "password123");
    Customer* customer = new Customer(1, "John Doe", creds);
    
    // Create accounts
    CheckingAccount* checkingAcc = new CheckingAccount("ACC001", 1000.0, 500.0);
    SavingsAccount* savingsAcc = new SavingsAccount("ACC002", 5000.0, 0.03);
    
    // Add accounts to customer
    customer->addAccount(checkingAcc);
    customer->addAccount(savingsAcc);
    
    // Add customer and accounts to bank
    myBank.addCustomer(customer);
    myBank.addAccount(checkingAcc);
    myBank.addAccount(savingsAcc);
    
    // Perform transactions
    checkingAcc->deposit(500.0);
    savingsAcc->deposit(1000.0);
    savingsAcc->applyInterest();
    
    // Create a transfer transaction
    TransferTransaction* transfer = new TransferTransaction(
        "TXN001", 
        250.0, 
        "ACC001", 
        "ACC002"
    );
    transfer->post();
    
    return 0;
}