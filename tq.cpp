#include <iostream>
#include <queue>
#include <string>
#include <mutex>

// Simple Transaction structure
struct Transaction {
    std::string txID;
    std::string sender;
    std::string receiver;
    int value;
};

class TransactionQueue {
private:
    std::queue<Transaction> txQueue; // Transaction Queue
    std::mutex mtx; // Mutex for thread safety

public:
    // Add a transaction to the queue
    void enqueue(const Transaction& tx) {
        std::lock_guard<std::mutex> lock(mtx);
        txQueue.push(tx);
    }

    // Remove and return the next transaction from the queue
    Transaction dequeue() {
        std::lock_guard<std::mutex> lock(mtx);
        if (txQueue.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        Transaction tx = txQueue.front();
        txQueue.pop();
        return tx;
    }

    // Check if the queue is empty
    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        return txQueue.empty();
    }

    // Get the number of transactions in the queue
    size_t size() {
        std::lock_guard<std::mutex> lock(mtx);
        return txQueue.size();
    }
};

int main() {
    TransactionQueue txQueue;

    // Sample transactions
    Transaction tx1 = {"tx1", "Alice", "Bob", 100};
    Transaction tx2 = {"tx2", "Bob", "Charlie", 50};
    Transaction tx3 = {"tx3", "Charlie", "Dave", 25};

    // Enqueue transactions
    txQueue.enqueue(tx1);
    txQueue.enqueue(tx2);
    txQueue.enqueue(tx3);

    // Dequeue and display transactions
    while (!txQueue.isEmpty()) {
        Transaction tx = txQueue.dequeue();
        std::cout << "Processed Transaction: " << tx.txID << std::endl;
        std::cout << "Sender: " << tx.sender << ", Receiver: " << tx.receiver << ", Value: " << tx.value << std::endl;
    }

    return 0;
}
