// ============================================================================
// m5lab1.h  —  Trip Planner: Choice Function Prototypes & Definitions
// ============================================================================
// This header contains EVERYTHING related to the branching story/choices.
// m5lab1.cpp includes this file after declaring global variables, so all
// choice functions here can read and write those globals freely.
//
// FILE LAYOUT:
//   1. PROTOTYPES  — one line each, with a semicolon, listed at the top
//   2. DEFINITIONS — full function bodies, listed below the prototypes
//
// BRANCH MAP:
//
//   main_menu()
//     │
//     ├─1─► choice_select_destination()
//     │          └──► choice_destination_details()   ← sub-branch
//     │
//     ├─2─► choice_select_dates()
//     │
//     ├─3─► choice_select_travel_class()
//     │          └──► choice_upgrade_class()          ← sub-branch
//     │
//     ├─4─► choice_select_hotel()
//     │
//     ├─5─► choice_add_activities()
//     │
//     └─6─► choice_view_summary()
//               ├──► ENDING A: Luxury trip (high budget)
//               └──► ENDING B: Budget trip (lower spend)
//
// ============================================================================

#ifndef M5LAB1_H   // Include guard — prevents this file from being included twice
#define M5LAB1_H   // which would cause "function already defined" errors

// ============================================================================
// SECTION 1 — FUNCTION PROTOTYPES
// Prototypes tell the compiler "this function exists somewhere below."
// Without them, calling choice_destination_details() inside
// choice_select_destination() would fail because the compiler reads
// top-to-bottom and hasn't seen the definition yet.
// ============================================================================

void choice_select_destination();              // Menu option 1
void choice_destination_details(string dest);  // Sub-branch: details for chosen city
void choice_select_dates();                    // Menu option 2
void choice_select_travel_class();             // Menu option 3
void choice_upgrade_class();                   // Sub-branch: upgrade to first class
void choice_select_hotel();                    // Menu option 4
void choice_add_activities();                  // Menu option 5
void choice_view_summary();                    // Menu option 6 — shows final plan


// ============================================================================
// SECTION 2 — FUNCTION DEFINITIONS
// Each function does exactly one job.  Notice how short and readable each
// one is because of this separation.
// ============================================================================


// ----------------------------------------------------------------------------
// choice_select_destination  —  Branch 1
//
// Displays a numbered list of destinations with estimated flight costs.
// The user picks one; we save it to the global g_destination and set a
// starting flight cost in g_flight_cost.
// After confirming the pick, we call choice_destination_details() to give
// the traveler a fun fact and a quick sub-choice about that city.
// ----------------------------------------------------------------------------
void choice_select_destination()
{
    // Parallel arrays: name[i] and cost[i] belong to the same destination
    const string destinations[5] = {
        "Oahu, Hawaii",
        "Cancun, Mexico",
        "Paris, France",
        "Tokyo, Japan",
        "New York City, USA"
    };

    // Base economy flight cost for each destination (index matches above)
    const int flightCosts[5] = { 600, 500, 1200, 1400, 300 };

    cout << "\n--- SELECT YOUR DESTINATION ---" << endl;
    cout << "Available destinations (economy flight estimate):" << endl;

    // Print each destination with its number and cost
    for (int i = 0; i < 5; i++)
    {
        cout << "  " << (i + 1) << ". "
             << destinations[i]
             << "  (~$" << flightCosts[i] << " flight)" << endl;
    }

    // Keep asking until the user gives a valid number
    while (true)
    {
        cout << "\nEnter destination number (1-5): ";
        string input;
        getline(cin, input);   // getline avoids leftover-newline bugs with cin >>

        try
        {
            int idx = stoi(input) - 1;   // Convert to 0-based array index

            if (idx >= 0 && idx < 5)
            {
                // Save the user's choices into the global trip-plan variables
                g_destination = destinations[idx];
                g_flight_cost = flightCosts[idx];   // Will be adjusted by class later

                cout << "\n✔ Destination set to: " << g_destination << endl;

                // Hand off to the sub-branch for fun facts and a follow-up choice
                choice_destination_details(g_destination);
                return;   // Done with this branch — return to main_menu()
            }
            else
            {
                cout << "Please enter a number between 1 and 5." << endl;
            }
        }
        catch (...)
        {
            // stoi() throws if the string isn't a number
            cout << "Invalid input. Please enter a number." << endl;
        }
    }
}


