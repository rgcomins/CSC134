#include <iostream>
#include "M5T2.H"
using namespace std;

int main()

{
    // print out a table of squares
    cout << "Num\tsquare" <<endl;
    int start = 1;
    int finish = 10;
    for (int num = start; num <= finish; num++) {
        int sq = square(num);
        print_table_line(num,sq);
    }
}
