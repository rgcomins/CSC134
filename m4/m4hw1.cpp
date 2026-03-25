/*CSC - 134
M4HW1.cpp
3/4/2026
Comins
Assignment: Ask user for a number (1-12)
then display the times table, as a table.
*/

#include <iostream>
using namespace std;

int main() {
   
    
    cout << "The Multiplication Table" << endl;
    const int MIN = 1;
    const int MAX = 12;
    int input = 5;
    int num = MIN;
    int multiplied;
    cout << "Number\tNumber multiplied\n";
    cout << "____________________________" << endl;
    while (num <= MAX) {
        multiplied = num * input;
        cout << num << "\t" << multiplied << endl;
        num++; //go to next number
    }
}