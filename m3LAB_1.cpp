#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

// Helper: convert string to lowercase
string toLower(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

int main() {

    // -------------------------------
    // WHILE LOOP: Ask if user wants to travel
    // -------------------------------
    while (true) {
        cout << "Do you want to travel to Ohahu, HI? (yes/no)\n";  // from document
        string response;
        getline(cin, response);

        response = toLower(response);

        if (response == "yes") {
            break;  // continue program
        }
        else if (response == "no") {
            cout << "Thank you. Have a great day!\n";
            return 0;  // exit program
        }
        else {
            cout << "Please enter 'yes' or 'no'.\n";
        }
    }

    // -------------------------------
    // DO-WHILE SIMULATION: Travel dates
    // -------------------------------
    string dates;
    while (true) {
        cout << "Enter your travel dates (MM/DD/YYYY - MM/DD/YYYY):\n";  // from document
        getline(cin, dates);

        if (dates.find('-') != string::npos) {
            break;
        } else {
            cout << "Invalid format. Please try again.\n";
        }
    }

    // -------------------------------
    // FOR LOOP: Collect origin, destination, travel class
    // -------------------------------
    string fields[3] = {
        "origin city",
        "destination city",
        "travel class (economy/first)"
    };

    string user_inputs[3];

    for (int i = 0; i < 3; i++) {
        while (true) {
            cout << "Please enter your " << fields[i] << ":\n";
            string entry;
            getline(cin, entry);

            string lower = toLower(entry);

            if (fields[i] == "travel class (economy/first)" &&
                !(lower == "economy" || lower == "first")) {
                cout << "Please choose 'economy' or 'first'.\n";
            }
            else if (entry.empty()) {
                cout << "Input cannot be empty.\n";
            }
            else {
                user_inputs[i] = entry;
                break;
            }
        }
    }

    string origin = user_inputs[0];
    string destination = user_inputs[1];
    string travel_class = toLower(user_inputs[2]);

    // -------------------------------
    // Calculate flight cost
    // -------------------------------
    int flight_cost = (travel_class == "economy") ? 600 : 1200;

    cout << "Flight cost from " << origin
         << " to " << destination
         << " in " << user_inputs[2]
         << " class: $" << flight_cost << "\n";

    // -------------------------------
    // Hotel room types
    // -------------------------------
    const string room_names[3] = {
        "Deluxe Ocean-View",
        "Ocean-View",
        "Garden-View"
    };

    const int room_prices[3] = {350, 250, 150};

    cout << "Available hotel room types:\n";
    for (int i = 0; i < 3; i++) {
        cout << (i + 1) << ". " << room_names[i]
             << " - $" << room_prices[i] << " per night\n";
    }

    // -------------------------------
    // Room selection
    // -------------------------------
    int room_choice = 0;
    while (true) {
        cout << "Select a room type by number (1-3):\n";
        string input;
        getline(cin, input);

        if (input == "1" || input == "2" || input == "3") {
            room_choice = stoi(input) - 1;
            break;
        } else {
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    string room_name = room_names[room_choice];
    int room_price = room_prices[room_choice];

    // -------------------------------
    // DO-WHILE SIMULATION: Number of nights
    // -------------------------------
    int nights = 0;
    while (true) {
        cout << "How many nights will you stay?\n";
        string input;
        getline(cin, input);

        try {
            nights = stoi(input);
            if (nights > 0) break;
            cout << "Please enter a positive number.\n";
        }
        catch (...) {
            cout << "Invalid input. Please enter a number.\n";
        }
    }

    // -------------------------------
    // Final cost summary
    // -------------------------------
    int hotel_total = nights * room_price;
    int total_cost = hotel_total + flight_cost;

    cout << "\n--- Booking Summary ---\n";
    cout << "Destination: Ohahu, HI\n";
    cout << "Travel Dates: " << dates << "\n";
    cout << "Flight: $" << flight_cost << "\n";
    cout << "Hotel: " << room_name << " for " << nights
         << " nights = $" << hotel_total << "\n";
    cout << "Total Trip Cost: $" << total_cost << "\n";

    return 0;
}
