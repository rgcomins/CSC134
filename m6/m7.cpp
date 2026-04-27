/*



*/

#include<iostream>
using namespace std;    

class Restaurant {
    private:
        string name;
        string location;
        int rating;
    public:
        void displayInfo() {
            cout << "Restaurant Name: " << name << endl;
            cout << "Location: " << location << endl;
            cout << "Rating: " << rating << "/5" << endl;
        }
    
  
	// constructor 
	Restaurant(string n, double r) {
		name = n;
		rating = r;
	}
	// getters and setters
    void setName(string n) {
        name = n; 
    }
    void setRating(double r) {
        rating = r;
    }
    string getName() const {
        return name;
    }
    double getRating() const {
        return rating;
    }
};

int main() {

    cout << "Restaurant Reviews" << endl;

    // Create one restaurant
    Restaurant rest1 = Restaurant("Mi Casita", 4.0);
    cout << rest1.getName() << endl;
    cout << rest1.getRating() << endl;

    // Make another uing user input
    Restaurant rest2 = Restaurant("", 00);

    string n;
    double r;
    cout << "Enter Restaurant Name: ";
    cin >> n;
    cout << "Rating (1.0 - 5.0): ",
    cin >> r;

    rest2.setName(n);
    rest2.setRating(r);
    cout << rest2.getName() << endl;
    cout << rest2.getRating() <<endl;
    rest2.displayInfo();




}
