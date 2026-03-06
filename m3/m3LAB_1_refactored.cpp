// ============================================================================
// m3LAB_1 - Oahu Travel Booking System (Refactored Version)
// ============================================================================
// This is the same program you built, reorganized into functions.
// Nothing about what the program DOES has changed — only HOW it's organized.
//
// KEY CONCEPTS DEMONSTRATED:
//   1. Function prototypes    — declaring functions before main()
//   2. Void functions         — displaySummary() doesn't return anything
//   3. Value-returning funcs  — askToTravel(), getTravelDates(), etc.
//   4. Pass by reference      — getFlightInfo() modifies 3 variables at once
//   5. Parameters             — displaySummary() receives everything it needs
//   6. Scope                  — each function has its own local variables
//
// Notice how main() now reads like a story:
//   "Ask if they want to travel, get dates, get flight info, pick a room..."
// ============================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

// ----------------------------------------------------------------------------
// Helper function (unchanged from your original!)
// ----------------------------------------------------------------------------
string toLower(const string& s)
{
    string out = s;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

// ============================================================================
// FUNCTION PROTOTYPES
// These go above main() so the compiler knows these functions exist.
// Think of them like a table of contents for your program.
// ============================================================================
bool   askToTravel();
string getTravelDates();
void   getFlightInfo(string &origin, string &dest, string &travelClass);
int    selectRoom();
int    getNights();
void   displaySummary(const string &dates, const string &origin,
                      const string &dest, const string &travelClass,
                      int flightCost, int roomChoice, int nights);

// ============================================================================
// MAIN — now short and readable, like an outline of the program
// ============================================================================
int main()
{
    // Step 1: Ask if user wants to travel (returns true/false)
    if (!askToTravel())
    {
        return 0;  // User said no — exit cleanly
    }

    // Step 2: Collect all the booking details
    string dates = getTravelDates();

    string origin, destination, travelClass;
    getFlightInfo(origin, destination, travelClass);
    //            ^^^^^^  ^^^^^^^^^^^  ^^^^^^^^^^^
    //            These three variables are passed BY REFERENCE.
    //            getFlightInfo() fills them in for us.
    //            Without the &, the values would stay empty here!

    int flightCost = (travelClass == "economy") ? 600 : 1200;

    int roomChoice = selectRoom();
    int nights     = getNights();

    // Step 3: Show the final booking summary
    displaySummary(dates, origin, destination, travelClass,
                   flightCost, roomChoice, nights);

    return 0;
}

// ============================================================================
// FUNCTION DEFINITIONS
// Each function does ONE job. This makes them easier to test and debug.
// ============================================================================

// ----------------------------------------------------------------------------
// askToTravel — VALUE-RETURNING FUNCTION (returns bool)
// Asks the user if they want to travel. Loops until valid input.
// Returns: true if yes, false if no
// ----------------------------------------------------------------------------
bool askToTravel()
{
    while (true)
    {
        cout << "Do you want to travel to Oahu, HI? (yes/no)" << endl;
        string response;
        getline(cin, response);
        response = toLower(response);

        if (response == "yes")
        {
            return true;   // Send back true to main()
        }
        else if (response == "no")
        {
            cout << "Thank you. Have a great day!" << endl;
            return false;  // Send back false to main()
        }
        else
        {
            cout << "Please enter 'yes' or 'no'." << endl;
        }
    }
}

// ----------------------------------------------------------------------------
// getTravelDates — VALUE-RETURNING FUNCTION (returns string)
// Collects a date range from the user with basic format validation.
// Returns: the date string (e.g., "03/15/2025 - 03/22/2025")
// ----------------------------------------------------------------------------
string getTravelDates()
{
    string dates;

    while (true)
    {
        cout << "Enter your travel dates (MM/DD/YYYY - MM/DD/YYYY):" << endl;
        getline(cin, dates);

        if (dates.find('-') != string::npos)
        {
            return dates;  // Valid enough — contains a dash
        }
        else
        {
            cout << "Invalid format. Please try again." << endl;
        }
    }
}

// ----------------------------------------------------------------------------
// getFlightInfo — VOID FUNCTION WITH REFERENCE PARAMETERS
//
// This is the most important function to understand in this program.
// It needs to send back THREE values (origin, dest, class), but a
// function can only return ONE thing. Solution: pass by reference (&).
//
// The & means "don't make a copy — use the ORIGINAL variable from main()."
// So when we assign to origin inside this function, it changes the
// origin variable back in main().
// ----------------------------------------------------------------------------
void getFlightInfo(string &origin, string &dest, string &travelClass)
{
    string fields[3] = {
        "origin city",
        "destination city",
        "travel class (economy/first)"
    };

    string userInputs[3];

    for (int i = 0; i < 3; i++)
    {
        while (true)
        {
            cout << "Please enter your " << fields[i] << ":" << endl;
            string entry;
            getline(cin, entry);

            string lower = toLower(entry);

            if (fields[i] == "travel class (economy/first)" &&
                !(lower == "economy" || lower == "first"))
            {
                cout << "Please choose 'economy' or 'first'." << endl;
            }
            else if (entry.empty())
            {
                cout << "Input cannot be empty." << endl;
            }
            else
            {
                userInputs[i] = entry;
                break;
            }
        }
    }

    // These assignments modify the variables back in main()
    // because of the & in the parameter list above.
    origin      = userInputs[0];
    dest        = userInputs[1];
    travelClass = toLower(userInputs[2]);
}

// ----------------------------------------------------------------------------
// selectRoom — VALUE-RETURNING FUNCTION (returns int)
// Displays hotel options and gets a validated choice.
// Returns: the array index (0, 1, or 2) of the chosen room
// ----------------------------------------------------------------------------
int selectRoom()
{
    const string roomNames[3] = {
        "Deluxe Ocean-View",
        "Ocean-View",
        "Garden-View"
    };

    const int roomPrices[3] = {350, 250, 150};

    cout << "Available hotel room types:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << (i + 1) << ". " << roomNames[i]
             << " - $" << roomPrices[i] << " per night" << endl;
    }

    while (true)
    {
        cout << "Select a room type by number (1-3):" << endl;
        string input;
        getline(cin, input);

        if (input == "1" || input == "2" || input == "3")
        {
            return stoi(input) - 1;  // Convert to 0-based index
        }
        else
        {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    }
}

// ----------------------------------------------------------------------------
// getNights — VALUE-RETURNING FUNCTION (returns int)
// Asks for the number of nights with validation.
// Returns: a positive integer
// ----------------------------------------------------------------------------
int getNights()
{
    while (true)
    {
        cout << "How many nights will you stay?" << endl;
        string input;
        getline(cin, input);

        try
        {
            int nights = stoi(input);
            if (nights > 0)
            {
                return nights;
            }
            cout << "Please enter a positive number." << endl;
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a number." << endl;
        }
    }
}

// ----------------------------------------------------------------------------
// displaySummary — VOID FUNCTION WITH PARAMETERS
//
// This function doesn't return anything (void). It just displays output.
// But it needs a LOT of information to do its job, so we pass it all in
// as parameters. Notice it doesn't ask for input or calculate anything —
// it just formats and prints. One job!
// ----------------------------------------------------------------------------
void displaySummary(const string &dates, const string &origin,
                    const string &dest, const string &travelClass,
                    int flightCost, int roomChoice, int nights)
{
    // Room data (needed for display and cost calculation)
    const string roomNames[3]  = {"Deluxe Ocean-View", "Ocean-View", "Garden-View"};
    const int    roomPrices[3] = {350, 250, 150};

    string roomName  = roomNames[roomChoice];
    int    roomPrice = roomPrices[roomChoice];

    int hotelTotal = nights * roomPrice;
    int totalCost  = hotelTotal + flightCost;

    cout << "\n--- Booking Summary ---" << endl;
    cout << "Destination: Oahu, HI" << endl;
    cout << "Travel Dates: " << dates << endl;
    cout << "Flight: " << origin << " to " << dest
         << " (" << travelClass << ") - $" << flightCost << endl;
    cout << "Hotel: " << roomName << " for " << nights
         << " nights = $" << hotelTotal << endl;
    cout << "Total Trip Cost: $" << totalCost << endl;
}