// ----------------------------------------------------------------------------
// choice_destination_details  —  Sub-Branch of choice_select_destination()
//
// Receives the destination string as a parameter (not a global) to keep
// the logic clean.  Shows a fun fact about the destination and asks the
// user if they want to look at activities now or later.
//
// This demonstrates:
//   • A void function WITH a parameter
//   • Calling another branch (choice_add_activities) from inside a branch
// ----------------------------------------------------------------------------
void choice_destination_details(string dest)
{
    cout << "\n--- DESTINATION DETAILS ---" << endl;

    // Use if/else-if to print a relevant fact for each destination.
    // We compare dest directly because we set it from the same array.
    if (dest == "Oahu, Hawaii")
    {
        cout << "Oahu is home to Waikiki Beach and the Pearl Harbor memorial." << endl;
        cout << "Best travel months: April–June and September–November." << endl;
    }
    else if (dest == "Cancun, Mexico")
    {
        cout << "Cancun sits on the Caribbean coast with turquoise water." << endl;
        cout << "Best travel months: December–April (dry season)." << endl;
    }
    else if (dest == "Paris, France")
    {
        cout << "Paris offers world-class art, cuisine, and the Eiffel Tower." << endl;
        cout << "Best travel months: April–June and October." << endl;
    }
    else if (dest == "Tokyo, Japan")
    {
        cout << "Tokyo blends ultra-modern tech with centuries-old temples." << endl;
        cout << "Best travel months: March–May (cherry blossoms) and October–November." << endl;
    }
    else   // New York City
    {
        cout << "NYC never sleeps — Broadway, Central Park, world-class food." << endl;
        cout << "Best travel months: April–June and September–November." << endl;
    }

    // Ask if the user wants to jump straight to activities
    cout << "\nWould you like to browse activities for " << dest << " now? (yes/no): ";
    string response;
    getline(cin, response);
    response = toLower(response);   // toLower() is defined in m5lab1.cpp

    if (response == "yes")
    {
        // Call the activities branch right away instead of returning to menu
        choice_add_activities();
    }
    else
    {
        cout << "You can add activities from the main menu anytime." << endl;
    }
    // Either way, control returns up to choice_select_destination(), then to menu
}


// ----------------------------------------------------------------------------
// choice_select_dates  —  Branch 2
//
// Collects the travel date range and number of nights.
// Dates are stored as a formatted string (display only).
// Nights are stored as an integer (used in cost calculations).
// ----------------------------------------------------------------------------
void choice_select_dates()
{
    cout << "\n--- SELECT TRAVEL DATES ---" << endl;

    // --- Collect the date range string ---
    while (true)
    {
        cout << "Enter travel dates (MM/DD/YYYY - MM/DD/YYYY): ";
        string dates;
        getline(cin, dates);

        // Basic validation: a valid range must contain a dash separator
        if (dates.find('-') != string::npos && dates.length() >= 10)
        {
            g_travel_dates = dates;   // Save to global
            cout << "✔ Travel dates set to: " << g_travel_dates << endl;
            break;
        }
        else
        {
            cout << "Invalid format. Please use: MM/DD/YYYY - MM/DD/YYYY" << endl;
        }
    }

    // --- Collect the number of nights ---
    while (true)
    {
        cout << "How many nights will you stay? ";
        string input;
        getline(cin, input);

        try
        {
            int nights = stoi(input);

            if (nights > 0 && nights <= 90)   // Reasonable trip length: 1–90 nights
            {
                g_nights = nights;   // Save to global
                cout << "✔ Number of nights set to: " << g_nights << endl;
                return;
            }
            else
            {
                cout << "Please enter a number between 1 and 90." << endl;
            }
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a whole number." << endl;
        }
    }
}


