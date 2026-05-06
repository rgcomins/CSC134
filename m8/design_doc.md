# Design Document — Project 4

**Name:** Richard Comins
**Track:** C (Direct to Visual — Flask + HTML/Jinja2)
**Project Title:** Hale Koa Hotel Booking System (m8)
**One-sentence pitch:** A Flask web app where a user picks a Hale Koa room, dates, and activities and gets back an itemized trip summary with the chosen room's image and nightly price.

---

## 1. The Problem

A traveler wants to plan a stay at the Hale Koa Hotel and see the full cost of the trip before committing. The app lets the user enter their name, travel dates, ticket price, room choice, number of nights, and any add-on activities, then renders a clean summary that includes the selected room's image, nightly rate, and a full price breakdown with tax. It is a planning/cost-calculator tool, not a real reservation system.

This version of the project removes the email-confirmation feature from the original prototype. The summary lives entirely on the trip-summary page; nothing is sent off the server.

---

## 2. State Inventory

| Data | Type | What Changes It |
|---|---|---|
| Traveler name | string | User typing in the Name field |
| Travel start date | date (YYYY-MM-DD) | User picking a date |
| Number of nights | int | User entering nights |
| Ticket (airfare) price | int (USD) | User entering ticket price |
| Selected room | string + int (name, nightly price) | User picking a `<select>` option (value `Name|price`) |
| Selected room image | string (filename) | Derived from selected room via `ROOMS` lookup |
| Selected activities | list of (name, cost) pairs | User toggling checkboxes |
| Travel style | string ("luxury" \| "budget" \| "adventure" \| none) | User picking a radio option |
| Comments | string (≤ 500 chars) | User typing in the comments textarea |
| Cost of stay | float | Derived: `nights × nightly_price` |
| Activity cost | int | Derived: sum of selected activity costs |
| Subtotal | float | Derived: `stay + ticket + activities` |
| Tax | float | Derived: `subtotal × 0.1025` |
| Grand total | float | Derived: `subtotal + tax` |
| Date range string | string | Derived: `start_date` to `start_date + nights` |

State only lives for the duration of one request/response. There is no DB and no session — refreshing the trip summary page loses the data, which is fine for an MVP cost calculator.

---

## 3. Function / Component Map

| Function or Component | What It Does | Inputs | Outputs |
|---|---|---|---|
| `home_page()` (route `/`) | Renders the landing page with a link to `/rooms` | none | rendered `index.html` |
| `rooms()` (route `/rooms`) | Renders the room gallery + booking form | none | rendered `ROOMS.html` |
| `trip_summary()` (route `/trip_summary`, POST) | Parses the form, computes costs, renders the summary | `request.form` | rendered `trip_summary.html` |
| `get_room_image(room_name)` | Looks up the image filename for a chosen room; returns a fallback if not found | room display name | image filename |
| `parse_room_selection(raw)` | Splits the `Name\|price` form value into a name and float price | `Rooms` form field | `(name, price)` |
| `parse_activities(raw_list)` | Splits each `name\|cost` activity value, returns names list and total cost | list of strings | `(["surfing", ...], total_int)` |
| `compute_dates(start, nights)` | Builds the `YYYY-MM-DD to YYYY-MM-DD` range string | start string, int nights | string |
| `compute_totals(stay, ticket, activities)` | Computes subtotal, tax (10.25%), and grand total | three numbers | dict of floats |
| `ROOMS` (constant dict) | Single source of truth: `{display_name: {price, image}}` | — | — |
| `ACTIVITIES` (constant list) | Catalog of activity name + cost used by the form | — | — |
| `index.html` template | Welcome screen | — | — |
| `ROOMS.html` template | Room images + booking form (POSTs to `/trip_summary`) | — | — |
| `trip_summary.html` template | Renders chosen room **image + nightly price**, dates, costs, tax, total | template vars | rendered HTML |

> The image-and-price display on the summary page is the headline visual feature for this version.

---

## 4. User Flow

**Main path:**

1. User visits `/` and sees the welcome page with a "Rooms" link.
2. User clicks "Rooms" and lands on `/rooms`. They see images of the five rooms and a booking form.
3. User fills out: name, start date, ticket price, room (dropdown), nights, activities (checkboxes), travel style (radio), comments.
4. User clicks Submit. The form POSTs directly to `/trip_summary` (no client-side email step).
5. `trip_summary()` parses the form, looks up the room image, computes stay/subtotal/tax/total, and renders the summary page.
6. User sees the chosen room's image and nightly price at the top of the summary, followed by the itemized breakdown.
7. User clicks "Return to home page" to start over.

**Key branches:**

- If the user picks no activities → activity list shows "None" and activity cost is `$0`.
- If the room name is missing from the `ROOMS` lookup → fall back to the generic `halekoa_Hotel.webp` image.
- If a required field is missing → HTML5 `required` validation blocks submission in the browser.
- If the user navigates directly to `/trip_summary` with GET → page renders an empty/error-tolerant state (template variables guarded; or 405). For MVP, POST is the only supported method.

---

## 5. What Could Go Wrong

| Risk | Plan |
|---|---|
| User enters non-numeric values for nights or ticket price | `type="number"` on inputs + server-side `int()` parse; on bad input show a friendly error page rather than a 500 |
| Room dropdown value missing the `\|` delimiter | Wrap the split in a try/except; fall back to a default room and image |
| User picks a start date in the past | Allowed for MVP (it's a calculator, not a reservation); document this as accepted behavior |
| Image file missing from `/static` | `get_room_image` returns the hotel fallback image |
| Tax rounding causes off-by-a-cent totals | Round subtotal and tax to 2 decimals before summing the grand total |
| User refreshes the summary page | Browser re-POST warning; acceptable since there is no persistence |

---

## 6. What I'll Ask AI to Help With

| Task | Why AI Help Makes Sense |
|---|---|
| Stripping the EmailJS code out of `ROOMS.html` cleanly | The existing template intercepts submit for email — I want a clean diff that just lets the form POST normally |
| Writing `parse_activities` as a small pure function | I have the logic inline in `trip_summary()`; I want it factored out so it's testable |
| Reviewing the trip-summary template for accessibility (alt text, headings) | I'm not strong on a11y; AI can flag obvious gaps |
| Suggesting a CSS layout for "image + price" cards on the summary page | I know what I want visually but the flexbox/grid syntax is fiddly |

---

## 7. What I'll Do Myself (No AI)

1. The route wiring and the `ROOMS` data structure — I want to own the source of truth for room data.
2. The cost math (`compute_totals`, date range) — this is the core logic of the app and I want to be able to defend every number on screen.

---

## 8. Scope Check

- Can I build the C-tier version in one focused work session? **yes** — the prototype already runs; this version is a trim + a visual polish.
- Does every feature in my plan connect to the core interaction (pick a trip → see the cost)? **yes**
- Have I cut anything that's "nice to have" but not essential? **yes** — email confirmation is removed for this version.

---

## Instructor Approval

*To be filled out during Week 13 check-in:*

- [ ] Scope is appropriate
- [ ] State inventory is complete
- [ ] Function map shows clear decomposition
- [ ] Student knows what they'll ask AI for and what they'll do themselves

**Notes:**
