// =============================================================================
// m3LAB_1 - Oahu Travel Booking System (YOUR VERSION - Functions Practice)
// =============================================================================
// Your original booking program works great! Now let's level up by
// organizing it into FUNCTIONS. This makes the code easier to read,
// test, and modify later.
//
// YOUR MISSION: Fill in the function bodies marked with TODO.
// The prototypes, main(), and toLower() are done for you.
// Each TODO tells you what the function should do.
//
// FUNCTIONS YOU WILL WRITE:
//   askToTravel()    - Asks if user wants to travel (returns bool)
//   getTravelDates() - Collects and validates travel dates (returns string)
//   getString()      - General-purpose validated string input (returns string)
//   getTravelClass() - Gets economy/first with validation (returns string)
//   selectRoom()     - Displays room menu, gets choice (returns int)
//   getNights()      - Gets number of nights with validation (returns int)
//   displaySummary() - Displays the final booking summary (void)
//
// HINT: All the logic you need is already in your original program.
//       You're just MOVING code into functions, not writing new logic.
// =============================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

// =============================================================================
// Function Prototypes - DONE FOR YOU
// These tell the compiler what functions exist before we define them.
// =============================================================================
string toLower(const string& s);
bool   askToTravel();
string getTravelDates();
string getString(string prompt);
string getTravelClass();
int    selectRoom();
int    getNights();
void   displaySummary(string dates, string origin, string destination,
                      string travelClass, int flightCost,
                      string roomName, int roomPrice, int nights);

// =============================================================================
// main() - DONE FOR YOU
// Look how clean this is! Each line calls a function that handles one job.
// =============================================================================
int main()
{
    // Step 1: Ask if the user wants to travel
    if (!askToTravel())
    {

        return 0;
    }

    // Step 2: Collect all booking information
    string dates       = getTravelDates();
    string origin      = getString("origin city");
    string destination = getString("destination city");
    string travelClass = getTravelClass();

    // Step 3: Calculate flight cost
    // Simple enough to stay in main — no function needed
    int flightCost = (travelClass == "economy") ? 600 : 1200;

    // Step 4: Hotel selection
    const string roomNames[3]  = {"Deluxe Ocean-View", "Ocean-View", "Garden-View"};
    const int    roomPrices[3] = {350, 250, 150};

    int roomChoice = selectRoom();
    string roomName  = roomNames[roomChoice];
    int    roomPrice = roomPrices[roomChoice];

    // Step 5: Number of nights
    int nights = getNights();

    // Step 6: Display the summary
    displaySummary(dates, origin, destination, travelClass,
                   flightCost, roomName, roomPrice, nights);

    return 0;
}

