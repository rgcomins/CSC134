// CSC 134
// M5HW1 - Sample Setup
// cominsr
// 4/1/26
#include <iostream>
using namespace std;

// List all question prototypes here
void question1();
void question2();
void question3();


// main() here
int main() {

    // Question 6: Print a menu so they can choose a question
    // Until I do question 6, they will all run one at a time

    question1();
    question2();
    question3();    // and so on
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
    cout << "Question 2" << endl;//Find the volume of a box
    cout << " Get the dimensions of a Box " << endl;
    double length,width,height,volume;

    cout << "Enter the length: ";
    cin >> length;
    cout << "Enter the width: ";
    cin >> width;
    cout << "Enter the height ";
    cin >> height;

    //Do the calculations
    volume = length * width * height;
    cout << "The volume of the box is: " << volume << endl ;
}
void question3() {
    //Define the variables
    int num;
    string Roman_Numeral;

    cout << "Enter a number from 1 to 10: ";
    cin >> num;
    if(num == 1) {
        Roman_Numeral = "I";
    }
    else if(num == 2){
        Roman_Numeral = "II";
    }
    else if(num == 3){
        Roman_Numeral = "III";
    }
    else if(num == 4){
        Roman_Numeral = "IV";
    }
    else if(num == 5){
        Roman_Numeral = "V";
    }
    else if(num == 6){
        Roman_Numeral = "VI";
    }
    else if(num == 7){
        Roman_Numeral = "VII";
    }
    else if(num == 8){
        Roman_Numeral = "VIII";
    }
    else if(num == 9){
        Roman_Numeral = "IX";
    }   
    else if(num == 10) {
        Roman_Numeral = "X";
    }
    cout << "The Roman Numeral is " << Roman_Numeral;
}