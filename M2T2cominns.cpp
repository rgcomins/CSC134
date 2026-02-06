/* This program generates a receipt for a meal.
It will include the price of the meal, before tax, the tax, a sub-total, and a total_price. */
//CSC 134
// M2T2 (Module 2)
// Receipt

// magic words
#include <iostream>
#include <iomanip>
using namespace std;


int main() {
//Define variables
string meal_name;

const double TAX_RATE = 0.08;
double meal_price, num_meals, sub_total, total,tax_amount;
//get info from user
cout << "What would you likle to order? " << endl;
//cin >> meal_name;
getline(cin, meal_name); // lets you use spaces
//Set variable amounts
meal_price = 5.99;
num_meals = 1;
sub_total = meal_price * num_meals;
tax_amount = sub_total * TAX_RATE;
total = sub_total + tax_amount;
//Do calculations
cout << setprecision(2) << fixed; // 2 decimal places
cout << "You ordered " << meal_name << endl;
//cout << sub_total << endl;
cout << "Sub Total $ "<< sub_total << endl;
cout << "TAX       $ " << tax_amount << endl;
cout << "Total     $ " << total << endl;
 

}