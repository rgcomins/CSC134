# Product Requirements Document (PRD)
## Hale Koa Hotel Booking System (m8)

**Project Name:** Island Flask App — Hale Koa Hotel Booking
**Author:** Richard Comins
**Version:** 2.0 (MVP, no email)
**Last Updated:** May 2026
**Status:** Functional MVP, email feature removed; image-and-price display on the summary is the next visual enhancement.

---

## 1. Executive Summary

### 1.1 Product Overview
The Hale Koa Hotel Booking System is a Flask-based web application that lets a user plan a vacation at the Hale Koa Hotel in Hawaii and see an itemized cost breakdown. The application demonstrates fundamental web development concepts: form handling, server-side data processing, date calculations, and Jinja2 templating.

This version removes the email-confirmation feature from the original prototype. All output stays on the trip-summary page; nothing is sent off the server.

### 1.2 Purpose
This project is an educational example for CSC 134 students, demonstrating:
- Flask web framework fundamentals
- HTML form creation and processing
- Server-side data validation and calculations
- Jinja2 template rendering with dynamic image lookup

### 1.3 Target Audience
- **Primary:** Students learning Flask web development
- **Secondary:** Instructors demonstrating real-world web application patterns
- **Tertiary:** Users planning a hypothetical trip to the Hale Koa Hotel

### 1.4 Changes from v1.0
- **Removed:** EmailJS integration, the email field's role in confirmation, the `userEmail`-driven email send, and the `/submit` legacy route.
- **Kept:** Landing page, room gallery, booking form, activities, travel style, comments, server-side cost calculation, trip-summary page.
- **Planned visual enhancement:** Display the chosen room's image alongside its nightly price on the trip-summary page (data already flows; this is presentation polish).

---

## 2. User Stories

### 2.1 Core User Stories (MVP)

| ID | As a... | I want to... | So that... | Priority |
|----|---------|--------------|------------|----------|
| US-01 | Visitor | View the hotel landing page | I can learn about the Hale Koa Hotel | Must Have |
| US-02 | Visitor | See available room types with images | I can visualize my accommodation options | Must Have |
| US-03 | Guest | Enter my name and travel dates | My booking is personalized | Must Have |
| US-04 | Guest | Select a room type with pricing | I can choose accommodations within my budget | Must Have |
| US-05 | Guest | Specify the number of nights | The system can calculate my total stay cost | Must Have |
| US-06 | Guest | Select activities to add to my trip | I can plan a complete vacation experience | Must Have |
| US-07 | Guest | See a detailed trip summary | I understand the full cost breakdown | Must Have |
| US-08 | Guest | See an image of my chosen room with its nightly price on the summary | I get a visual confirmation of what I picked | Must Have |

### 2.2 Enhanced User Stories (Future)

| ID | As a... | I want to... | So that... | Priority |
|----|---------|--------------|------------|----------|
| US-09 | Guest | Choose my preferred travel style | I can get tailored recommendations | Could Have |
| US-10 | Guest | Add comments to my booking | I can communicate special requests | Could Have |
| US-11 | Admin | View booking submissions | I can manage reservations | Won't Have (MVP) |

> **Removed from v1.0:** "Receive an email confirmation" is no longer in scope.

---

## 3. Functional Requirements

### 3.1 Landing Page (`/`)
- **FR-01:** Display welcome message with hotel branding
- **FR-02:** Show background image of Hawaii/hotel location
- **FR-03:** Provide navigation link to room selection page
- **FR-04:** Support GET (POST not required for v2)

### 3.2 Room Selection Page (`/rooms`)
- **FR-05:** Display all available room types with images:
  - Deluxe Ocean Front ($395/night)
  - Ilima Ocean West ($345/night)
  - Ocean View ($295/night)
  - Partial Ocean View ($219/night)
  - Resort View ($189/night)

- **FR-06:** Provide booking form with the following fields:

  | Field | Type | Required | Validation |
  |-------|------|----------|------------|
  | Name | Text | Yes | Non-empty |
  | Travel Start Date | Date | Yes | Valid date |
  | Ticket Price | Number | Yes | Positive integer |
  | Room Type | Dropdown | Yes | Valid selection |
  | Number of Nights | Number | Yes | Positive integer |
  | Activities | Checkboxes | No | Multiple selection |
  | Travel Style | Radio | No | Single selection |
  | Comments | Textarea | No | 500 char max |

  > **Removed:** the Email field. The form no longer collects an email address.

- **FR-07:** Available activities with pricing:
  - Surfing ($125)
  - Hiking ($75)
  - Snorkeling ($149)
  - Attend a Luau ($130)

