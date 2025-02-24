#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_manager.h"

int initDatabase(const char *dbName, sqlite3 **db) {
    int rc = sqlite3_open(dbName, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return 0;
}

int createTransactionTable(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS transactions ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "type INTEGER, "
                      "amount REAL, "
                      "description TEXT);";
    char *errMsg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    }
    return SQLITE_OK;
}

int insertTransaction(sqlite3 *db, const Transaction *transaction) {
    const char *sql = "INSERT INTO transactions (id, type, amount, description) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    sqlite3_bind_int(stmt, 2, transaction->type);
    sqlite3_bind_double(stmt, 3, transaction->amount);
    sqlite3_bind_text(stmt, 4, transaction->description, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    return rc;
}

int getTransactions(sqlite3 *db, Transaction **transactions, int *count) {
    const char *sql = "SELECT id, type, amount, description FROM transactions;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch transactions: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    int capacity = 10;
    *transactions = malloc(capacity * sizeof(Transaction));
    *count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (*count >= capacity) {
            capacity *= 2;
            *transactions = realloc(*transactions, capacity * sizeof(Transaction));
        }
        Transaction t;
        t.id = sqlite3_column_int(stmt, 0);
        t.type = sqlite3_column_int(stmt, 1);
        t.amount = sqlite3_column_double(stmt, 2);
        const unsigned char *desc = sqlite3_column_text(stmt, 3);
        strncpy(t.description, (const char*)desc, DESCRIPTION_LENGTH - 1);
        t.description[DESCRIPTION_LENGTH - 1] = '\0';
        (*transactions)[*count] = t;
        (*count)++;
    }
    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

void closeDatabase(sqlite3 *db) {
    sqlite3_close(db);
}