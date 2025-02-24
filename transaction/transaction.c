#include <stdio.h>
#include <string.h>
#include "transaction.h"

Transaction createTransaction(TransactionType type, double amount, const char *description) {
    Transaction t;
    t.type = type;
    t.amount = amount;
    // Ensure the description fits into our fixed-size array
    strncpy(t.description, description, DESCRIPTION_LENGTH - 1);
    t.description[DESCRIPTION_LENGTH - 1] = '\0';
    return t;
}

void displayTransaction(const Transaction *transaction) {
    if (!transaction) return;
    const char *typeStr = (transaction->type == INCOME) ? "Income" : "Expense";
    printf("ID: %d\nType: %s\nAmount: %.2f\nDescription: %s\n\n", 
           transaction->id, typeStr, transaction->amount, transaction->description);
}