- **FR-08:** Embed promotional YouTube video

- **FR-09:** Form submits via standard HTML POST directly to `/trip_summary`. No JavaScript interception, no third-party SDKs.

### 3.3 Trip Summary Page (`/trip_summary`)
- **FR-10:** Display personalized trip summary with traveler name
- **FR-11:** **Display the chosen room's image and nightly price** prominently near the top of the summary (image card with price label).
- **FR-12:** Calculate and display:
  - Travel date range (start date + number of nights)
  - Room type and nightly rate
  - Ticket price
  - Selected activities and their costs
  - Total cost of stay (nights × room rate)
  - Subtotal (stay + tickets + activities)
  - Tax (10.25% of subtotal)
  - Grand total
- **FR-13:** Format all currency values with comma separators and 2 decimal places
- **FR-14:** Provide navigation link back to home page

### 3.4 Removed: Email Integration
The entire "Email Integration" section from v1.0 (FR-13/14/15 in the prior PRD) is removed. The application does not send, queue, or store email. No EmailJS, no Flask-Mail, no SMTP configuration, no email-related template variables.

---

## 4. Technical Requirements

### 4.1 Technology Stack

| Component | Technology | Version |
|-----------|------------|---------|
| Backend Framework | Flask | 3.x |
| Template Engine | Jinja2 | (bundled) |
| Programming Language | Python | 3.8+ |
| Frontend | HTML5, CSS3 | — |
| Development Server | Werkzeug | (bundled) |

> Removed: EmailJS, JavaScript-side form interception, mailtrap/SMTP credentials.

### 4.2 Application Architecture

```
m8/
├── app.py                 # Main Flask application
├── design_doc.md          # Project 4 design doc (this version)
├── PRD.md                 # This document
├── README.md              # Run/build instructions
├── static/                # Static assets
│   ├── deluxe.png
│   ├── ilima.png
│   ├── ocean-view-room.png
│   ├── partial-ocean-view-room.png
│   ├── resort-view.png
│   ├── halekoa_Hotel.webp
│   └── rainbow_map.jpg
└── templates/             # Jinja2 templates
    ├── index.html         # Landing page
    ├── ROOMS.html         # Room selection & booking form
    └── trip_summary.html  # Trip cost calculation + chosen-room image/price
```

> Removed: `results.html` (only used by the legacy `/submit` route), and any email-related JS in `ROOMS.html`.

### 4.3 Route Specifications

| Route | Method(s) | Handler | Template | Description |
|-------|-----------|---------|----------|-------------|
| `/` | GET | `home_page()` | `index.html` | Landing page |
| `/rooms` | GET | `rooms()` | `ROOMS.html` | Room selection |
| `/trip_summary` | POST | `trip_summary()` | `trip_summary.html` | Cost calculation |

> Removed: `/submit` legacy form handler.

### 4.4 Data Flow

```
User visits homepage (/)
         │
         ▼
Clicks "Rooms" link
         │
         ▼
Views room images & fills booking form (/rooms)
         │
         ▼
Form POSTs directly to /trip_summary  (no JS interception)
         │
         ▼
Flask:
  • Parses room name/price + image filename
  • Parses activities, sums costs
  • Computes date range
  • Computes stay, subtotal, tax (10.25%), grand total
         │
         ▼
trip_summary.html renders:
  • Chosen room image + nightly price card
  • Itemized breakdown
```

### 4.5 Calculation Logic

```python
# Room cost calculation
cost_of_stay = num_nights * room_price

# Date range calculation
end_date = start_date + timedelta(days=num_nights)

# Activity cost (sum of selected activities)
activity_cost = sum(cost for name, cost in selected_activities)

# Final calculations
sub_total = cost_of_stay + ticket_price + activity_cost
tax = round(sub_total * 0.1025, 2)   # Hawaii lodging tax rate
total = sub_total + tax
```

---

## 5. User Interface Requirements

### 5.1 Landing Page
- Full-screen background image (`rainbow_map.jpg`)
- White text on transparent background
- Prominent "Rooms" navigation link (lime green)
- Welcoming headline message

