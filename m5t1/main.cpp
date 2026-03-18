#include <iostream>

using namespace std;
//M5T1, Simple Function
//cominsr
//3/18/26

// Declare our Functions
void say_hello();                   //no arguments, no return
int get_answer();                   //no args, returns int
int double_a_number(int number);     //int arg, returns int

int main()
{
    say_hello();
    cout << "The answer is: " <<get_answer() << endl;
    cout <<"Type in an integer: ";
    int num;
    cin >> num;
    int answer = double_a_number(num);
    cout << "Double the number is: " << answer << endl;
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

