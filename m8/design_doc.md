# Design Document — Project 4

**Name:** Richard Comins
**Track:** C (Direct to Visual — Flask + HTML/Jinja2)
**Project Title:** Honolulu Hotels Booking System (m8)
**One-sentence pitch:** A Flask web app where a user browses a curated menu of Honolulu hotels, picks a room and dates, and gets back an itemized trip summary with the chosen hotel name, the room's image, and the nightly price.

---

## 1. The Problem

A traveler wants to plan a stay in Honolulu and compare a few hotels before committing. The app shows a curated menu of Honolulu hotels (Hale Koa, Hilton Hawaiian Village, The Royal Hawaiian, Moana Surfrider, Sheraton Waikiki). The user picks one hotel, picks a room and dates at that property, optionally adds activities, and sees a clean summary that includes the hotel name, the selected room's image, nightly rate, and a full price breakdown with tax. It is a planning/cost-calculator tool, not a real reservation system.

This version of the project removes the email-confirmation feature from the original prototype. The summary lives entirely on the trip-summary page; nothing is sent off the server.

The creative direction (color palette, typography, layout system, photographic style) is captured separately in `DESIGN.md`. This document focuses on the data and behavior.

---

## 2. State Inventory

| Data | Type | What Changes It |
|---|---|---|
| Selected hotel | string (`hotel_slug`) | User clicking a hotel card on `/hotels` |
| Hotel name / location / hero image / rooms | derived | Looked up from the `HOTELS` dict by `hotel_slug` |
| Traveler name | string | User typing in the Name field |
| Travel start date | date (YYYY-MM-DD) | User picking a date |
| Number of nights | int | User entering nights |
| Ticket (airfare) price | int (USD) | User entering ticket price |
| Selected room | string + int (name, nightly price) | User picking a `<select>` option (value `Name|price`) |
| Selected room image | string (filename) | Derived from selected hotel + room via `HOTELS` lookup |
| Selected activities | list of (name, cost) pairs | User toggling checkboxes |
| Travel style | string ("luxury" \| "budget" \| "adventure" \| none) | User picking a radio option |
| Comments | string (≤ 500 chars) | User typing in the comments textarea |
| Cost of stay | float | Derived: `nights × nightly_price` |
| Activity cost | int | Derived: sum of selected activity costs |
| Subtotal | float | Derived: `stay + ticket + activities` |
| Tax | float | Derived: `subtotal × 0.1025` |
| Grand total | float | Derived: `subtotal + tax` |
| Date range string | string | Derived: `start_date` to `start_date + nights` |

State only lives for the duration of one request/response. The selected hotel is carried between `/rooms/<hotel_slug>` and `/trip_summary` via a hidden form field. There is no DB and no session — refreshing the trip summary page loses the data, which is fine for an MVP cost calculator.

---

## 3. Function / Component Map

| Function or Component | What It Does | Inputs | Outputs |
|---|---|---|---|
| `home_page()` (route `/`) | Renders the landing page with a "Browse Hotels" CTA to `/hotels` | none | rendered `index.html` |
| `hotels_menu()` (route `/hotels`) | Renders the curated hotel menu with starting-from prices | none | rendered `hotels.html` |
| `rooms(hotel_slug)` (route `/rooms/<hotel_slug>`) | Looks up the hotel, renders its banner + room gallery + booking form. 404-style page if slug unknown | URL slug | rendered `rooms.html` |
| `trip_summary()` (route `/trip_summary`, POST) | Parses the form (including hidden `hotel_slug`), looks up the hotel, computes costs, renders the summary | `request.form` | rendered `trip_summary.html` |
| `get_room_image(hotel_slug, room_name)` | Looks up the per-hotel image filename for a chosen room; returns a fallback if not found | hotel slug, room display name | image filename |
| `parse_room_selection(raw)` | Splits the `Name\|price` form value into a name and float price | `Rooms` form field | `(name, price)` |
| `parse_activities(raw_list)` | Splits each `name\|cost` activity value, returns names list and total cost | list of strings | `(["surfing", ...], total_int)` |
| `compute_dates(start, nights)` | Builds the `YYYY-MM-DD to YYYY-MM-DD` range string | start string, int nights | string |
| `compute_totals(stay, ticket, activities)` | Computes subtotal, tax (10.25%), and grand total | three numbers | tuple of floats |
| `starting_price(hotel)` | Returns the minimum room price for a hotel (used on the menu cards) | hotel dict | int |
| `HOTELS` (constant dict) | Single source of truth: `{slug: {name, tagline, location, hero_image, rooms: {display_name: {price, image}}}}` | — | — |
| `ACTIVITIES` (constant list) | Catalog of activity name + cost used by the form | — | — |
| `index.html` template | Landing screen with "Browse Hotels" CTA | — | — |
| `hotels.html` template | Curated hotel menu cards (NEW) | — | — |
| `rooms.html` template | Hotel banner + room gallery + booking form (POSTs to `/trip_summary`) | — | — |
| `trip_summary.html` template | Renders hotel name + chosen room **image + nightly price**, dates, costs, tax, total | template vars | rendered HTML |
| `not_found.html` template | Friendly fallback when `hotel_slug` is unknown | — | — |

