/*This program creates a simple booking program that sumerizes travel expenses.
it also creates a receipt program that determines if a tip is applies to the final bill 
or if in the case of take out orders how much  tip is required. Finally, it generates a 
random numbers and performs calculations on these numbers.
*/ 

// CSC-134
// Assignment M3HW1
// Comins Richard
// 03/06/2026
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// one function per question
void question1();
void question2();
void question3();
void question4();

int main() {
    question1(); // yes or no
    question2(); // receipt with tip
    question3(); // see m3lab1
    // add more
    question4();



}

// questions go here
void question1() {
    // cout << "Hello, I'm a c++ program! " << endl;
    //cout << "Do you want to travel to Honolulu, Hi " << endl;
    // cout << "Type,  yes or no " << endl;
    bool ask_to_travel();

        
    while (true) {
        cout << "Do you want to travel to Ohahu, HI? (yes/no)\n";  // from document
        string response;
        getline(cin, response);

        //response = tolower(response);
        // manual tolower()
        /*std::string s = response;
        for (auto& x : s) {
        x = tolower(x);
        }
        response = s;
        */
        if (response == "yes") {
            cout << "Ok, Aloha!" << endl;
            return; // true;  // continue program
        }
        else if (response == "no") {
            cout << "Thank you. Have a great day!\n";
            return; // false;  // exit program
        }
        else {
            cout << "Please enter 'yes' or 'no'.\n";
        }
}
    cout << "Q1" << endl;

}

void question2() {
    // receipt
    //Define variables
    string meal_name;
    string line = "--------------------------";
    const double TIP_RATE = 0.15;
    const double TAX_RATE = 0.08;
    double tip_amount; 
    bool dine_in; 
    //bool take_out;
    double meal_price, num_meals, sub_total, total,tax_amount;
    //get info from user
    cout << "What would you likle to order? " << endl;
    cin >> meal_name;
    getline(cin, meal_name); // lets you use spaces
    cout << "Is this order dine_in? ";
    string yesorno;
     
    //Set variable amounts
    meal_price = 5.99;
    num_meals = 1;
    sub_total = meal_price * num_meals;
    tax_amount = sub_total * TAX_RATE;
    
    //Do calculations
    // Handle the tip
    cin >> yesorno;
    if (yesorno == "yes") {
        tip_amount = sub_total * TIP_RATE;
    }
    else {
        tip_amount = 0.0;
    }

    total = sub_total + tax_amount + tip_amount;

    cout << setprecision(2) << fixed; // 2 decimal places
    cout << "You ordered " << meal_name << endl;
    //cout << sub_total << endl;
    cout << "Sub Total $ "<< sub_total << endl;
    cout << "TAX       $ " << tax_amount << endl;
    cout << "tip_amount $ " << tip_amount << endl;
    cout << line << endl;
    cout << "Total     $ " << total << endl;

    cout << line << endl;
}

void question3() {
    cout << "Q3: See M3Lab1" << endl;
}
void question4() {
    //seed the random number generator
    int seed = time(0);
    srand(seed);
    // Roll two dice and show the results
    int first, second, total;
    first = (rand() % 10) + 1;;
    second = (rand() % 10) + 1;
    total = first + second;

    cout << first << " + " << second << " = " << "?" << endl;
    

}


