/* CSC 134
m1Hw1
Cominsr 6423
02/05/2026

The purpose of this program is to declare variables, store these variables in memory, 
and finally out information to the screen.
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    //declare my variables
    string movie_name = "Casablanca";           //whatever you want
    int year_released = 1942;                   //year released
    double gross_amt = 6.9;                   //amount of money made
    string quote = "Play it again Sam";         //movie quote

    //Print the output.
    cout << "One of my favorite movies of all time is " << movie_name << endl;
    cout << "It was released to the public in " << year_released << endl;
    cout << "Although not as popular as I expected, it grossed  $" << gross_amt << " Million" <<endl;

    cout << "One of the most memorable lines in the movie was " << quote << endl;

    return 0;


}