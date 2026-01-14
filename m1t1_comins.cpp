//CSC 134
// M1T1 (Module 1, Tutorial 1)
// Hello, World!

// magic words
#include <iostream>
using namespace std;

int main() {
    cout << "Hello CSC 134"<< endl; // ENDL
    cout<< endl; //another new line
    cout << "Hello World!"<< endl; // ENDL
    cout<< endl; //another new line<<
    
    string name;//new box to hold a name in
    cout<< "What is your name? ";
    cin >> name; //read in their answer
    // finally, say hi to them
    cout << "Well hi, " <<name<<"!" << endl;
    
    return 0;

}