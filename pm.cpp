#include <iostream>
#include <queue>
#include <string>
#include <mutex>
#include <functional>

// Transaction structure with an additional "fee" field
struct Transaction {
    std::string txID;
    std::string sender;
    std::string receiver;
    int value;
    int fee;  // Transaction fee (higher value means higher priority)

    // Operator overload for priority comparison based on fee
    bool operator<(const Transaction& other) const {
        return fee < other.fee;
    }
};

class PriorityTransactionQueue {
private:
    std::priority_queue<Transaction, std::vector<Transaction>, std::less<Transaction>> txQueue;
    std::mutex mtx;

public:
    // Enqueue transaction, highest fee at the top
    void enqueue(const Transaction& tx) {
        std::lock_guard<std::mutex> lock(mtx);
        txQueue.push(tx);
    }

    // Dequeue transaction, remove the transaction with the highest fee
    Transaction dequeue() {
        std::lock_guard<std::mutex> lock(mtx);
        if (txQueue.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        Transaction tx = txQueue.top();
        txQueue.pop();
        return tx;
    }

    // Check if the queue is empty
    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        return txQueue.empty();
    }
};

int main() {
    PriorityTransactionQueue pQueue;

    // Sample transactions with varying fees
    Transaction tx1 = {"tx1", "Alice", "Bob", 100, 2};
    Transaction tx2 = {"tx2", "Bob", "Charlie", 50, 3};
    Transaction tx3 = {"tx3", "Charlie", "Dave", 25, 1};

    // Enqueue transactions
    pQueue.enqueue(tx1);
    pQueue.enqueue(tx2);
    pQueue.enqueue(tx3);

    // Dequeue transactions (should come out in order of highest to lowest fee)
    while (!pQueue.isEmpty()) {
        Transaction tx = pQueue.dequeue();
        std::cout << "Processed Transaction: " << tx.txID << ", Fee: " << tx.fee << std::endl;
    }

    return 0;
}
