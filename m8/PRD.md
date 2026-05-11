# Product Requirements Document (PRD)
## Honolulu Hotels Booking System (m8)

**Project Name:** Island Flask App — Honolulu Hotels Booking
**Author:** Richard Comins
**Version:** 3.0 (Multi-hotel MVP)
**Last Updated:** May 2026
**Status:** Scope expanded from single-hotel (Hale Koa) to a curated menu of Honolulu hotels. Email feature still removed. Visual polish (chosen-room image + price card on summary) carries forward.

---

## 1. Executive Summary

### 1.1 Product Overview
The Honolulu Hotels Booking System is a Flask-based web application that lets a user pick a hotel from a curated menu of Honolulu properties, choose a room, plan add-on activities, and see an itemized cost breakdown for the trip. The application demonstrates fundamental web development concepts: form handling, server-side data processing, date calculations, nested data lookup, and Jinja2 templating.

This version expands the original single-hotel prototype (Hale Koa only) into a menu-driven experience. The user selects a hotel first, then sees that hotel's room inventory and booking form. The trip summary continues to feature the chosen room's image and nightly price.

### 1.2 Purpose
This project is an educational example for CSC 134 students, demonstrating:
- Flask web framework fundamentals with multiple related routes
- HTML form creation and processing
- Nested data structures (hotel → rooms) and lookup by URL parameter
- Server-side data validation and calculations
- Jinja2 template rendering with dynamic image lookup

### 1.3 Target Audience
- **Primary:** Students learning Flask web development
- **Secondary:** Instructors demonstrating real-world web application patterns
- **Tertiary:** Users planning a hypothetical trip to a Honolulu hotel

### 1.4 Changes from v2.0
- **Added:** Hotel menu page (`/hotels`) that lists a curated set of Honolulu hotels with hero image, location, short description, and a "Choose this hotel" call to action.
- **Changed:** `/rooms` route now requires a hotel selection. New URL shape is `/rooms/<hotel_slug>`. The page shows that hotel's banner and only that hotel's rooms.
- **Changed:** Data model. `HOTELS` is the new top-level dict: `{hotel_slug: {name, tagline, hero_image, location, rooms: {...}}}`. The per-hotel `rooms` mapping has the same shape as the old `ROOMS` dict.
- **Changed:** Trip summary now also displays the hotel name (in addition to room name, image, and nightly price).
- **Kept:** Email confirmation stays removed. Landing page, activities catalog, travel style, comments, server-side cost calculation, image-and-price card on summary all remain.

---

## 2. User Stories

### 2.1 Core User Stories (MVP)

| ID | As a... | I want to... | So that... | Priority |
|----|---------|--------------|------------|----------|
| US-01 | Visitor | View a welcome landing page | I can learn what the app does | Must Have |
| US-02 | Visitor | Browse a menu of Honolulu hotels with images and short descriptions | I can compare properties before picking one | Must Have |
| US-03 | Visitor | Choose a specific hotel and continue to its room selection page | I can focus on the property I care about | Must Have |
| US-04 | Visitor | See available room types with images **for the hotel I chose** | I can visualize my accommodation options | Must Have |
| US-05 | Guest | Enter my name and travel dates | My booking is personalized | Must Have |
| US-06 | Guest | Select a room type with pricing | I can choose accommodations within my budget | Must Have |
| US-07 | Guest | Specify the number of nights | The system can calculate my total stay cost | Must Have |
| US-08 | Guest | Select activities to add to my trip | I can plan a complete vacation experience | Must Have |
| US-09 | Guest | See a detailed trip summary | I understand the full cost breakdown | Must Have |
| US-10 | Guest | See an image of my chosen room with hotel name and nightly price on the summary | I get a visual confirmation of what I picked | Must Have |

### 2.2 Enhanced User Stories (Future)

| ID | As a... | I want to... | So that... | Priority |
|----|---------|--------------|------------|----------|
| US-11 | Guest | Choose my preferred travel style | I can get tailored recommendations | Could Have |
| US-12 | Guest | Add comments to my booking | I can communicate special requests | Could Have |
| US-13 | Visitor | Filter hotels by price range or neighborhood | I can narrow the menu | Won't Have (MVP) |
| US-14 | Admin | View booking submissions | I can manage reservations | Won't Have (MVP) |

> **Removed from v1.0:** "Receive an email confirmation" remains out of scope.

---

## 3. Functional Requirements

### 3.1 Landing Page (`/`)
- **FR-01:** Display welcome message branded to "Honolulu Hotels" (no longer single-hotel branding).
- **FR-02:** Show full-bleed Hawaii hero image.
- **FR-03:** Provide a prominent "Browse Hotels" call to action that links to `/hotels`.
- **FR-04:** Support GET only.

