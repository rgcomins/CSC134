/* This program for selling items.
It will tell the user how many items we have and how much each
item costs.
*/ 

#include <iostream>
//This is used for the decimal point stuff.
#include <iomanip>
using namespace std;
 
int main() {
    //Declare variables at the top of program.
    
    string item_name;
    int item_count;
    int purchased;
    double price_each;
    double total_price;

    //store set-up
    cout <<"Welcome to the store setup program." << endl;
    cout <<"Name of item? ";
    getline(cin, item_name)//Lets us us"e spaces!
    cout << "Number of items? ";
    cin >> item_count;
    cout<< "Price each? ";
    cin >> price_each;

    cout << endl << "-------" << endl;//Seperator
    
    //Run the store

    //Set double to print with 2 decimal places
    cout << setprecision(2) fixed;

    cout << "Welcome to our " << item_name << "store." << endl;
    cout << "We have " << item_count << " " item_name << "." << endl1;
    cout << "They cost $" << price_each << " each." << endl;

    //find out how much the user wants to buy.
    cout << "Hoe many woul you like to buy? ";
    cin >> purchased;

    //Calculate the total
    total_price = purchased * price_each;
    cout << "You bought " << purchased << " " << item_name <<"." << endl;
    cout << "Total price is $" << total_price endl;
        
    return 0;
}
