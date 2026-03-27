// ============================================================================
// m5lab1.cpp  —  Trip Planner: Main Program File
// ============================================================================
// This file is the "engine" of the Trip Planner.  It contains:
//   1. Global variables  — shared trip-plan data used by all choice functions
//   2. A utility function (toLower) — used throughout for input validation
//   3. #include "m5lab1.h" — pulls in all the choice functions
//   4. main_menu()  — the looping menu that routes user choices
//   5. main()       — the program entry point
//
// WHY TWO FILES?
//   Separating the story/choice logic (m5lab1.h) from the engine (m5lab1.cpp)
//   keeps each file focused on one job and makes it easy to extend the story
//   without touching the menu or main() at all.
//
// BUILDING:
//   g++ m5lab1.cpp -o m5lab1
//   (The .h file is pulled in automatically via #include)
// ============================================================================

#include <iostream>    // cout, cin, endl
#include <string>      // string, getline
#include <algorithm>   // transform() — used in toLower()
using namespace std;


// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
// These variables hold the traveler's choices and persist across all the
// choice function calls.  Any function can read or write them because they
// are declared outside of any function (global scope).
//
// Naming convention: g_ prefix makes globals easy to spot in large files.
// ============================================================================

string g_destination  = "";   // The city/country the user is traveling to
string g_travel_dates = "";   // Date range as a display string (e.g. "03/15/2026 - 03/22/2026")
string g_travel_class = "";   // Cabin class: "Economy", "Business", or "First Class"
int    g_nights       = 0;    // Number of nights at the hotel
int    g_flight_cost  = 0;    // Flight cost (set by destination, adjusted by class)
string g_hotel        = "";   // Hotel tier name chosen by the user
int    g_hotel_cost   = 0;    // Nightly hotel rate (used to compute total in summary)
string g_activities   = "";   // Comma-separated list of activities the user entered


// ============================================================================
// UTILITY FUNCTION — toLower
// ============================================================================
// Converts a string to all-lowercase so that "YES", "Yes", and "yes" all
// compare equal.  Used whenever we validate yes/no or keyword input.
//
// Parameter:  s — the string to convert (passed by const reference to avoid
//                 making an unnecessary copy of the original)
// Returns:    a new string with every character in lowercase
// ============================================================================
string toLower(const string& s)
{
    string out = s;   // Make a copy so we don't modify the caller's string

    // transform() visits each character and applies ::tolower to it in-place
    transform(out.begin(), out.end(), out.begin(), ::tolower);

    return out;   // Return the lowercased copy
}


// ============================================================================
// INCLUDE THE HEADER
// ============================================================================
// This must come AFTER the global variables and toLower() definition because
// the choice functions inside m5lab1.h use all of them.  If we moved this
// include to the very top, the compiler would error — the globals and
// toLower() wouldn't exist yet when it tried to compile the choice functions.
// ============================================================================
#include "m5lab1.h"


// ============================================================================
// main_menu  —  The Routing Hub
// ============================================================================
// Displays the trip-planner menu and calls the appropriate choice function
// based on the user's input.  Loops indefinitely until the user chooses Quit.
//
// Note: main_menu() is defined HERE (after the #include) so that it can call
// the choice functions that are defined in m5lab1.h.
// ============================================================================
void main_menu()
{
    while (true)   // Keep the menu visible until the user explicitly quits
    {
        // ---- Display the menu ----
        cout << "\n========================================" << endl;
        cout << "       TRIP PLANNER  —  MAIN MENU      " << endl;
        cout << "========================================" << endl;

        // Show a quick status line for each option so the user knows what
        // they've filled in already without having to open the summary.
        cout << "  1. Destination  : "
             << (g_destination.empty()  ? "(not set)" : g_destination)  << endl;

        cout << "  2. Travel Dates : "
             << (g_travel_dates.empty() ? "(not set)" : g_travel_dates) << endl;

        cout << "  3. Travel Class : "
             << (g_travel_class.empty() ? "(not set)" : g_travel_class) << endl;

        cout << "  4. Hotel        : "
             << (g_hotel.empty()        ? "(not set)" : g_hotel)        << endl;

        cout << "  5. Activities   : "
             << (g_activities.empty()   ? "(none)"    : g_activities)   << endl;

        cout << "  6. View Trip Summary" << endl;
        cout << "  7. Quit" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Choice (1-7): ";

        string input;
        getline(cin, input);   // Read the full line to prevent newline bugs

        // ---- Parse input as integer ----
        int choice = 0;
        try
        {
            choice = stoi(input);   // stoi converts "1" -> 1, throws if not a number
        }
        catch (...)
        {
            // stoi threw an exception — user typed something that isn't a number
            cout << "Please enter a number between 1 and 7." << endl;
            continue;   // Skip the switch and loop back to the menu
        }

        // ---- Route to the matching choice function ----
        switch (choice)
        {
            case 1:
                choice_select_destination();    // Branch 1 — defined in m5lab1.h
                break;

            case 2:
                choice_select_dates();          // Branch 2 — defined in m5lab1.h
                break;

            case 3:
                choice_select_travel_class();   // Branch 3 — defined in m5lab1.h
                break;

            case 4:
                choice_select_hotel();          // Branch 4 — defined in m5lab1.h
                break;

            case 5:
                choice_add_activities();        // Branch 5 — defined in m5lab1.h
                break;

            case 6:
                choice_view_summary();          // Branch 6 — defined in m5lab1.h
                break;

            case 7:
                // Polite exit message, then fall out of the loop
                cout << "\nThank you for using Trip Planner!" << endl;
                cout << "Safe travels wherever the journey takes you." << endl;
                return;   // Return to main(), which then exits the program

            default:
                // Catches numbers outside 1-7
                cout << "Please enter a number between 1 and 7." << endl;
        }
    }
}


// ============================================================================
// main  —  Program Entry Point
// ============================================================================
// Every C++ program starts here.  main() is intentionally short — it just
// shows a welcome banner, asks if the user wants to start, and hands off to
// main_menu() for the rest of the work.
// ============================================================================
int main()
{
    // ---- Welcome banner ----
    cout << "========================================" << endl;
    cout << "        WELCOME TO TRIP PLANNER         " << endl;
    cout << "    Plan your perfect getaway today!    " << endl;
    cout << "========================================" << endl;

    // ---- Ask if the user is ready to start ----
    // We loop here so accidental typos don't kill the program.
    while (true)
    {
        cout << "\nReady to start planning your trip? (yes/no): ";
        string response;
        getline(cin, response);        // Read the full input line
        response = toLower(response);  // Normalize to lowercase for comparison

        if (response == "yes")
        {
            break;   // Exit this loop and continue to main_menu()
        }
        else if (response == "no")
        {
            cout << "No problem! Come back when you're ready to travel." << endl;
            return 0;   // Exit the program cleanly (0 = success)
        }
        else
        {
            cout << "Please type 'yes' or 'no'." << endl;
        }
    }

    // ---- Hand off to the main menu ----
    // All the real work happens in main_menu() and the choice functions.
    main_menu();

    return 0;   // 0 tells the OS the program finished successfully
}
