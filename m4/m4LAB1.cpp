/*CSC - 134
m4LAB1.cpp
3/26/2026
Comins
Assignment:
*/

#include <iostream>
using namespace std;

int main() {

    // Define variables
    int width = 5;
    int height = 5;

    // Input

    // Process

    // Output: loop through each row
    for (int i=0; i < height; i++) {
        // For each row, print one * per column
        for (int j=0; j < width; j++) {
            cout << "*" << " ";
        }
        cout << endl; // move to the next row
    }

    return 0;
}
