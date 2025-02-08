#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <ostream>
#include "useraccount.hpp"
#include "utility.hpp"

class Exchange {
private:
    std::unordered_map<std::string, UserAccount> users;
    std::vector<Order> order_book;
    std::vector<Trade> trade_history;
    void MatchOrders();

public:
    void MakeDeposit(const std::string &username, const std::string &asset, int amount);
    bool MakeWithdrawal(const std::string &username, const std::string &asset, int amount);
    bool AddOrder(const Order &order);
    void PrintUserPortfolios(std::ostream &os) const;
    void PrintUsersOrders(std::ostream &os) const;
    void PrintTradeHistory(std::ostream &os) const;
    void PrintBidAskSpread(std::ostream &os) const;
};
