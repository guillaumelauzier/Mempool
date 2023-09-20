#include <iostream>
#include <unordered_set>
#include <string>

struct Transaction {
    std::string sender;
    std::string receiver;
    int amount;

    Transaction(std::string sender, std::string receiver, int amount)
        : sender(sender), receiver(receiver), amount(amount) {}

    // Hashing function for storing transactions in a set
    struct HashFunction {
        size_t operator()(const Transaction& tx) const {
            return std::hash<std::string>()(tx.sender) ^
                   std::hash<std::string>()(tx.receiver) ^
                   std::hash<int>()(tx.amount);
        }
    };

    // Equality function for storing transactions in a set
    bool operator==(const Transaction& other) const {
        return sender == other.sender &&
               receiver == other.receiver &&
               amount == other.amount;
    }
};

int main() {
    // Simulated mempool of pending transactions
    std::unordered_set<Transaction, Transaction::HashFunction> mempool;

    // Simulated blockchain of confirmed transactions
    std::unordered_set<Transaction, Transaction::HashFunction> blockchain;

    // Add a transaction to the blockchain
    Transaction tx1("Alice", "Bob", 50);
    blockchain.insert(tx1);

    // Attempt to add a duplicate transaction (double-spend)
    Transaction tx2("Alice", "Bob", 50);

    // Check for double-spending
    if (blockchain.find(tx2) != blockchain.end()) {
        std::cout << "Double-spend detected!" << std::endl;
    } else {
        std::cout << "Transaction is valid." << std::endl;
        blockchain.insert(tx2);  // Normally, you would not insert a detected double-spend
    }

    return 0;
}
