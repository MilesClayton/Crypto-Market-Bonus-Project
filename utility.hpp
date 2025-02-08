#pragma once
#include <iostream>
#include <string>

struct Order {
  std::string username;
  std::string side;  // Can be "Buy" or "Sell"
  std::string asset;
  int amount;
  int price;
  bool operator==(const Order& other) const;
  friend std::ostream& operator<<(std::ostream& os, const Order& order);

};

struct Trade {
  std::string buyer_username;
  std::string seller_username;
  std::string asset;
  int amount;
  int price;
};