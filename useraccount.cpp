#include "useraccount.hpp"
#include <iostream>

UserAccount::UserAccount(const std::string &name) : username(name) {}

auto UserAccount::Deposit(const std::string &asset, int amount) -> bool {
    if (amount <= 0) return false;
    portfolio[asset] += amount;
    return true;
}

bool UserAccount::Withdraw(const std::string &asset, int amount) {
    auto it = portfolio.find(asset);
    if (amount <= 0 || it == portfolio.end() || it->second < amount) {
        return false;
    }
    portfolio[asset] -= amount;
    return true;
}

int UserAccount::GetBalance(const std::string &asset) const {
    auto it = portfolio.find(asset);
    if (it != portfolio.end()) {
        return it->second;
    }
    return 0;
}

void UserAccount::PrintPortfolio(std::ostream &os) const {
    os << "Portfolio of: " << username << std::endl;
    if (portfolio.empty()) {
        os << "No assets available.\n";
        return;
    }
    for (const auto &entry : portfolio) {
        os << "  Currency: " << entry.first << " | Amount: " << entry.second << std::endl;
    }
}
