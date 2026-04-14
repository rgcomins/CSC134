/*
M6T1 - Basic Arrays
cominsr
4/13/26
*/

#include <iostream>
using namespace std;

int main() {
    cout << "This is part 1 and it does not use an array. " << endl;

    // declare variables
    const int SIZE = 5; // changing this is the only way to resize the array
    int total_cars =0;
    int cars_seen_today;    
    double average_1;
    cout << "This program will ask you to enter a count of cars seen." << endl;
    for (int n=0; n<SIZE; n++) {
        cout << "Day " << n+1 << ": ";
        cin >> cars_seen_today;
        total_cars = total_cars + cars_seen_today;

    }
    
    // Do the calculations
    average_1 = total_cars /SIZE;
    cout << "Over " << SIZE << " days," << endl;
    cout << "Total cars: " << total_cars << endl;
    cout << "Average:    " << average_1 << endl;
    
    cout<< "___________________________________" << endl;
    
    
    cout << "This is part 2 and it uses an array. " << endl;

    // Set up variables
    //const int SIZE = 5; // changing this is the only way to resize the array
    int cars[SIZE];     // contains 5 (SIZE) integers
    double sum = 0;
    double average;
    cout << "This program will ask you to enter a count of cars seen." << endl;
    // first loop: get data
    for (int i=0; i<SIZE; i++) {
        cout << "Day " << i+1 << ": ";
        cin >> cars[i];
    }
    // second loop: sum and average
    for (int i=0; i<SIZE; i++) {
        sum += cars[i]; // add that day's cars
    }
    average = sum / SIZE;
    cout << "Over " << SIZE << " days," << endl;
    cout << "Total cars: " << sum << endl;
    cout << "Average:    " << average << endl;
}