> The image-and-price display on the summary page is still the headline visual feature for this version. The hotel-menu page is the headline structural feature.

---

## 4. User Flow

**Main path:**

1. User visits `/` and sees the welcome page with a "Browse Hotels" CTA.
2. User clicks "Browse Hotels" and lands on `/hotels`. They see five hotel cards (Hale Koa, Hilton Hawaiian Village, Royal Hawaiian, Moana Surfrider, Sheraton Waikiki), each with image, tagline, location, starting nightly rate, and a "Choose this hotel" button.
3. User clicks a hotel card → `/rooms/<hotel_slug>`. They see that hotel's banner and that hotel's room gallery.
4. User fills out: name, start date, ticket price, room (dropdown of *this hotel's* rooms), nights, activities, travel style, comments. The form also carries a hidden `hotel_slug`.
5. User clicks Submit. The form POSTs directly to `/trip_summary`.
6. `trip_summary()` looks up the hotel, parses the form, computes stay/subtotal/tax/total, and renders the summary page.
7. User sees the hotel name and the chosen room's image with nightly price at the top of the summary, followed by the itemized breakdown.
8. User clicks "Book another hotel" (→ `/hotels`) or "Return to home" (→ `/`).

**Key branches:**

- If the user navigates to `/rooms/<unknown>` → render `not_found.html` with a link back to `/hotels`.
- If the user picks no activities → activity list shows "None" and activity cost is `$0`.
- If the room name is missing from the hotel's rooms dict → fall back to the generic hotel image.
- If a required field is missing → HTML5 `required` validation blocks submission in the browser.
- If the user navigates directly to `/trip_summary` with GET → 405 Method Not Allowed (acceptable for MVP).

---

## 5. What Could Go Wrong

| Risk | Plan |
|---|---|
| User enters non-numeric values for nights or ticket price | `type="number"` on inputs + server-side `int()` parse; on bad input show a friendly error page rather than a 500 |
| Room dropdown value missing the `\|` delimiter | Wrap the split in a try/except; fall back to a default room and image |
| Form posts a `hotel_slug` that isn't in `HOTELS` | Treat as the not-found case in `trip_summary()` too — render a friendly error |
| User picks a start date in the past | Allowed for MVP (it's a calculator, not a reservation) |
| Image file missing from `/static` | `get_room_image` returns the hotel fallback image |
| Tax rounding causes off-by-a-cent totals | Round subtotal and tax to 2 decimals before summing the grand total |
| User refreshes the summary page | Browser re-POST warning; acceptable since there is no persistence |
| Hotel inventory grows beyond what fits in one screen | Menu grid wraps; mobile layout stacks. Long-term, add filtering (see PRD §9.2 Phase 3) |

---

## 6. What I'll Ask AI to Help With

| Task | Why AI Help Makes Sense |
|---|---|
| Generating the initial `HOTELS` data shape with placeholder rooms for the four new hotels | Tedious to type; easy to mis-spell slugs / mismatch image paths |
| Refactoring `get_room_image` to take a hotel slug without breaking the existing tests/flow | Small but easy to typo in the lookup chain |
| Writing the hotel-card CSS so it reads like a real resort site (see `DESIGN.md`) | I know the look I want but the grid/flex syntax is fiddly |
| Reviewing the trip-summary template for accessibility (alt text, headings, landmarks) | I'm not strong on a11y; AI can flag obvious gaps |

---

## 7. What I'll Do Myself (No AI)

1. The route wiring and the `HOTELS` data structure — I want to own the source of truth.
2. The cost math (`compute_totals`, date range) — this is the core logic of the app and I want to be able to defend every number on screen.
3. Choosing which Honolulu hotels go in the curated set, and writing each tagline.

---

## 8. Scope Check

- Can I build the C-tier version in one focused work session? **yes** — the single-hotel app already runs; adding a menu + per-hotel rooms is a contained change to the data model and one new route.
- Does every feature in my plan connect to the core interaction (pick a trip → see the cost)? **yes** — the hotel menu is an extra step that makes the "pick" richer; it does not divert from the core flow.
- Have I cut anything that's "nice to have" but not essential? **yes** — email confirmation, hotel filtering, real photography, and persistence are all out of scope for this version.

---

## Instructor Approval

*To be filled out during Week 13 check-in:*

- [ ] Scope is appropriate
- [ ] State inventory is complete
- [ ] Function map shows clear decomposition
- [ ] Student knows what they'll ask AI for and what they'll do themselves

**Notes:**