### 3.2 Hotel Menu Page (`/hotels`) — **NEW**
- **FR-05:** Display a grid (or card list) of curated Honolulu hotels. Each card shows:
  - Hero image of the hotel
  - Hotel name
  - Short tagline / description (1–2 sentences)
  - Neighborhood / location (e.g., "Waikiki Beach")
  - Starting nightly rate (lowest room rate at that hotel)
  - "Choose this hotel" button that links to `/rooms/<hotel_slug>`
- **FR-06:** The hotel list is sourced from a single `HOTELS` dict in `app.py`. Adding/removing hotels is a data-only change.
- **FR-07:** Initial curated hotel set (subject to discussion):
  - Hale Koa Hotel — Waikiki (military resort)
  - Hilton Hawaiian Village Waikiki Beach Resort — Waikiki
  - The Royal Hawaiian — Waikiki
  - Moana Surfrider, A Westin Resort & Spa — Waikiki
  - Sheraton Waikiki — Waikiki

### 3.3 Room Selection Page (`/rooms/<hotel_slug>`) — **CHANGED**
- **FR-08:** Show the hotel's banner / hero image and name at the top of the page.
- **FR-09:** Display the room types available **at the chosen hotel**, each with an image and nightly rate. Room inventory is per-hotel (each hotel defines its own rooms in the `HOTELS` dict).
- **FR-10:** If `<hotel_slug>` is unknown, render a friendly "hotel not found" page with a link back to `/hotels`.
- **FR-11:** Provide booking form with the following fields:

  | Field | Type | Required | Validation |
  |-------|------|----------|------------|
  | Name | Text | Yes | Non-empty |
  | Travel Start Date | Date | Yes | Valid date |
  | Ticket Price | Number | Yes | Positive integer |
  | Room Type | Dropdown | Yes | Valid selection from this hotel's rooms |
  | Number of Nights | Number | Yes | Positive integer |
  | Activities | Checkboxes | No | Multiple selection |
  | Travel Style | Radio | No | Single selection |
  | Comments | Textarea | No | 500 char max |

  > **Hidden field:** the form also POSTs the `hotel_slug` so `/trip_summary` knows which hotel the booking belongs to.

- **FR-12:** Available activities are shared across hotels (Honolulu-wide). Pricing:
  - Surfing ($125)
  - Hiking ($75)
  - Snorkeling ($149)
  - Attend a Luau ($130)

- **FR-13:** Form submits via standard HTML POST to `/trip_summary`. No JavaScript interception, no third-party SDKs.

### 3.4 Trip Summary Page (`/trip_summary`) — **CHANGED**
- **FR-14:** Display personalized trip summary with traveler name and **hotel name**.
- **FR-15:** Display the chosen room's image and nightly price prominently near the top of the summary (image card with price label), with the hotel name shown above the room name.
- **FR-16:** Calculate and display:
  - Hotel name and location
  - Travel date range (start date + number of nights)
  - Room type and nightly rate
  - Ticket price
  - Selected activities and their costs
  - Total cost of stay (nights × room rate)
  - Subtotal (stay + tickets + activities)
  - Tax (10.25% of subtotal)
  - Grand total
- **FR-17:** Format all currency values with comma separators and 2 decimal places.
- **FR-18:** Provide navigation link back to `/hotels` (to try another property) and back to `/`.

### 3.5 Removed: Email Integration
Still removed. No EmailJS, no Flask-Mail, no SMTP configuration, no email-related template variables.

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

### 4.2 Application Architecture

```
m8/
├── app.py                 # Main Flask application
├── design_doc.md          # Project 4 design doc
├── DESIGN.md              # Creative / visual design vision
├── PRD.md                 # This document
├── README.md              # Run/build instructions
├── static/                # Static assets
│   ├── hotels/            # Hotel hero images
│   │   ├── hale-koa.jpg
│   │   ├── hilton-hawaiian-village.jpg
│   │   ├── royal-hawaiian.jpg
│   │   ├── moana-surfrider.jpg
│   │   └── sheraton-waikiki.jpg
│   ├── rooms/             # Per-hotel room images (filenames namespaced by hotel)
│   │   ├── hale-koa/
│   │   ├── hilton-hawaiian-village/
│   │   └── ...
│   └── shared/            # Landing hero, activity icons, fallback image
└── templates/
    ├── index.html         # Landing page
    ├── hotels.html        # Hotel menu (NEW)
    ├── rooms.html         # Room selection & booking form (per hotel)
    ├── trip_summary.html  # Trip cost calculation + chosen-hotel/room display
    └── not_found.html     # Friendly "hotel not found" page
```

