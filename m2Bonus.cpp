/*
SC 134
M2Bonus - Def and use functions
comins
02/20/26

1. Given a rectangle with height 8 and width 10, calculate and print the area. 
(This one is most similar to "Apple Orchard", except these are both of type int.
 The formula "Area equals length times width" will be useful.)

*/

#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    //Question 1
    //Declare my variables
    int length;
    int width;
    int area;

    //Get the length from the user
    cout << "What is the length of the rectangle? ";
    cin >> length;
    //Get the width from the user?
    cout << "What is the width of the rectangle? ";
    cin >> width;
    // Do the calculations
    area = (length * width);
    cout << "The area of the rectangle is. ";
    cout << area << "\n\n";

    //Question 2
    //Declare my variables
    double product_price = 99.99;
    double sales_tax = 0.08;
    double tax_amount = (product_price * sales_tax);
    double total = (product_price + tax_amount);
    cout << setprecision(2) << fixed;
    //Print the results
    cout << "\nThe product price is.$ ";
    cout << product_price;
    cout << "\nThe ammount of sales tax is.$ ";
    cout << tax_amount;
    cout << "\nThe final cost is.$ ";
    cout << total << "\n\n";
    //Question 3
    //Define my variable.
    const double PI = 3.14;
    double diameter = 12;
    double radius = diameter /2;
    double area_pizza =  PI * radius *radius;
    //Print  area of the pizza
    cout << "The area of the pizza is " << area_pizza << endl;
    cout << "\n\n";
    //Question 4      
    cout << "If we cut the pizza into 8 slices, The area of each slice will be ";
    cout << area_pizza / 8;



}