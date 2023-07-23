#ifndef ACCOUNT_H
#define ACCOUNT_H

class account
{
    // Private member variables
    char name[100], fathername[100], address[100], type[10];
    float balance;
    int acno;

public:
    // Member functions declaration
    void open_account();    // Create account
    void deposit_money();   // Deposit money
    void withdraw_money();  // Subtract withdrawn amount from balance
    void display_account(); // Display account info
    void modify_account();  // Modify account info
    void write_account();   // Write record to binary file
    void display_sp(int);   // Display acc details given by the user
    void modify_acc(int);   // Modify record of the file
    void delete_account(int); // Delete record of the file
    void display_all();     // Display all account details
    int retacno() const;    // Retrieve the account number
    void report() const;    // Function to show data in tabular format
};

#endif

