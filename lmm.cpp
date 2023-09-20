#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <unordered_set>

struct Transaction {
    int id;
    // Additional fields like fee, timestamp, etc. could be added here.

    Transaction(int id) : id(id) {}

    bool operator==(const Transaction& other) const {
        return id == other.id;
    }
};

struct TransactionHash {
    std::size_t operator()(const Transaction& tx) const {
        return std::hash<int>{}(tx.id);
    }
};

class LocalMempool {
private:
    std::unordered_set<Transaction, TransactionHash> transactions;

public:
    // Add a transaction to the local mempool
    void addTransaction(const Transaction& tx) {
        transactions.insert(tx);
    }

    // Simulate sharing transactions with another local mempool (node)
    void shareWith(LocalMempool& other) {
        for (const auto& tx : transactions) {
            other.addTransaction(tx);
        }
    }

    // Print the contents of the local mempool
    void printMempool() const {
        std::cout << "Local Mempool: ";
        for (const auto& tx : transactions) {
            std::cout << tx.id << ' ';
        }
        std::cout << std::endl;
    }
};

int main() {
    // Initialize three local mempools (nodes)
    LocalMempool node1, node2, node3;

    // Add transactions to the first node
    node1.addTransaction(Transaction(1));
    node1.addTransaction(Transaction(2));

    // Add transactions to the second node
    node2.addTransaction(Transaction(3));

    // Initially, all mempools are different
    std::cout << "Initial state:" << std::endl;
    node1.printMempool();
    node2.printMempool();
    node3.printMempool();

    // Simulate transaction propagation in the network
    node1.shareWith(node2);
    node2.shareWith(node3);

    std::cout << "\nAfter transaction propagation:" << std::endl;
    node1.printMempool();
    node2.printMempool();
    node3.printMempool();

    return 0;
}
