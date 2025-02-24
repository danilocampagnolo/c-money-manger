#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction/transaction.h"
#include "db_manager/db_manager.h"


double calculateBalance(const Transaction *transactions, int count) {
    double balance = 0.0;
    for (int i = 0; i < count; i++) {
        if (transactions[i].type == INCOME)
            balance += transactions[i].amount;
        else
            balance -= transactions[i].amount;
    }
    return balance;
}

int main(void) {
    sqlite3 *db;
    
    if (initDatabase("transactions.db", &db) != 0) {
        fprintf(stderr, "Database initialization failed.\n");
        return 1;
    }
    
    createTransactionTable(db);

    int choice;
    while (1) {
        printf("\n=== Money Manager Menu ===\n");
        printf("1. Insert new transaction\n");
        printf("2. View all transactions\n");
        printf("3. Calculate balance\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            int id;
            int type;
            double amount;
            char description[DESCRIPTION_LENGTH];

            printf("Enter transaction type (0 for INCOME, 1 for EXPENSE): ");
            scanf("%d", &type);
            getchar();

            printf("Enter amount: ");
            scanf("%lf", &amount);
            getchar();

            printf("Enter description: ");
            fgets(description, DESCRIPTION_LENGTH, stdin);

            description[strcspn(description, "\n")] = '\0';

            Transaction t = createTransaction((TransactionType)type, amount, description);
            if (insertTransaction(db, &t) == SQLITE_DONE) {
                printf("Transaction inserted successfully.\n");
            } else {
                printf("Error inserting transaction.\n");
            }
        } else if (choice == 2) {
            Transaction *transactions = NULL;
            int count = 0;
            if (getTransactions(db, &transactions, &count) == SQLITE_OK && count > 0) {
                printf("\nLoaded %d transactions:\n", count);
                for (int i = 0; i < count; i++) {
                    displayTransaction(&transactions[i]);
                }
                free(transactions);
            } else {
                printf("No transactions found.\n");
            }
        } else if (choice == 3) {
            Transaction *transactions = NULL;
            int count = 0;
            if (getTransactions(db, &transactions, &count) == SQLITE_OK && count > 0) {
                double balance = calculateBalance(transactions, count);
                printf("Current Balance: %.2f\n", balance);
                free(transactions);
            } else {
                printf("No transactions to calculate balance.\n");
            }
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    closeDatabase(db);
    return 0;
}