> Filenames are illustrative; existing flat `static/*.png` files can be kept for the initial pass and migrated to the namespaced layout when convenient.

### 4.3 Route Specifications

| Route | Method(s) | Handler | Template | Description |
|-------|-----------|---------|----------|-------------|
| `/` | GET | `home_page()` | `index.html` | Landing page |
| `/hotels` | GET | `hotels_menu()` | `hotels.html` | Curated Honolulu hotel menu |
| `/rooms/<hotel_slug>` | GET | `rooms(hotel_slug)` | `rooms.html` | Room selection for one hotel |
| `/trip_summary` | POST | `trip_summary()` | `trip_summary.html` | Cost calculation |

### 4.4 Data Model

```python
HOTELS = {
    "hale-koa": {
        "name": "Hale Koa Hotel",
        "tagline": "An armed-forces resort on Waikiki Beach.",
        "location": "Waikiki",
        "hero_image": "hotels/hale-koa.jpg",
        "rooms": {
            "Deluxe Ocean Front": {"price": 395, "image": "rooms/hale-koa/deluxe.png"},
            "Ilima Ocean West":   {"price": 345, "image": "rooms/hale-koa/ilima.png"},
            "Ocean View":         {"price": 295, "image": "rooms/hale-koa/ocean-view.png"},
            "Partial Ocean View": {"price": 219, "image": "rooms/hale-koa/partial-ocean-view.png"},
            "Resort View":        {"price": 189, "image": "rooms/hale-koa/resort-view.png"},
        },
    },
    "hilton-hawaiian-village": { ... },
    "royal-hawaiian":          { ... },
    "moana-surfrider":         { ... },
    "sheraton-waikiki":        { ... },
}
```

- `hotel_slug` is the URL-safe key (kebab-case).
- Per-hotel rooms keep the existing `{price, image}` shape, so `get_room_image()` and `parse_room_selection()` continue to work with a tiny modification (they take a `hotel_slug` parameter now).
- Starting-from price for a hotel card is `min(room["price"] for room in hotel["rooms"].values())`.

### 4.5 Data Flow

```
User visits /
       │
       ▼
Clicks "Browse Hotels" → /hotels
       │
       ▼
Sees hotel cards; clicks "Choose this hotel" → /rooms/<hotel_slug>
       │
       ▼
Sees that hotel's rooms; fills booking form
       │  (form includes hidden hotel_slug)
       ▼
Form POSTs to /trip_summary
       │
       ▼
Flask:
  • Looks up hotel by slug
  • Parses room name/price + image filename
  • Parses activities, sums costs
  • Computes date range
  • Computes stay, subtotal, tax (10.25%), grand total
       │
       ▼
trip_summary.html renders:
  • Hotel name + chosen room image + nightly price card
  • Itemized breakdown
```

### 4.6 Calculation Logic
Unchanged from v2.0.

```python
cost_of_stay = num_nights * room_price
end_date = start_date + timedelta(days=num_nights)
activity_cost = sum(cost for name, cost in selected_activities)
sub_total = cost_of_stay + ticket_price + activity_cost
tax = round(sub_total * 0.1025, 2)
total = sub_total + tax
```

---

## 5. User Interface Requirements

The detailed creative vision lives in `DESIGN.md`. This section captures only the functional UI requirements; visual treatment is owned by the design doc.

### 5.1 Landing Page
- Full-bleed hero image of Honolulu / Waikiki.
- Clear hotel-app branding ("Honolulu Hotels").
- One primary call-to-action: "Browse Hotels" → `/hotels`.

### 5.2 Hotel Menu Page
- Responsive grid of hotel cards (one per hotel in `HOTELS`).
- Each card: hero image, name, tagline, neighborhood, "from $X/night", action button.
- Cards visually distinguishable on hover/focus (lift + subtle shadow).

### 5.3 Room Selection Page
- Hotel banner (hero image + name + tagline) at the top.
- Room gallery showing only that hotel's rooms.
- Booking form below or beside the gallery.
- A "← Back to all hotels" link.

### 5.4 Trip Summary Page
- Chosen-hotel + chosen-room card at the top: hotel name, room name, room image, nightly price.
- Itemized cost breakdown.
- Bold grand total.
- Return links: `/hotels` (book another) and `/` (home).

---

## 6. Hotel & Room Inventory

The hotel set is curated and configurable in `HOTELS`. Initial set:

| Hotel | Slug | Location |
|-------|------|----------|
| Hale Koa Hotel | `hale-koa` | Waikiki |
| Hilton Hawaiian Village Waikiki Beach Resort | `hilton-hawaiian-village` | Waikiki |
| The Royal Hawaiian | `royal-hawaiian` | Waikiki |
| Moana Surfrider, A Westin Resort & Spa | `moana-surfrider` | Waikiki |
| Sheraton Waikiki | `sheraton-waikiki` | Waikiki |

