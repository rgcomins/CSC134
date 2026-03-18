#include <iostream>

using namespace std;
//M5T1, Simple Function
//cominsr
//3/18/26

// Declare our Functions
void say_hello();                   //no arguments, no return
int get_answer();                   //no args, returns int
int double_a_number(int number);     //int arg, returns int
double area_of_rectangle(double length, double width);
double area_of_square(double side);

int main()
{
    say_hello();
    cout << "The answer is: " <<get_answer() << endl;
    cout <<"Type in an integer: ";
    int num;
    cin >> num;
    int answer = double_a_number(num);
    cout << "Double the number is: " << answer << endl;

    // AREA EXAMPLES
    double length = 4;
    double width = 6;
    double side = 5;

    double area_rect = area_of_rectangle(length, width);
    double area_sq   = area_of_square(side);
    cout << "Rect area  = " << area_rect << endl;
    cout << "Square area= " << area_sq << endl;


    return 0;

    //cout << "Hello world!" << endl;
    //return 0;
}
//Define our function (full code goes here)

void say_hello() {
    cout << "Hello world!" <<endl;

}
int get_answer() {
    return 42;
    }

int double_a_number(int number) {
    int answer = number *2;;
    return answer;
}

double area_of_rectangle(double length, double width) {
    // area is length times width
    double area = length * width;
    return area;

}
double area_of_square(double side) {
    double area = side * side;
    return area;
}

