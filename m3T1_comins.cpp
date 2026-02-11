/* This program calculates the area of a rectangle ant 
the outpute the largest  rectangle.
*/ 

#include <iostream>
//This is used for the decimal point stuff.
#include <iomanip>
using namespace std;
 
int main() {





// a user, I want to measure rectangles to find out how big they are.

// Set up varjables
double length1, width1, area1;
double length2, width2,area2;
// ask user for info
cout << "What is the rectangle1's length? ";
cin >> length1;
cout << "What is the rectangle1's width?";
cin >> width1;

cout << "What is the rectangle2's length? ";
cin >> length2;
cout << "What is the rectangle2's width? ";
cin >> width2;

// do the calulation
area1 = length1 * width1;
area2 = length2 * width2;

// Print the answer
cout << "Rectangle #1: " << length1 << " by " << width1 << " is area " << area1 << endl;
cout << "Rectangle #2; " << length2 << " by " << width2 << " is area " << area2 << endl;

// Which one is larger?
if (area1 > area2) {
    cout << "The first rectangle is the largest. " << endl;
}
if (area2 > area1) {
    cout << "The second rectangle is the largest. " << endl;
}
if (area1 == area2) {
    cout << "The area of both rectangles are equal." << endl;
}


return 0;


}