Room inventory for Hale Koa is carried over from v2.0. Room inventories for the other four hotels are TBD (placeholder rooms + prices for the initial pass; refine once we have art).

`get_room_image(hotel_slug, room_name)` returns the per-hotel image filename, falling back to `shared/halekoa_Hotel.webp` if either the hotel or room name is unknown.

---

## 7. Activity Catalog

Unchanged. Activities are Honolulu-wide and not tied to a specific hotel.

| Activity | Price | Value String |
|----------|-------|--------------|
| Surfing | $125 | `surfing|125` |
| Hiking | $75 | `hiking|75` |
| Snorkeling | $149 | `snorkeling|149` |
| Attend a Luau | $130 | `luau|130` |

---

## 8. Testing Scenarios

### 8.1 Basic Flow Test
1. Navigate to `/`.
2. Click "Browse Hotels" → `/hotels`.
3. See the five hotel cards.
4. Click "Choose this hotel" on the Hale Koa card → `/rooms/hale-koa`.
5. Fill form with valid data:
   - Name: "Test User"
   - Date: tomorrow
   - Ticket Price: 500
   - Room: Deluxe Ocean Front
   - Nights: 3
   - Activities: Surfing, Luau
6. Submit form.
7. Verify trip summary shows:
   - "Hale Koa Hotel" as the hotel
   - Chosen-room image at top with `$395.00/night` label
   - Dates: Start to Start+3 days
   - Stay cost: $1,185.00
   - Activity cost: $255.00
   - Subtotal: $1,940.00
   - Tax: $198.85
   - Total: $2,138.85

### 8.2 Edge Cases

| Test | Input | Expected Result |
|------|-------|-----------------|
| Unknown hotel slug | `/rooms/foo` | Friendly "hotel not found" page with link back to `/hotels` |
| No activities | Leave all unchecked | Activities: "None", Cost: $0 |
| Single night | nights = 1 | Stay cost = room rate |
| All activities | Select all 4 | Activity cost = $479 |
| Tampered room dropdown value | Submit `Rooms=Foo|100` for a real hotel | Fallback image used; price honored as 100 (documented) |
| GET on `/trip_summary` | Direct URL | 405 Method Not Allowed (or graceful redirect to `/`) |

---

## 9. Known Limitations & Future Enhancements

### 9.1 Current Limitations
1. Hotel and room images for the new hotels are placeholders until real art is added.
2. No server-side input validation beyond `int()`/`float()` parsing.
3. No user authentication or session management.
4. No database persistence (data lost on refresh).
5. No confirmation/receipt mechanism (email removed; nothing replaces it yet).
6. Travel style radio buttons not used in calculations.
7. Comments field collected but not displayed in summary.

### 9.2 Planned Enhancements

#### Phase 2 (this iteration)
- [ ] Add `HOTELS` data structure and `/hotels`, `/rooms/<hotel_slug>` routes.
- [ ] Build the hotel menu template and reskin the room page per hotel.
- [ ] Implement the creative visual direction described in `DESIGN.md`.

#### Phase 3
- [ ] Real photography / licensed imagery for each hotel.
- [ ] Filter / sort the hotel menu (by neighborhood, by starting price).
- [ ] Surface comments and travel style on the summary.
- [ ] Server-side validation with friendly error pages.

#### Phase 4
- [ ] Database storage (SQLite).
- [ ] Booking confirmation numbers.
- [ ] Printable / shareable summary view.
- [ ] Responsive mobile layout pass.
- [ ] Accessibility pass (alt text, ARIA, focus states).

---

## 10. Glossary

| Term | Definition |
|------|------------|
| **Flask** | Python micro web framework |
| **Jinja2** | Template engine used by Flask |
| **Hotel slug** | URL-safe kebab-case identifier for a hotel (e.g., `hale-koa`) |
| **Hale Koa** | Military resort hotel in Waikiki, Hawaii |
| **MVP** | Minimum Viable Product |
| **PRD** | Product Requirements Document |

---

## 11. Appendix

### A. Sample Form Data Structure

```python
# Request form data received at /trip_summary
{
    "hotel_slug": "hale-koa",
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

### B. Rendered Template Variables

```python
# Variables passed to trip_summary.html
{
    "traveler_name": "John Doe",
    "hotel_name": "Hale Koa Hotel",
    "hotel_location": "Waikiki",
    "type": "Deluxe Ocean Front",
    "room_image": "rooms/hale-koa/deluxe.png",
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
