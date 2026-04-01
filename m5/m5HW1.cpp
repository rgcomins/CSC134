// CSC 134
// M5HW1 - Sample Setup
// cominsr
// 4/1/26
// Not answering the questions, just setting up the structure.
#include <iostream>
using namespace std;

// List all question prototypes here
void question1();
void question2();
// rest go here


// main() here
int main() {

    // Question 6: Print a menu so they can choose a question
    // Until I do question 6, they will all run one at a time

    question1();
    question2();
    // and so on
    return 0;
}

// All full questions (function definitions) go here
void question1() {
    string month1,month2,month3;
    double rainfall_month1,rainfall_month2,rainfall_month3;
    double total_rainfall,average_rainfall;
    
    cout << "Question 1" << endl;
    cout <<  "Enter the name of month1: ";
    cin >> month1;
    cout << "Enter rainfaill for month1: ";
    cin >> rainfall_month1;

    cout <<  "Enter the name of month2: ";
    cin >> month2;
    cout << "Enter rainfaill for month2: ";
    cin >> rainfall_month2;

    cout <<  "Enter the name of month3: ";
    cin >> month3;
    cout << "Enter rainfaill for month3: ";
    cin >> rainfall_month3;

    total_rainfall = rainfall_month1 + rainfall_month2 + rainfall_month3;
    average_rainfall = total_rainfall / 3;
    cout << "The total rainfall was " << total_rainfall << endl;
    cout << "the average rainfall was " << average_rainfall << endl;

}

void question2() {
    cout << "Question 2" << endl;
}