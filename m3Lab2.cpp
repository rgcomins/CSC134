#include <iostream>
#include <iomanip>
using namespace std;

//main() goes here

int main() {
    double num_grade;
    string letter_grade;
    cout << "This program takes a number grade (0-100) and provides the letter grade (A-F)" << endl;
    //input
    cout <<"Enter number grade: ";
    cin >> num_grade;
    //calculate
   
     if (num_grade >= 90) {
        letter_grade = "A";
    } 
    else  if (num_grade >= 80) {
        letter_grade = "B";
    } 
    else if (num_grade >= 70) {
        letter_grade = "C";
    } 
    else if (num_grade >= 60) {
        letter_grade = "D";
    
    } 
    else {
        letter_grade = " F";
    }
     
       



    //output
    cout << "A grade of " << num_grade << " is letter grade " << letter_grade << endl;







}