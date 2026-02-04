//csc134
//m1Lab1
//rgcomins
//01/21/2026

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    //declare my variables
    string item_name = "apples";            //whatever you want
    int item_count = 100;                   //how many we have
    double item_cost = 0.80;                //price per item
    double total_cost;                      //don't know yet

   //magic words to set 2 decimal places - requires <iomanip>
   cout << setprecision(2) << fixed;
   
   //Do the work - Welcome them to the store.
   cout << "Welcomme to the " <<item_name << "store." << endl;
   cout << "We have " << item_count << " " << item_name << "." << endl;
   cout << "They cost $" <<item_cost << "each." << endl;

   //Calculate the total price
   total_cost = item_count * item_cost;
   //print the total
   cout << "To buy all of them will cost $" << total_cost << endl;
      
    return 0;
     


} 

