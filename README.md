# **Bonus Project – Cryptocurrency Exchange Simulator**

A **C++ cryptocurrency exchange simulator** that enables users to deposit funds, place buy/sell orders, and execute trades. The system automatically **matches orders**, **maintains trade history**, and **calculates bid-ask spreads** to simulate a real-world trading environment.  


## **Project Structure**  

```
📁 Bonus_Project/
│── 📄 main.cpp          # Entry point of the program
│── 📄 exchange.cpp      # Order book, trade matching, and transaction processing
│── 📄 exchange.hpp      # Header file for Exchange class
│── 📄 useraccount.cpp   # Handles user balances and transactions
│── 📄 useraccount.hpp   # Header file for UserAccount class
│── 📄 utility.cpp       # Utility functions and operator overloads
│── 📄 utility.hpp       # Header file for utility functions
│── 📄 CMakeLists.txt    # CMake configuration for building the project
└── 📄 README.md         # Project documentation (this file)
```

---

## ⚙**Installation & Compilation**  

### **Prerequisites**  
- C++17 or later  
- CMake (for build management)  


## 📜 **Usage**  

### **Deposit & Withdraw Funds**
Users can deposit and withdraw various assets:  
```cpp
msu_base.MakeDeposit("Alice", "USD", 5000);
msu_base.MakeWithdrawal("Alice", "BTC", 2);
```

### **Placing Orders**  
Users can place **Buy/Sell** orders:  
```cpp
msu_base.AddOrder({"Alice", "Buy", "BTC", 2, 30000});
msu_base.AddOrder({"Bob", "Sell", "BTC", 1, 29900});
```

### **Trade Execution**  
- The system **automatically matches** buy/sell orders based on price.  
- If a matching order is found, a trade executes immediately.  

### **Displaying Data**  
- View **user portfolios**:  
  ```cpp
  msu_base.PrintUserPortfolios(std::cout);
  ```
- View **active and filled orders**:  
  ```cpp
  msu_base.PrintUsersOrders(std::cout);
  ```
- View **trade history**:  
  ```cpp
  msu_base.PrintTradeHistory(std::cout);
  ```
- View **market bid-ask spread**:  
  ```cpp
  msu_base.PrintBidAskSpread(std::cout);
  ```
