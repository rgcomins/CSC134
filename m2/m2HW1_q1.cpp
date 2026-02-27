/*
CSC - 134
comins
2/12/2026
The /atm program will generate an account having both a name and number. It will show all 
transactions including both deposits and withdrawls. Finally the program will calculate the final ballance
of the account. It will then display the following:
    
    the name on the account
    the account number
    the final account balance.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main(){

//define variables
string first_name;
string last_name;
string account_name = first_name + last_name;
//string latest_account_balance = ;
int account_number = 123456789;// nine digits
double starting_account_balance;
double deposit_amount;
double withdrawl_amount;
double account_balance;
//double 
// do the math
cout << account_name << endl;
cout << account_number << endl;
cout << "Enter your first name." << endl;
cin >> first_name; 
cout <<"Enter your last name." << endl;
cin >> last_name;
cout <<"What is your account_balance?"  << endl;
cin >> starting_account_balance;
cout << "How much was your deposit? " << endl;
cin >> deposit_amount;
cout << "Your new account balance equals the account balance plus your deposit.  ";
account_balance = starting_account_balance + deposit_amount;
cout <<"$"<< account_balance << endl;
cout <<"What is the amount of your withdrawl?" << endl;
cout << "Your account balance now equals the account balance - the withdrawl_amount."<< endl;
cin >> withdrawl_amount;
account_balance = account_balance - withdrawl_amount;
cout <<"$"<< account_balance << endl;


return 0;


}