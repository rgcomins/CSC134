/*Purpose:  Calculate and display the area of a rectangle
m5LAB2.cpp
3/30/2026
Comins
*/
// M5LAB2
// Finishing someone's work -- Area of a rectangle
// norrisa
// 3/30/26

#include <iostream>
using namespace std;

// Declare (Write the prototypes for)
// the getLength,
// getWidth, getArea, and displayData
// functions here.
double getLength();
double getWidth();
double getArea(double length, double width);
void   displayData(double length, double width, double area);

int main()
{
	// This program calculates the area of a rectangle.
	// TODO: fix any syntax errors
	
   double length,    // The rectangle's length
          width,     // The rectangle's width
          area;      // The rectangle's area
          
   // Get the rectangle's length.
   length = getLength();
   
   // Get the rectangle's width.
   width = getWidth();
   
   // Get the rectangle's area.
   area = getArea(length, width);
   
   // Display the rectangle's data.
   displayData(length, width, area);
          
   return 0;
}

//***************************************************
// TODO: write the getLength, getWidth, getArea,    *
// and displayData functions below.                 *
//***************************************************

double getLength() {
    // getLength - Asks the user to enter a rectangle's length, and return that value as a double.
    double length;
    cout << "Enter the rectangle's length: ";
    cin >> length;
    return length;
}
double getWidth() {
    double width; 
    cout << "Enter the rectangle's width: ";
    cin >> width;
    return width;   
} 
double getArea(double length, double width) {
    double area = length * width;
    return area;
}

void displayData(double length, double width, double area) {
    cout << "Length: " << length << endl;
    cout << "Width: " << width << endl;
    cout << "Area: " << area << endl;
    cout << endl;
}
