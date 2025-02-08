#pragma once
#include <string>
#include <map>
#include <ostream>

class UserAccount {
private:
    std::string username;
    std::map<std::string, int> portfolio;  // Asset -> Amount

public:
    UserAccount(const std::string &name = "");
    bool Deposit(const std::string &asset, int amount);
    bool Withdraw(const std::string &asset, int amount);
    int GetBalance(const std::string &asset) const;  // Added this
    std::map<std::string, int> GetPortfolio() const { return portfolio; }
    void PrintPortfolio(std::ostream &os) const;
};
