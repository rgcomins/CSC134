/*
SC 134
m2HW_q3 - The Pizza Program
comins
2/13/26

Find number of pizzas needed for the amount of guests invited if each guest gets 3 slices
of pizza.  The program should calculate and display how many piees of pizza are left over.

*/

#include <iostream>
#include <iomanip>
using namespace std;
int main() {

    // Define variables
    int num_guests;
    int num_slices_needed;
    int num_pizzas;    
    int num_slices_per_pizza;
    int num_slices_remaining;
    int total_slices;
    cout << "How many guests are you inviting?" << endl;
    cin >> num_guests;
    num_slices_needed = num_guests * 3;
    cout << "How many slice is each pizza cut into?" << endl;
    cin >> num_slices_per_pizza;
    cout << "The number of pizzas ordered? " << endl;
    cin >> num_pizzas;
    // do the math
    total_slices = num_pizzas * num_slices_per_pizza;
    num_slices_remaining = total_slices - num_slices_needed;
    cout << num_slices_remaining << " slices left over" << endl;



}