// =============================================================================
// toLower() - DONE FOR YOU (this was already a helper function — nice work!)
// =============================================================================
string toLower(const string& s)
{
    string out = s;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

// =============================================================================
// TODO 1: askToTravel()
// -----------------------------------------------------------------------------
// This function should:
//   - Ask "Do you want to travel to Oahu, HI? (yes/no)"
//   - Use a while loop to keep asking until they say yes or no
//   - Return TRUE if they say yes
//   - Return FALSE if they say no (after printing a goodbye message)
//   - Print an error if they type anything else
//   - Use toLower() so "YES", "Yes", "yes" all work
//
// HINT: Look at the first section of your original program.
//       Replace 'break' with 'return true' and 'return 0' with 'return false'.
// =============================================================================
bool askToTravel()
{
    while (true) {
        cout << "Do you want to travel to Ohahu, HI? (yes/no)\n";  // from document
        string response;
        getline(cin, response);

        response = toLower(response);

        if (response == "yes") {
            return true;  // continue program
        }
        else if (response == "no") {
            cout << "Thank you. Have a great day!\n";
            return false;  // exit program
        }
        else {
            cout << "Please enter 'yes' or 'no'.\n";
        }
    }


}

// =============================================================================
// TODO 2: getTravelDates()
// -----------------------------------------------------------------------------
// This function should:
//   - Ask "Enter your travel dates (MM/DD/YYYY - MM/DD/YYYY):"
//   - Use a while loop to keep asking until input contains a '-'
//   - Return the valid date string
//
// HINT: Look at your "DO-WHILE SIMULATION: Travel dates" section.
//       Replace 'break' with 'return dates'.
// =============================================================================
string getTravelDates()
{
    string dates;
    while (true) {
        cout << "Enter your travel dates (MM/DD/YYYY - MM/DD/YYYY):\n";  // from document
        getline(cin, dates);

        if (dates.find('-') != string::npos) {
            return dates;
        } else {
            cout << "Invalid format. Please try again.\n";
        }
    }


}

// =============================================================================
// TODO 3: getString()
// -----------------------------------------------------------------------------
// This function should:
//   - Display "Please enter your " + prompt + ":"
//   - Use a while loop to keep asking until input is not empty
//   - Return the non-empty string
//
// The 'prompt' parameter lets us reuse this function for different inputs.
// In main() we call it twice:
//   getString("origin city")       -> "Please enter your origin city:"
//   getString("destination city")  -> "Please enter your destination city:"
//
// HINT: This is simpler than your original for loop version.
//       Just validate that the entry is not empty and return it.
// =============================================================================
string getString(string prompt)
{
    cout << "Please enter your " << prompt << ":";
    string entry;
    getline(cin, entry);
    return entry;




}

// =============================================================================
// TODO 4: getTravelClass()
// -----------------------------------------------------------------------------
// This function should:
//   - Ask "Please enter your travel class (economy/first):"
//   - Use a while loop to keep asking until they enter economy or first
//   - Use toLower() so "ECONOMY", "Economy", etc. all work
//   - Return the LOWERCASE version of their choice
//
// HINT: This is like getString() but with extra validation.
//       Check for empty input AND check that it's economy or first.
// =============================================================================
string getTravelClass()
{
    cout << "Please enter your travel class (economy/first): " << endl;
    string travel_class;
    cin >> travel_class;
    return travel_class;
    


}

// =============================================================================
// TODO 5: selectRoom()
// -----------------------------------------------------------------------------
// This function should:
//   - Display the three room options with prices using a for loop:
//       1. Deluxe Ocean-View - $350 per night
//       2. Ocean-View - $250 per night
//       3. Garden-View - $150 per night
//   - Ask "Select a room type by number (1-3):"
//   - Validate input (only accept "1", "2", or "3")
//   - Return the ARRAY INDEX (0, 1, or 2) — not what the user typed!
//
// HINT: The room data arrays go INSIDE this function since only this
//       function needs them for display. Use stoi(input) - 1 to convert.
// =============================================================================
int selectRoom()
{
    // YOUR CODE HERE


}

// =============================================================================
// TODO 6: getNights()
// -----------------------------------------------------------------------------
// This function should:
//   - Ask "How many nights will you stay?"
//   - Validate that input is a positive number
//   - Handle non-numeric input with try/catch
//   - Return the valid number of nights
//
// HINT: This is almost identical to your original code.
//       Replace 'break' with 'return nights'.
// =============================================================================
int getNights()
{
    // YOUR CODE HERE


}

// =============================================================================
// TODO 7: displaySummary()
// -----------------------------------------------------------------------------
// This is a VOID function — it doesn't return anything.
// It just displays the final booking summary.
//
// This function should:
//   - Calculate hotel total (nights * roomPrice)
//   - Calculate total cost (hotelTotal + flightCost)
//   - Display the formatted booking summary:
//       --- Booking Summary ---
//       Destination: Oahu, HI
//       Travel Dates: [dates]
//       Flight: [origin] to [destination] ([class] class) - $[cost]
//       Hotel: [room] for [nights] nights = $[hotel total]
//       Total Trip Cost: $[total]
//
// IMPORTANT: This function can't "see" main()'s variables!
//   Everything it needs is passed in through the parameters.
//   Look at the parameter list above — those are your variables.
// =============================================================================
void displaySummary(string dates, string origin, string destination,
                    string travelClass, int flightCost,
                    string roomName, int roomPrice, int nights)
{
    // YOUR CODE HERE


}
