#include <iostream>
#include <queue>
#include <unordered_map>

// Structure to represent a transaction
struct Transaction {
    int id;
    int parent_id;
    Transaction(int id, int parent_id): id(id), parent_id(parent_id) {}
};

int main() {
    // Mempool to store valid transactions
    std::queue<Transaction> mempool;

    // Orphan pool to store orphan transactions
    std::queue<Transaction> orphanPool;

    // Hash table to quickly check if a transaction with a given ID is in the mempool
    std::unordered_map<int, bool> mempoolIndex;

    // Simulate adding some transactions to the mempool and orphan pool
    mempool.push(Transaction(1, 0));  // Transaction with ID 1, no parent
    mempoolIndex[1] = true;
    
    orphanPool.push(Transaction(2, 1));  // Transaction with ID 2, parent ID 1
    orphanPool.push(Transaction(3, 4));  // Transaction with ID 3, parent ID 4

    // New transaction arrives, gets added to the mempool
    Transaction newTx(4, 0);  // Transaction with ID 4, no parent
    mempool.push(newTx);
    mempoolIndex[4] = true;

    // Check if any transactions in the orphan pool can be moved to the mempool
    std::queue<Transaction> tempOrphanPool;

    while (!orphanPool.empty()) {
        Transaction orphan = orphanPool.front();
        orphanPool.pop();

        if (mempoolIndex.find(orphan.parent_id) != mempoolIndex.end()) {
            // Parent found, move to mempool
            mempool.push(orphan);
            mempoolIndex[orphan.id] = true;
        } else {
            // Parent not found, keep in orphan pool
            tempOrphanPool.push(orphan);
        }
    }

    // Replace old orphanPool with tempOrphanPool
    orphanPool = tempOrphanPool;

    // Print contents of mempool
    std::cout << "Transactions in mempool: ";
    while (!mempool.empty()) {
        Transaction tx = mempool.front();
        mempool.pop();
        std::cout << tx.id << " ";
    }
    std::cout << std::endl;

    // Print contents of orphan pool
    std::cout << "Transactions in orphan pool: ";
    while (!orphanPool.empty()) {
        Transaction orphan = orphanPool.front();
        orphanPool.pop();
        std::cout << orphan.id << " ";
    }
    std::cout << std::endl;

    return 0;
}