### 5.2 Room Selection Page
- Room images displayed in a bordered table or gallery layout
- Booking form with white background, rounded corners
- Color-coded travel style radio buttons:
  - Luxury: Tomato red (#ff6347)
  - Budget: Steel blue (#4682b4)
  - Adventure: Lime green (#32cd32)
- Cyan submit button (#00ced1)
- Orange-red reset button (#ff4500)
- Green comment textarea (lightgreen)

### 5.3 Trip Summary Page
- **Chosen-room card at the top:** image (max-width ~400px, rounded corners, soft border) + room name + nightly price label.
- Clean layout with navigation
- Currency formatting with commas and decimals
- Bold grand total for emphasis
- Return link to home page

---

## 6. Room Inventory

| Room Type | Nightly Rate | Image File |
|-----------|--------------|------------|
| Deluxe Ocean Front | $395 | `deluxe.png` |
| Ilima Ocean West | $345 | `ilima.png` |
| Ocean View | $295 | `ocean-view-room.png` |
| Partial Ocean View | $219 | `partial-ocean-view-room.png` |
| Resort View | $189 | `resort-view.png` |

The Python `ROOMS` dict is the single source of truth for both price and image filename. `get_room_image(room_name)` returns the image filename, falling back to `halekoa_Hotel.webp` if the room name is unknown.

---

## 7. Activity Catalog

| Activity | Price | Value String |
|----------|-------|--------------|
| Surfing | $125 | `surfing|125` |
| Hiking | $75 | `hiking|75` |
| Snorkeling | $149 | `snorkeling|149` |
| Attend a Luau | $130 | `luau|130` |

---

## 8. Testing Scenarios

### 8.1 Basic Flow Test
1. Navigate to home page (`/`)
2. Click "Rooms" link
3. Fill form with valid data:
   - Name: "Test User"
   - Date: tomorrow
   - Ticket Price: 500
   - Room: Deluxe Ocean Front
   - Nights: 3
   - Activities: Surfing, Luau
4. Submit form
5. Verify trip summary shows:
   - Chosen-room image (`deluxe.png`) at top with `$395.00/night` label
   - Dates: Start to Start+3 days
   - Stay cost: $1,185.00
   - Activity cost: $255.00
   - Subtotal: $1,940.00
   - Tax: $198.85
   - Total: $2,138.85

### 8.2 Edge Cases

| Test | Input | Expected Result |
|------|-------|-----------------|
| No activities | Leave all unchecked | Activities: "None", Cost: $0 |
| Single night | nights = 1 | Stay cost = room rate |
| All activities | Select all 4 | Activity cost = $479 |
| Minimum room | Resort View | $189/night, `resort-view.png` shown |
| Unknown room name (manual tampering) | Submit `Rooms=Foo|100` | Fallback image `halekoa_Hotel.webp` |
| GET on `/trip_summary` | Direct URL | 405 Method Not Allowed (or graceful redirect to `/`) |

---

## 9. Known Limitations & Future Enhancements

### 9.1 Current Limitations
1. No server-side input validation beyond `int()`/`float()` parsing
2. No user authentication or session management
3. No database persistence (data lost on refresh)
4. No confirmation/receipt mechanism (email removed; nothing replaces it yet)
5. Travel style radio buttons not used in calculations
6. Comments field collected but not displayed in summary

### 9.2 Planned Enhancements

#### Phase 2
- [ ] Make the chosen-room image + price card the visual focus of the summary (this iteration)
- [ ] Surface comments and travel style on the summary
- [ ] Server-side validation with friendly error pages

#### Phase 3
- [ ] Database storage (SQLite)
- [ ] Booking confirmation numbers
- [ ] Printable / shareable summary view (replaces email-receipt use case)
- [ ] Responsive mobile layout
- [ ] Accessibility pass (alt text, ARIA, focus states)

---

## 10. Glossary

| Term | Definition |
|------|------------|
| **Flask** | Python micro web framework |
| **Jinja2** | Template engine used by Flask |
| **Hale Koa** | Military resort hotel in Waikiki, Hawaii |
| **MVP** | Minimum Viable Product |
| **PRD** | Product Requirements Document |

---

## 11. Appendix

### A. Sample Form Data Structure

```python
# Request form data received at /trip_summary
{
    "name": "John Doe",
    "dates": "2025-06-15",
    "ticketPrice": "450",
    "Rooms": "Deluxe Ocean Front|395",
    "num_nights": "5",
    "activity": ["surfing|125", "snorkeling|149"],
    "style": "luxury",
    "comments": "Anniversary trip"
}
```

> Note: no `userEmail` field.

### B. Rendered Template Variables

```python
# Variables passed to trip_summary.html
{
    "traveler_name": "John Doe",
    "type": "Deluxe Ocean Front",
    "room_image": "deluxe.png",
    "cost": 395.00,
    "dates": "2025-06-15 to 2025-06-20",
    "num_nights": 5,
    "ticket_price": 450,
    "activity": "surfing, snorkeling",
    "activityCost": 274,
    "cost_of_stay": 1975.00,
    "sub_total": 2699.00,
    "tax": 276.65,
    "total": 2975.65
}
```

> Note: no `email` variable.
