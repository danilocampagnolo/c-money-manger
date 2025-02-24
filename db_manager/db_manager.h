#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "../transaction/transaction.h"
#include <sqlite3.h>

int initDatabase(const char *dbName, sqlite3 **db);
int createTransactionTable(sqlite3 *db);
int insertTransaction(sqlite3 *db, const Transaction *transaction);
int getTransactions(sqlite3 *db, Transaction **transactions, int *count);
void closeDatabase(sqlite3 *db);

#endif // DB_MANAGER_H