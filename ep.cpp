#include <iostream>
#include <queue>
#include <vector>
#include <ctime>

enum EvictionPolicy {
    LowestFeeFirst,
    OldestFirst
};

struct Transaction {
    int id;
    double fee;
    std::time_t timestamp;

    Transaction(int id, double fee, std::time_t timestamp) : id(id), fee(fee), timestamp(timestamp) {}

    // This comparator sorts by fee, then by time (oldest first)
    bool operator<(const Transaction& other) const {
        return (fee < other.fee) || (fee == other.fee && timestamp > other.timestamp);
    }
};

class Mempool {
private:
    std::priority_queue<Transaction> transactions;
    size_t maxSize;
    EvictionPolicy policy;

public:
    Mempool(size_t maxSize, EvictionPolicy policy) : maxSize(maxSize), policy(policy) {}

    // Add a transaction to the mempool
    void addTransaction(const Transaction& tx) {
        if (transactions.size() < maxSize) {
            transactions.push(tx);
        } else {
            // Evict based on the current policy
            if ((policy == LowestFeeFirst && tx.fee > transactions.top().fee) ||
                (policy == OldestFirst && tx.timestamp < transactions.top().timestamp)) {
                transactions.pop();  // Evict
                transactions.push(tx);
            }
            // Otherwise, reject the incoming transaction
        }
    }

    // Print the contents of the mempool
    void printMempool() const {
        std::priority_queue<Transaction> temp = transactions;

        while (!temp.empty()) {
            std::cout << "Transaction ID: " << temp.top().id
                      << ", Fee: " << temp.top().fee
                      << ", Timestamp: " << temp.top().timestamp
                      << std::endl;
            temp.pop();
        }
    }
};

int main() {
    Mempool mempool(5, LowestFeeFirst);  // Mempool size limit set to 5 and using LowestFeeFirst policy

    mempool.addTransaction(Transaction(1, 5.0, std::time(nullptr)));
    mempool.addTransaction(Transaction(2, 3.0, std::time(nullptr)));
    mempool.addTransaction(Transaction(3, 7.0, std::time(nullptr)));
    mempool.addTransaction(Transaction(4, 1.0, std::time(nullptr)));
    mempool.addTransaction(Transaction(5, 4.0, std::time(nullptr)));

    std::cout << "Initial Mempool:" << std::endl;
    mempool.printMempool();

    std::cout << "\nAfter adding a high fee transaction:" << std::endl;
    mempool.addTransaction(Transaction(6, 10.0, std::time(nullptr)));
    mempool.printMempool();

    return 0;
}
