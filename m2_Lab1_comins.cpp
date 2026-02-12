/*
SC 134
M2Lab1 - The Crate Program
comins
1/28/26

Find volume of crateC
Find cost, customer_price, and profit
Print everything out
*/

#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    // Part 1 -- Declare Variables
    // constant variables (don't change unless the market changes)
    const double COST_PER_CUBIC_FOOT = 0.23;
    const double CHARGE_PER_CUBIC_FOOT = 0.5;

    // Crate variables 
    double length, width, height, volume; // all in feet
    // Money variables
    double cost, customer_price, profit;  // all in $

    // Part 2 -- Get the Input
    cout << "Welcome to the crate program." <<endl;
    cout << "Enter the create dimensions,"<<endl;
    cout << "Crate Length ";
    cin >> length;
    cout << "Crate Width ";
    cin >> width;
    cout << "Crate height ";
    cin >> height;

    // Part 3 -- Do the Calculations
    volume = (length * width * height); 
    // Find the cost and the customer_price 
    cost = volume * COST_PER_CUBIC_FOOT;
    customer_price = volume * CHARGE_PER_CUBIC_FOOT;
    profit = customer_price - cost;
    // Part 4 -- Print the Output
    cout << setprecision(2) << fixed; // 2 decimal places
    cout << "==== CRATE INFO ====" << endl;
    cout << "Volume is " << volume << "cubic feet." <<endl;
    cout << "wholesale price is $" << cost <<endl;
    cout << "Customer price is $" << customer_price << endl;
    cout << "Profit per crate: $" << profit << endl;

    return 0; 
}    
