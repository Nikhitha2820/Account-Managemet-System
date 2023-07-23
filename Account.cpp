#include "Account.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void account::open_account()
{
    std::cout << "\nEnter the Account No: ";
    std::cin >> acno;

    std::cout << "\nEnter your Full Name: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "\nEnter your Father Name: ";
    std::cin.getline(fathername, 100);

    std::cout << "\nEnter your Address: ";
    std::cin.getline(address, 100);

    std::cout << "\nChoose the type of account savings(s) or current(c): ";
    std::cin.getline(type, 10);

    std::cout << "\nEnter amount you want to deposit: ";
    std::cin >> balance;

    std::cout << "\nYour account is created successfully!" << std::endl;
}

void account::deposit_money()
{
    float dep;
    std::cout << "\nEnter the amount you want to deposit: ";
    std::cin >> dep;

    balance = balance + dep;
    std::cout << "\nYour current balance is: " << balance << std::endl;
}

void account::withdraw_money()
{
    float wd;
    std::cout << "\nEnter amount you want to withdraw: ";
    std::cin >> wd;

    if (balance >= wd)
    {
        balance = balance - wd;
        std::cout << "\nYour remaining balance is: " << balance << std::endl;
    }
    else
    {
        std::cout << "\nInsufficient balance!" << std::endl;
    }
}

void account::display_account()
{
    std::cout << "\nAccount Number: " << acno << std::endl;
    std::cout << "Name of Account Holder: " << name << std::endl;
    std::cout << "Father Name: " << fathername << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Type of Account: " << type << std::endl;
    std::cout << "Current/Total Balance: " << balance << std::endl;
}

void account::modify_account()
{
    std::cout << "\nAccount No: " << acno;
    std::cout << "\nModify Account Holder Name: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "Modify Type of Account: ";
    std::cin.getline(type, 10);

    std::cout << "Modify Account Balance: ";
    std::cin >> balance;
}

int account::retacno() const
{
    return acno;
}

void account::report() const
{
    std::cout << acno << std::setw(10) << " " << name << std::setw(10) << " " << type << std::setw(6) << balance << std::endl;
}

void account::write_account()
{
    std::ofstream outFile("account.bin", std::ios::binary | std::ios::app);

    if (!outFile)
    {
        std::cout << "Error in creating file..";
        return;
    }

    account ac;
    ac.open_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

void account::display_sp(int n)
{
    bool flag = false;
    account ac;
    std::ifstream inFile("account.bin", std::ios::binary);

    if (!inFile)
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    std::cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.display_account();
            flag = true;
        }
    }

    inFile.close();
    if (!flag)
    {
        std::cout << "\n\nAccount number does not exist" << std::endl;
    }
}

void account::modify_acc(int n)
{
    bool found = false;
    account ac;
    std::fstream File("account.bin", std::ios::binary | std::ios::in | std::ios::out);

    if (!File)
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    while (!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.display_account();
            std::cout << "\nEnter The New Details of the account" << std::endl;
            ac.modify_account();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();

    if (!found)
    {
        std::cout << "\n\n Record Not Found";
    }
}

void account::delete_account(int n)
{
    account ac;
    std::ifstream inFile("account.bin", std::ios::binary);
    if (!inFile)
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    std::ofstream outFile("Temp.bin", std::ios::binary);
    inFile.seekg(0, std::ios::beg);

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }

    inFile.close();
    outFile.close();
    remove("account.bin");
    rename("Temp.bin", "account.bin");
    std::cout << "\n\n\tRecord Deleted..";
}

void account::display_all()
{
    account ac;
    std::ifstream inFile("account.bin", std::ios::binary);

    if (!inFile)
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    std::cout << "\n\nACCOUNT HOLDER LIST\n\n";
    std::cout << "====================================================\n";
    std::cout << "A/c no.       NAME           Type  Balance\n";
    std::cout << "====================================================\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }

    inFile.close();
}

int main()
{
    account b;
    int ch, num;
    char option;

    std::cout << "\n<------------------------------------------------------>" << std::endl;
    std::cout << "<---------------Welcome to our services----------------->" << std::endl;
    std::cout << "<------------------------------------------------------>" << std::endl;

    do
    {
        system("cls");
        std::cout << "\nMain Menu";
        std::cout << "\n1.) Open Account";
        std::cout << "\n2.) Deposit Money";
        std::cout << "\n3.) Withdraw Money";
        std::cout << "\n4.) Display Account";
        std::cout << "\n5.) Close Account";
        std::cout << "\n6.) Modify Existing Account";
        std::cout << "\n7.) Display All Accounts";
        std::cout << "\n8.) Exit";
        std::cout << "\n\nSelect your option (1-8): ";
        std::cin >> ch;

        system("cls");

        switch (ch)
        {
        case 1:
            std::cout << "\n1.) Open Account" << std::endl;
            b.write_account();
            break;
        case 2:
            std::cout << "\n2.) Deposit Money" << std::endl;
            std::cout << "Enter account number: ";
            std::cin >> num;
            b.deposit_money();
            break;
        case 3:
            std::cout << "\n3.) Withdraw Money" << std::endl;
            std::cout << "Enter account number: ";
            std::cin >> num;
            b.withdraw_money();
            break;
        case 4:
            std::cout << "\n4.) Display Account" << std::endl;
            std::cout << "Enter account number: ";
            std::cin >> num;
            b.display_sp(num);
            break;
        case 5:
            std::cout << "\n5.) Close Account" << std::endl;
            std::cout << "Enter account number: ";
            std::cin >> num;
            b.delete_account(num);
            break;
        case 6:
            std::cout << "\n6.) Modify Existing Account" << std::endl;
            std::cout << "Enter account number: ";
            std::cin >> num;
            b.modify_acc(num);
            break;
        case 7:
            std::cout << "\n7.) Display All Accounts" << std::endl;
            b.display_all();
            break;
        case 8:
            std::cout << "\nThank you for using our services. Exiting..." << std::endl;
            exit(0);
        default:
            std::cout << "\nPlease Try again and choose the correct option!" << std::endl;
            break;
        }

        std::cout << "\nDo you want to continue banking without exit? Press (Y/N): ";
        std::cin >> option;

    } while (option == 'y' || option == 'Y');

    return 0;
}

