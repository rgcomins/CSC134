/*CSC - 134
M4HW1.cpp
3/4/2026
Comins & Claude
Assignment: Ask user for a number (1-12)
then display the times table, as a table.
*/

#include <iostream>
using namespace std;

int main() {

    // Constants for the valid input range
    const int MIN = 1;
    const int MAX = 12;

    // Variables
    int input;      // number entered by the user
    int num;        // current row in the table
    int multiplied; // result of num * input

    // Prompt user for a number within the valid range
    cout << "The Multiplication Table" << endl;
    cout << "Enter a number (1-12): ";
    cin >> input;

    // Validate that input is within the accepted range
    if (input < MIN || input > MAX) {
        cout << "Invalid input. Please enter a number between 1 and 12." << endl;
        return 1; // exit with error code
    }

    // Print table header
    cout << "\nNumber\tResult" << endl;
    cout << "____________________________" << endl;

    // Loop from MIN to MAX, printing each multiplication result
    num = MIN;
    while (num <= MAX) {
        multiplied = num * input;
        cout << num << "\t" << multiplied << endl;
        num++; // advance to the next row
    }

    return 0;
}
