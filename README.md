# c-money-manager

A simple command-line money management tool written in C using SQLite for data persistence.

## Description

`c-money-manager` allows users to track their income and expenses through a simple command-line interface. Transactions are stored in an SQLite database (`transactions.db`) created in the same directory where the program is run.

## Features

* Add new transactions (Income or Expense) with an amount and description.
* View a list of all recorded transactions.
* Calculate and display the current account balance based on recorded transactions.
* Persists transaction data using an SQLite database.

## Dependencies

* **GCC** (or any C compiler that supports C99 standard)
* **SQLite3** library and header files.

## How to Build

You need to have `gcc` and `sqlite3` development libraries installed.

1.  **Compile the object files:**
    ```bash
    gcc -c transaction/transaction.c -o transaction/transaction.o
    gcc -c db_manager/db_manager.c -o db_manager/db_manager.o -lsqlite3
    gcc -c main.c -o main.o
    ```

2.  **Link the object files to create the executable:**
    ```bash
    gcc main.o transaction/transaction.o db_manager/db_manager.o -o money_manager -lsqlite3
    ```
    *(Ensure the SQLite3 library (`-lsqlite3`) is correctly linked)*

## How to Run

After successful compilation, run the executable from your terminal:

```bash
./money_manager