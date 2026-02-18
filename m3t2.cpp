/*This program starts the game of Craps.
CSC 134
M3T2
2/16/2026
Cominsr6423
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

//This is used for the decimal point stuff.
#include <iomanip>
#include <ctime>
using namespace std;
// function declarations
// (Tell the program what functions will be!)

int roll();

// main() goes here
int main() {
    //seed the random number generator
    int seed = time(0);
    srand(seed);
    // Roll two dice and show the results
int first, second, total;
    first = roll();
    second = roll();
    total = first + second;
    cout << "You rolled 🎲 " << first << " + " << second << " = " << total << endl;
    
    //How did we do?
    string result;  //did we win or lose?

    if (total == 7 || total == 11) {
        result = "win";
    }
    else if (total == 2 || total == 3 || total == 12) {
        result = "lose";
    }
    else {
         result = "point";
    }
       

    cout << "Roll results " <<result <<endl;
    return 0;

}

// Function definitions
// (Actually write the entire function!)
int roll() {
    //rand() gives a large random number
    // % 6 divides by six, and keeps the remainder
    // finally, add 1 so it's 1 to 6, not zero to five
    int my_roll = (rand() % 6) + 1;
    return my_roll;
}





