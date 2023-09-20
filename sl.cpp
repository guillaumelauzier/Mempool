#include <iostream>
#include <queue>
#include <vector>

struct Transaction {
    int id;
    double fee;

    Transaction(int id, double fee) : id(id), fee(fee) {}

    // Operator to allow priority_queue to sort by fee, with highest fee at the top
    bool operator<(const Transaction& other) const {
        return fee < other.fee;
    }
};

class Mempool {
private:
    std::priority_queue<Transaction> transactions;
    size_t maxSize;

public:
    Mempool(size_t maxSize) : maxSize(maxSize) {}

    // Add a transaction to the mempool
    void addTransaction(const Transaction& tx) {
        if (transactions.size() < maxSize) {
            transactions.push(tx);
        } else {
            // If the new transaction has a higher fee than the lowest in the mempool
            if (tx.fee > transactions.top().fee) {
                transactions.pop();  // Evict the lowest-fee transaction
                transactions.push(tx);
            }
            // Otherwise, reject the incoming transaction (not added to the mempool)
        }
    }

    // Print the contents of the mempool
    void printMempool() const {
        std::priority_queue<Transaction> temp = transactions;

        while (!temp.empty()) {
            std::cout << "Transaction ID: " << temp.top().id << ", Fee: " << temp.top().fee << std::endl;
            temp.pop();
        }
    }
};

int main() {
    Mempool mempool(5);  // Mempool size limit set to 5

    mempool.addTransaction(Transaction(1, 5.0));
    mempool.addTransaction(Transaction(2, 3.0));
    mempool.addTransaction(Transaction(3, 7.0));
    mempool.addTransaction(Transaction(4, 1.0));
    mempool.addTransaction(Transaction(5, 4.0));

    std::cout << "Initial Mempool:" << std::endl;
    mempool.printMempool();

    std::cout << "\nAfter adding a high fee transaction:" << std::endl;
    mempool.addTransaction(Transaction(6, 10.0));
    mempool.printMempool();

    return 0;
}