// ----------------------------------------------------------------------------
// choice_select_travel_class  —  Branch 3
//
// Offers three cabin classes and adjusts the flight cost multiplier.
// If the user picks economy, we offer an upgrade prompt (sub-branch).
// This shows branching logic inside a branch function.
// ----------------------------------------------------------------------------
void choice_select_travel_class()
{
    cout << "\n--- SELECT TRAVEL CLASS ---" << endl;
    cout << "  1. Economy       (base flight price)" << endl;
    cout << "  2. Business      (2x base flight price)" << endl;
    cout << "  3. First Class   (3x base flight price)" << endl;

    while (true)
    {
        cout << "\nEnter class (1-3): ";
        string input;
        getline(cin, input);

        if (input == "1")
        {
            g_travel_class = "Economy";
            // Flight cost stays at the base set during destination selection
            cout << "✔ Travel class set to: Economy" << endl;

            // Sub-branch: offer upgrade to people who picked economy
            choice_upgrade_class();
            return;
        }
        else if (input == "2")
        {
            g_travel_class = "Business";
            g_flight_cost  = g_flight_cost * 2;   // Business doubles the base
            cout << "✔ Travel class set to: Business" << endl;
            cout << "   Updated flight cost: $" << g_flight_cost << endl;
            return;
        }
        else if (input == "3")
        {
            g_travel_class = "First Class";
            g_flight_cost  = g_flight_cost * 3;   // First class triples the base
            cout << "✔ Travel class set to: First Class" << endl;
            cout << "   Updated flight cost: $" << g_flight_cost << endl;
            return;
        }
        else
        {
            cout << "Please enter 1, 2, or 3." << endl;
        }
    }
}


// ----------------------------------------------------------------------------
// choice_upgrade_class  —  Sub-Branch of choice_select_travel_class()
//
// Only reached when the user chose Economy.  Gives them a one-time pitch
// to upgrade, then adjusts the flight cost if they accept.
// ----------------------------------------------------------------------------
void choice_upgrade_class()
{
    cout << "\n--- UPGRADE OFFER ---" << endl;
    cout << "Economy class selected.  For only $" << (g_flight_cost) << " more" << endl;
    cout << "you could upgrade to Business and enjoy extra legroom," << endl;
    cout << "priority boarding, and complimentary meals." << endl;
    cout << "Upgrade to Business class? (yes/no): ";

    string response;
    getline(cin, response);
    response = toLower(response);

    if (response == "yes")
    {
        g_travel_class = "Business";        // Override the Economy choice
        g_flight_cost  = g_flight_cost * 2; // Apply the 2x multiplier
        cout << "✔ Upgraded to Business Class!" << endl;
        cout << "   Updated flight cost: $" << g_flight_cost << endl;
    }
    else
    {
        cout << "No problem — Economy it is!" << endl;
        // g_travel_class and g_flight_cost stay as Economy (already set above)
    }
}


// ----------------------------------------------------------------------------
// choice_select_hotel  —  Branch 4
//
// Displays three hotel tiers and saves the user's pick plus cost-per-night.
// The actual hotel total is calculated later in choice_view_summary().
// ----------------------------------------------------------------------------
void choice_select_hotel()
{
    // Parallel arrays for hotel options
    const string hotelNames[3] = {
        "Budget Inn      (no-frills, clean, central location)",
        "Comfort Suites  (pool, breakfast included)",
        "Luxury Resort   (full service, ocean/city view)"
    };

    // Cost per night for each tier
    const int hotelRates[3] = { 120, 220, 400 };

    cout << "\n--- SELECT YOUR HOTEL ---" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "  " << (i + 1) << ". " << hotelNames[i]
             << "  — $" << hotelRates[i] << "/night" << endl;
    }

    while (true)
    {
        cout << "\nEnter hotel choice (1-3): ";
        string input;
        getline(cin, input);

        if (input == "1" || input == "2" || input == "3")
        {
            int idx      = stoi(input) - 1;   // Convert to 0-based index
            g_hotel      = hotelNames[idx];   // Save full display name
            g_hotel_cost = hotelRates[idx];   // Save nightly rate

            cout << "✔ Hotel set to: " << g_hotel << endl;
            return;
        }
        else
        {
            cout << "Please enter 1, 2, or 3." << endl;
        }
    }
}


// ----------------------------------------------------------------------------
// choice_add_activities  —  Branch 5
//
// Lets the user type in activities they'd like to do.
// Demonstrates a simple accumulator: each entry is appended to g_activities.
// The user types "done" to finish.
// ----------------------------------------------------------------------------
void choice_add_activities()
{
    cout << "\n--- ADD ACTIVITIES ---" << endl;

    if (!g_destination.empty())
    {
        cout << "Add activities for your trip to " << g_destination << "." << endl;
    }
    else
    {
        cout << "Add activities for your trip." << endl;
    }

    cout << "(Type each activity and press Enter. Type 'done' when finished.)" << endl;

    // Clear any previously saved activities before rebuilding the list
    g_activities = "";

    int count = 0;   // Track how many activities were entered

    while (true)
    {
        cout << "  Activity " << (count + 1) << ": ";
        string activity;
        getline(cin, activity);

        if (toLower(activity) == "done")
        {
            break;   // Exit the loop when the user is finished
        }
        else if (activity.empty())
        {
            cout << "  (Activity cannot be blank. Type 'done' to finish.)" << endl;
        }
        else
        {
            // Append this activity to the running list, separated by ", "
            if (!g_activities.empty())
            {
                g_activities += ", ";   // Add separator between activities
            }
            g_activities += activity;
            count++;

            // Cap the list at 8 activities to keep output readable
            if (count >= 8)
            {
                cout << "  (Maximum of 8 activities reached.)" << endl;
                break;
            }
        }
    }

    if (count == 0)
    {
        g_activities = "None planned";   // Friendly placeholder for the summary
        cout << "No activities added." << endl;
    }
    else
    {
        cout << "✔ " << count << " activit" << (count == 1 ? "y" : "ies")
             << " saved." << endl;
    }
}


