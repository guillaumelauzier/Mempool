#include <iostream>
#include <string>
#include <openssl/sha.h>  // For SHA256
#include <sstream>

struct Transaction {
    std::string sender;
    std::string receiver;
    int value;
    std::string signature;
};

std::string hashTransaction(const Transaction& tx) {
    std::string data = tx.sender + tx.receiver + std::to_string(tx.value);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data.c_str(), data.size(), hash);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << (int)hash[i];
    }
    return ss.str();
}

bool verifyTransaction(const Transaction& tx) {
    // Check for negative or zero value
    if (tx.value <= 0) {
        return false;
    }

    // Check if sender and receiver are valid (non-empty)
    if (tx.sender.empty() || tx.receiver.empty()) {
        return false;
    }

    // Verify the signature (In this example, it's a simple hash)
    if (tx.signature != hashTransaction(tx)) {
        return false;
    }

    // Further checks like checking the sender's balance can go here

    return true;
}

int main() {
    // Create a sample transaction
    Transaction tx;
    tx.sender = "Alice";
    tx.receiver = "Bob";
    tx.value = 100;
    tx.signature = hashTransaction(tx);  // For demonstration, assuming signature is just a hash

    // Verify the transaction
    if (verifyTransaction(tx)) {
        std::cout << "Transaction is valid.\n";
    } else {
        std::cout << "Transaction is invalid.\n";
    }

    // Modify transaction and re-verify
    tx.value = -100;
    if (verifyTransaction(tx)) {
        std::cout << "Transaction is valid.\n";
    } else {
        std::cout << "Transaction is invalid.\n";
    }

    return 0;
}
