#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdbool.h>

#define DESCRIPTION_LENGTH 100

typedef enum {
    INCOME,
    EXPENSE
} TransactionType;

typedef struct {
    int id;
    TransactionType type;
    double amount;
    char description[DESCRIPTION_LENGTH];
} Transaction;


Transaction createTransaction(TransactionType type, double amount, const char *description);


void displayTransaction(const Transaction *transaction);

#endif