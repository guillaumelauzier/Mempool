#include <iostream>
#include <queue>

// Structure to represent a transaction
struct Transaction {
    int fee;
};

// Function to estimate fee
int estimateFee(int networkLoad) {
    int baseFee = 10;
    int extraFee = networkLoad / 10;

    return baseFee + extraFee;
}

int main() {
    std::queue<Transaction> mempool; // Mempool to store transactions

    // Simulate adding some transactions to the mempool
    mempool.push({15});
    mempool.push({12});
    mempool.push({18});
    mempool.push({10});

    // Get the current network load (modeled as the number of transactions in the mempool)
    int networkLoad = mempool.size();

    // Estimate fee based on the current network load
    int suggestedFee = estimateFee(networkLoad);

    std::cout << "Current network load: " << networkLoad << " transactions\n";
    std::cout << "Suggested transaction fee: " << suggestedFee << " units\n";

    return 0;
}