// ----------------------------------------------------------------------------
// choice_view_summary  —  Branch 6  (two possible endings)
//
// Calculates the total trip cost from all saved globals and prints a
// formatted itinerary.  The "ending" branches on total cost:
//   • ENDING A — Luxury Trip  (total > $3,000)
//   • ENDING B — Budget Trip  (total <= $3,000)
//
// Also warns the user if required fields are missing so they know what
// still needs to be filled in before the plan is complete.
// ----------------------------------------------------------------------------
void choice_view_summary()
{
    cout << "\n========================================" << endl;
    cout << "          YOUR TRIP PLAN SUMMARY        " << endl;
    cout << "========================================" << endl;

    // ---- Check which fields have been filled in ----
    bool missingInfo = false;

    if (g_destination.empty())
    {
        cout << "  ⚠  Destination:    (not selected — use menu option 1)" << endl;
        missingInfo = true;
    }
    else
    {
        cout << "  Destination:      " << g_destination << endl;
    }

    if (g_travel_dates.empty())
    {
        cout << "  ⚠  Travel Dates:   (not entered — use menu option 2)" << endl;
        missingInfo = true;
    }
    else
    {
        cout << "  Travel Dates:     " << g_travel_dates << endl;
        cout << "  Nights:           " << g_nights << endl;
    }

    if (g_travel_class.empty())
    {
        cout << "  ⚠  Travel Class:   (not selected — use menu option 3)" << endl;
        missingInfo = true;
    }
    else
    {
        cout << "  Travel Class:     " << g_travel_class << endl;
        cout << "  Flight Cost:      $" << g_flight_cost << endl;
    }

    if (g_hotel.empty())
    {
        cout << "  ⚠  Hotel:          (not selected — use menu option 4)" << endl;
        missingInfo = true;
    }
    else
    {
        // Calculate hotel total only if we have both hotel and nights
        int hotelTotal = (g_nights > 0) ? g_hotel_cost * g_nights : 0;
        cout << "  Hotel:            " << g_hotel << endl;
        cout << "  Hotel Total:      $" << hotelTotal
             << "  (" << g_nights << " nights x $" << g_hotel_cost << ")" << endl;
    }

    // Activities are optional — always show them
    cout << "  Activities:       "
         << (g_activities.empty() ? "None planned" : g_activities) << endl;

    // ---- Calculate and show total only if all required fields are present ----
    if (!missingInfo)
    {
        int hotelTotal = g_hotel_cost * g_nights;     // Total hotel spend
        int grandTotal = g_flight_cost + hotelTotal;  // Full trip cost

        cout << "----------------------------------------" << endl;
        cout << "  TOTAL ESTIMATED COST:  $" << grandTotal << endl;
        cout << "========================================" << endl;

        // ---- ENDING A: Luxury Trip ----
        if (grandTotal > 3000)
        {
            cout << "\n★  LUXURY TRIP UNLOCKED  ★" << endl;
            cout << "You're planning a top-tier getaway!" << endl;
            cout << "Expect premium service and unforgettable memories." << endl;
            cout << "Don't forget travel insurance for a trip this special." << endl;
        }
        // ---- ENDING B: Budget-Smart Trip ----
        else
        {
            cout << "\n✈  SMART TRAVELER AWARD  ✈" << endl;
            cout << "You've put together a great trip at a great price." << endl;
            cout << "Consider a travel rewards card to earn miles on this booking!" << endl;
        }
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "  Complete the missing steps above" << endl;
        cout << "  to see your total cost and trip summary." << endl;
        cout << "========================================" << endl;
    }
}

#endif   // M5LAB1_H — end of include guard
