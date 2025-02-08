#include "Exchange.h"
#include <algorithm>

// Deposit funds into a user's portfolio
void Exchange::MakeDeposit(const std::string &username, const std::string &asset, int amount) {
    if (amount <= 0) return;
    users[username].Deposit(asset, amount);
}

// Withdraw funds from a user's portfolio
bool Exchange::MakeWithdrawal(const std::string &username, const std::string &asset, int amount) {
    if (amount <= 0) return false;
    auto it = users.find(username);
    if (it == users.end()) return false;
    return it->second.Withdraw(asset, amount);
}

// Add an order to the order book
bool Exchange::AddOrder(const Order &order) {
    if (order.amount <= 0 || order.price <= 0 ||
        (order.side != "Buy" && order.side != "Sell") ||
        !users.count(order.username)) {
        return false;
    }

    if (order.side == "Buy" && users[order.username].GetBalance("USD") < order.amount * order.price) {
        return false;
    }

    if (order.side == "Sell" && users[order.username].GetBalance(order.asset) < order.amount) {
        return false;
    }

    if (order.side == "Buy") {
        users[order.username].Withdraw("USD", order.amount * order.price);
    } else {
        users[order.username].Withdraw(order.asset, order.amount);
    }

    order_book.push_back(order);
    MatchOrders();
    return true;
}

// Match buy and sell orders in the order book
void Exchange::MatchOrders() {
    std::vector<size_t> to_remove;
    for (size_t i = 0; i < order_book.size(); ++i) {
        for (size_t j = i + 1; j < order_book.size(); ++j) {
            auto &buy = (order_book[i].side == "Buy") ? order_book[i] : order_book[j];
            auto &sell = (order_book[i].side == "Sell") ? order_book[i] : order_book[j];

            if (buy.asset == sell.asset && buy.side == "Buy" && sell.side == "Sell" && buy.price >= sell.price) {
                int trade_amount = std::min(buy.amount, sell.amount);
                int trade_price = sell.price;

                users[buy.username].Deposit(buy.asset, trade_amount);
                users[sell.username].Deposit("USD", trade_amount * trade_price);

                trade_history.push_back({buy.username, sell.username, buy.asset, trade_amount, trade_price});

                buy.amount -= trade_amount;
                sell.amount -= trade_amount;

                if (buy.amount == 0) {
                    to_remove.push_back(i);
                }
                if (sell.amount == 0) {
                    to_remove.push_back(j);
                }
            }
        }
    }
}

// Print user portfolios
void Exchange::PrintUserPortfolios(std::ostream &os) const {
    os << "User Portfolios (in alphabetical order):\n";

    std::vector<std::string> sorted_users;

    for (const auto &[username, _] : users) {
        sorted_users.push_back(username);
    }
    std::sort(sorted_users.begin(), sorted_users.end());

    for (const auto &username : sorted_users) {
        const auto &portfolio = users.at(username).GetPortfolio();
        os << username << "'s Portfolio: ";

        bool has_assets = false;
        for (const auto &[asset, amount] : portfolio) {
            if (amount > 0) {
                if (has_assets) os << ", ";
                os << amount << " " << asset;
                has_assets = true;
            }
        }
        os << (has_assets ? ", \n" : "\n");
    }
}

// Print all users' orders
void Exchange::PrintUsersOrders(std::ostream &os) const {
    os << "Users Orders (in alphabetical order):\n";

    std::vector<std::string> sorted_users;
    for (const auto &[username, _] : users) {
        sorted_users.push_back(username);
    }
    std::sort(sorted_users.begin(), sorted_users.end());

    for (const auto &username : sorted_users) {
        os << username << "'s Open Orders (in chronological order):\n";

        for (const auto &order : order_book) {
            if (order.username == username && order.amount > 0) {
                os << order.side << " " << order.amount << " " << order.asset
                   << " at " << order.price << " USD by " << username << "\n";
            }
        }

        os << username << "'s Filled Orders (in chronological order):\n";
        for (const auto &trade : trade_history) {
            if (trade.buyer_username == username || trade.seller_username == username) {
                os << trade.amount << " " << trade.asset << " at "
                   << trade.price << " USD by " << username << "\n";
            }
        }
    }
}

// Print trade history
void Exchange::PrintTradeHistory(std::ostream &os) const {
    if (trade_history.empty()) {
        os << "No trade history available.\n";
        return;
    }
    os << "Trade History:\n";
    for (const auto &trade : trade_history) {
        os << "Buyer: " << trade.buyer_username
           << ", Seller: " << trade.seller_username
           << ", Asset: " << trade.asset
           << ", Amount: " << trade.amount
           << ", Price: $" << trade.price << "\n";
    }
}

// Print bid-ask spread
void Exchange::PrintBidAskSpread(std::ostream &os) const {
    std::map<std::string, int> highest_bid;
    std::map<std::string, int> lowest_ask;

    for (const auto &order : order_book) {
        if (order.side == "Buy") {
            highest_bid[order.asset] = std::max(highest_bid[order.asset], order.price);
        } else if (order.side == "Sell") {
            if (lowest_ask[order.asset] == 0 || order.price < lowest_ask[order.asset]) {
                lowest_ask[order.asset] = order.price;
            }
        }
    }

    os << "Asset Bid Ask Spread (in alphabetical order):\n";
    for (const auto &[asset, bid] : highest_bid) {
        os << asset << ": Highest Open Buy = "
           << (bid == 0 ? "NA" : std::to_string(bid))
           << " USD and Lowest Open Sell = "
           << (lowest_ask[asset] == 0 ? "NA" : std::to_string(lowest_ask[asset]))
           << " USD\n";
    }
}

