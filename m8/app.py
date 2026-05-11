"""
Aloha Escapes — Honolulu Hotels Booking System (m8)
Author: Richard Comins

Flask web app for planning a Honolulu hotel stay and seeing an
itemized cost breakdown. v4: full re-skin to the "Aloha Escapes"
design language defined in wireframes/.../DESIGN.md (Playfair Display +
Plus Jakarta Sans, Sandy Neutral background, Sunset Orange CTAs,
glassmorphic accents).

The Python side is largely unchanged from v3 — what's new here is
that each hotel now carries the extra fields needed to fill the
wireframe layout: description, amenities, rating, review_count, tags.
"""

from datetime import datetime, timedelta
from flask import Flask, render_template, request

app = Flask(__name__)

# Brand name used across the templates.  Centralized so we can rebrand
# in one place without touching every page.
BRAND = "Aloha Escapes"

# -----------------------------------------------------------------------------
# Image credits.  All non-Hale-Koa photography in /static comes from
# Wikimedia Commons under Creative Commons or Public Domain licenses.
# Attribution is preserved here per the license terms.
#
#   hilton-hero.jpg ............ "Hilton Hawaiian Village Panorama" — Don Ramey Logan — CC BY-SA 3.0
#   hilton-room-view.jpg ....... "Room with a view" — Janine (Mililani, HI) — CC BY 2.0
#   hilton-balcony.jpg ......... "Oceanview balcony" — Janine — CC BY 2.0
#   hilton-lagoon.jpg .......... "Hilton Lagoon" — hh oldman — CC BY 3.0
#   hilton-pool.jpg ............ "Hilton pool" — Janine — CC BY 2.0
#
#   royal-hawaiian-hero.jpg .... "The Royal Hawaiian (2024)" — Frank Schulenburg — CC BY-SA 4.0
#   royal-garden-courtyard.jpg . "Garden Courtyard, Royal Hawaiian Hotel" — Warren LeMay — CC BY-SA 2.0
#   royal-courtyard.jpg ........ "Courtyard, Royal Hawaiian Hotel" — Warren LeMay — CC BY-SA 2.0
#   royal-pool.jpg ............. "Malulani Pool at the Royal Hawaiian Hotel" — Frank Schulenburg — CC BY-SA 4.0
#
#   moana-hero.jpg ............. "Moana Surfrider, A Westin Resort & Spa, Waikiki Beach" — Peaceray — CC BY-SA 3.0
#   moana-lobby.jpg ............ "Lobby, Moana Hotel" — Warren LeMay — CC BY-SA 2.0
#   moana-staircase.jpg ........ "Grand Staircase, Moana Hotel" — Warren LeMay — CC BY-SA 2.0
#   moana-porte-cochere.jpg .... "Moana-Hotel-porte-cochere" — Joel Bradshaw — Public Domain
#
#   sheraton-hero.jpg .......... "Sheraton Waikiki from Waikiki Beach" — Coolcaesar — CC BY 4.0
#   sheraton-diamondhead.jpg ... "Sheraton-waikiki-diamondheadview" (Diamond Head View From Kai Ocean Suite) — moore — CC BY-SA 3.0
#   sheraton-sunrise.jpg ....... "Sunrise at Waikiki Beach, 2002" — Antonio Salsedo — CC BY 3.0
#   sheraton-dusk.jpg .......... "Waikiki at dusk" — MNKFotos (Maxim Kutsenko) — CC BY-SA 3.0
#
# Source: https://commons.wikimedia.org/
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# HOTELS: single source of truth for the curated Honolulu hotel menu.
#
# Each hotel record carries:
#   - name           display name shown on cards and detail page
#   - tagline        one-line hook used on the hotel menu cards
#   - description    longer copy that fills the "About this sanctuary" block
#   - location       city/neighborhood label (e.g., "Waikiki, Honolulu")
#   - rating         float 0-5 shown next to the star icon on the detail page
#   - review_count   int shown after the rating (purely decorative for now)
#   - tags           short labels rendered as pill chips on the detail page
#   - amenities      list of (material_symbol, label) tuples for the amenity grid
#   - hero_image     filename in /static — used for the hotel banner + bento
#   - rooms          per-hotel room inventory; same {price, image} shape as v3
#
# Tags / amenities / ratings are illustrative placeholders so the design
# system has real content to render.  Real review/amenity data would
# eventually replace these.
# -----------------------------------------------------------------------------
HOTELS = {
    "hale-koa": {
        "name": "Hale Koa Hotel",
        "tagline": "An armed-forces resort set on 72 oceanfront acres of Waikiki.",
        "description": (
            "Reserved exclusively for the U.S. armed forces community, the Hale Koa is a quiet, "
            "uncrowded 72-acre oceanfront resort tucked between Fort DeRussy Park and the surf "
            "of Waikiki Beach. Designed around generous lawns and palm-shaded pools, the property "
            "offers a calm, family-friendly counterpoint to the busier corner of Kalakaua Avenue."
        ),
        "location": "Waikiki, Honolulu",
        "rating": 4.7,
        "review_count": 142,
        "tags": ["Oceanfront Property", "Family Friendly", "Military Resort"],
        "amenities": [
            ("pool", "Two Oceanfront Pools"),
            ("restaurant", "Five On-Site Restaurants"),
            ("fitness_center", "Fitness Center"),
            ("local_parking", "Resort Parking"),
            ("wifi", "Complimentary Wi-Fi"),
            ("beach_access", "Private Beach Access"),
        ],
        "hero_image": "halekoa_Hotel.webp",
        "rooms": {
            "Deluxe Ocean Front":  {"price": 395, "image": "deluxe.png"},
            "Ilima Ocean West":    {"price": 345, "image": "ilima.png"},
            "Ocean View":          {"price": 295, "image": "ocean-view-room.png"},
            "Partial Ocean View":  {"price": 219, "image": "partial-ocean-view-room.png"},
            "Resort View":         {"price": 189, "image": "resort-view.png"},
        },
    },
    "hilton-hawaiian-village": {
        "name": "Hilton Hawaiian Village Waikiki Beach Resort",
        "tagline": "A 22-acre village with five pools and its own saltwater lagoon.",
        "description": (
            "A self-contained beachfront village on the quieter Diamond Head end of Waikiki, "
            "the Hilton Hawaiian Village spreads across 22 oceanfront acres of pools, gardens, "
            "and the property's own saltwater lagoon. The signature Friday-night fireworks light "
            "up the sand each week, and the property's five towers offer everything from "
            "lagoon-view value rooms to oceanfront suites."
        ),
        "location": "Waikiki, Honolulu",
        "rating": 4.5,
        "review_count": 318,
        "tags": ["Oceanfront", "Family Friendly", "Five Towers"],
        "amenities": [
            ("pool", "Five Resort Pools"),
            ("water", "Private Lagoon"),
            ("restaurant", "20+ Dining Options"),
            ("spa", "Mandara Spa"),
            ("fitness_center", "Fitness Center"),
            ("wifi", "Premium Wi-Fi"),
        ],
        "hero_image": "hilton-hero.jpg",
        "rooms": {
            "Rainbow Tower Ocean Front": {"price": 549, "image": "hilton-room-view.jpg"},
            "Ali'i Tower Ocean View":    {"price": 489, "image": "hilton-balcony.jpg"},
            "Tapa Tower Partial Ocean":  {"price": 329, "image": "hilton-lagoon.jpg"},
            "Lagoon Tower Resort View":  {"price": 259, "image": "hilton-pool.jpg"},
        },
    },
    "royal-hawaiian": {
        "name": "The Royal Hawaiian",
        "tagline": "The Pink Palace of the Pacific, on Waikiki since 1927.",
        "description": (
            "Affectionately known as the Pink Palace of the Pacific, The Royal Hawaiian has anchored "
            "the heart of Waikiki since 1927. Coral-pink Spanish-Moorish architecture, towering "
            "monkeypod trees, and a beachfront garden lawn give the property a sense of place that "
            "few resorts in the world can match. Inside, a careful restoration keeps the historic "
            "wing genuinely historic while the Mailani Tower offers a contemporary oceanfront stay."
        ),
        "location": "Waikiki, Honolulu",
        "rating": 4.8,
        "review_count": 521,
        "tags": ["Historic Landmark", "Beachfront", "Luxury Heritage"],
        "amenities": [
            ("pool", "Heated Pool"),
            ("spa", "Abhasa Waikiki Spa"),
            ("restaurant", "Surf Lanai Dining"),
            ("local_bar", "Mai Tai Bar"),
            ("wifi", "Premium Wi-Fi"),
            ("beach_access", "Private Beach Cabanas"),
        ],
        "hero_image": "royal-hawaiian-hero.jpg",
        "rooms": {
            "Historic Tower Suite":     {"price": 829, "image": "royal-garden-courtyard.jpg"},
            "Mailani Tower Ocean View": {"price": 649, "image": "royal-courtyard.jpg"},
            "Garden View Room":         {"price": 459, "image": "royal-pool.jpg"},
        },
    },
    "moana-surfrider": {
        "name": "Moana Surfrider, A Westin Resort & Spa",
        "tagline": "The First Lady of Waikiki, welcoming guests since 1901.",
        "description": (
            "The First Lady of Waikiki, the Moana Surfrider opened in 1901 and remains a study in "
            "white-columned, plantation-style hospitality. The 100-year-old banyan tree that shades "
            "the central courtyard is the heart of the property, and afternoon tea on the veranda is "
            "still a daily ritual. A blend of original Beaux-Arts heritage and quiet modern luxury."
        ),
        "location": "Waikiki, Honolulu",
        "rating": 4.6,
        "review_count": 287,
        "tags": ["Historic Landmark", "Beachfront", "Westin Heavenly Bed"],
        "amenities": [
            ("pool", "Beachfront Pool"),
            ("spa", "Moana Lani Spa"),
            ("restaurant", "Beachhouse at the Moana"),
            ("local_cafe", "Veranda Afternoon Tea"),
            ("fitness_center", "Westin Workout"),
            ("wifi", "Complimentary Wi-Fi"),
        ],
        "hero_image": "moana-hero.jpg",
        "rooms": {
            "Banyan Suite Ocean Front":  {"price": 729, "image": "moana-lobby.jpg"},
            "Diamond Wing Ocean View":   {"price": 549, "image": "moana-staircase.jpg"},
            "Tower Wing City View":      {"price": 379, "image": "moana-porte-cochere.jpg"},
        },
    },
    "sheraton-waikiki": {
        "name": "Sheraton Waikiki",
        "tagline": "Twin towers stepping straight onto the sand of Waikiki Beach.",
        "description": (
            "The Sheraton Waikiki's twin towers step almost directly onto the sand, putting nearly "
            "every guest within view of Diamond Head and the rolling break of Waikiki Beach. The "
            "property is built for those who want easy access to the surf without sacrificing the "
            "amenities of a full resort, including the famous infinity edge pool overlooking the ocean."
        ),
        "location": "Waikiki, Honolulu",
        "rating": 4.4,
        "review_count": 412,
        "tags": ["Oceanfront", "Infinity Pool", "Family Friendly"],
        "amenities": [
            ("pool", "Infinity Edge Pool"),
            ("spa", "SpaHalekulani"),
            ("restaurant", "Kai Market"),
            ("fitness_center", "Sheraton Fitness"),
            ("wifi", "Premium Wi-Fi"),
            ("beach_access", "Direct Beach Access"),
        ],
        "hero_image": "sheraton-hero.jpg",
        "rooms": {
            "Leahi Club Ocean Front": {"price": 599, "image": "sheraton-diamondhead.jpg"},
            "Deluxe Ocean View":      {"price": 449, "image": "sheraton-sunrise.jpg"},
            "Resort View Room":       {"price": 269, "image": "sheraton-dusk.jpg"},
        },
    },
}

# Used when a slug or room name lookup fails.  Falls back to the
# generic property shot so the page still renders.
FALLBACK_IMAGE = "halekoa_Hotel.webp"

# Hawaii combined transient accommodation / GE tax used in the cost summary.
TAX_RATE = 0.1025

# Activity catalog.  Same in every hotel — these are Honolulu-wide
# experiences, not tied to a specific property.  Each tuple is:
#   (form-value key, display label, price in USD)
ACTIVITIES = [
    ("surfing",    "Surfing",        125),
    ("hiking",     "Hiking",          75),
    ("snorkeling", "Snorkeling",     149),
    ("luau",       "Attend a Luau",  130),
]


# -----------------------------------------------------------------------------
# Lookup + parsing helpers.  Pure functions, no Flask state — easy to
# read and easy to unit test if we ever add tests.
# -----------------------------------------------------------------------------
def get_hotel(hotel_slug: str):
    """Return the hotel record for `hotel_slug`, or None if unknown."""
    return HOTELS.get(hotel_slug)


def starting_price(hotel: dict) -> int:
    """Lowest nightly rate offered at a hotel.  Used on the menu cards."""
    return min(room["price"] for room in hotel["rooms"].values())


def get_room_image(hotel_slug: str, room_name: str) -> str:
    """Per-hotel room image filename, with safe fallbacks."""
    hotel = HOTELS.get(hotel_slug)
    if not hotel:
        return FALLBACK_IMAGE
    room = hotel["rooms"].get(room_name)
    return room["image"] if room else hotel.get("hero_image", FALLBACK_IMAGE)


def bento_images(hotel: dict, max_extra: int = 3):
    """
    Return up to (1 hero + max_extra room) image filenames for the bento
    gallery on the hotel detail page.  The hero is always first so the
    template can place it as the big tile on the left.
    """
    images = [hotel["hero_image"]]
    for room in hotel["rooms"].values():
        if len(images) >= 1 + max_extra:
            break
        images.append(room["image"])
    return images


def parse_room_selection(raw: str):
    """Split the form value `Name|price` back into a (name, float) pair."""
    name, price_str = raw.split("|")
    return name, round(float(price_str), 2)


def parse_activities(raw_list):
    """Sum activity costs and join their names into a label for display."""
    names = []
    total = 0
    for item in raw_list:
        name, cost = item.split("|")
        names.append(name)
        total += int(cost)
    label = ", ".join(names) if names else "None"
    return label, total


def compute_dates(start_date_str: str, num_nights: int) -> str:
    """Build the 'YYYY-MM-DD to YYYY-MM-DD' range string for the summary."""
    end_date = datetime.strptime(start_date_str, "%Y-%m-%d") + timedelta(days=num_nights)
    return f"{start_date_str} to {end_date.strftime('%Y-%m-%d')}"


def compute_totals(cost_of_stay: float, ticket_price: int, activity_cost: int):
    """Return (subtotal, tax, grand_total) for the trip-summary breakdown."""
    sub_total = round(cost_of_stay + ticket_price + activity_cost, 2)
    tax = round(sub_total * TAX_RATE, 2)
    total = round(sub_total + tax, 2)
    return sub_total, tax, total


# -----------------------------------------------------------------------------
# Routes
# -----------------------------------------------------------------------------

@app.route("/")
def home_page():
    """Landing page — the editorial hero with the glass CTA panel."""
    return render_template("index.html", brand=BRAND)


@app.route("/hotels")
def hotels_menu():
    """Curated hotel menu — each card links to /rooms/<slug>."""
    # Project the HOTELS dict down to the small set of fields each
    # card actually needs.  This keeps the template simple.
    cards = []
    for slug, hotel in HOTELS.items():
        cards.append({
            "slug": slug,
            "name": hotel["name"],
            "tagline": hotel["tagline"],
            "location": hotel["location"],
            "hero_image": hotel["hero_image"],
            "tags": hotel["tags"],
            "rating": hotel["rating"],
            "starting_price": starting_price(hotel),
        })
    return render_template("hotels.html", brand=BRAND, hotels=cards)


@app.route("/rooms/<hotel_slug>")
def rooms(hotel_slug):
    """Hotel detail page with bento gallery, about, amenities, and booking form."""
    hotel = get_hotel(hotel_slug)
    if not hotel:
        # Unknown slug → quiet 404 page rather than a stack trace.
        return render_template("not_found.html", brand=BRAND), 404

    return render_template(
        "rooms.html",
        brand=BRAND,
        hotel_slug=hotel_slug,
        hotel=hotel,
        activities=ACTIVITIES,
        starting_price=starting_price(hotel),
        gallery=bento_images(hotel),
    )


@app.route("/trip_summary", methods=["POST"])
def trip_summary():
    """Cost calculation + summary render.  Reads the hidden hotel_slug
    field from the booking form so we know which hotel the booking is for."""
    hotel_slug = request.form.get("hotel_slug", "")
    hotel = get_hotel(hotel_slug)
    if not hotel:
        return render_template("not_found.html", brand=BRAND), 404

    # Form value for `Rooms` is shaped as "Display Name|price" so we
    # can recover both pieces with a single split.
    room_name, room_price = parse_room_selection(request.form.get("Rooms"))
    room_image = get_room_image(hotel_slug, room_name)

    traveler_name = request.form.get("name")
    ticket_price = int(request.form.get("ticketPrice"))
    num_nights = int(request.form.get("num_nights"))

    activity_label, activity_cost = parse_activities(request.form.getlist("activity"))

    dates = compute_dates(request.form.get("dates"), num_nights)

    cost_of_stay = round(num_nights * room_price, 2)
    sub_total, tax, total = compute_totals(cost_of_stay, ticket_price, activity_cost)

    return render_template(
        "trip_summary.html",
        brand=BRAND,
        traveler_name=traveler_name,
        hotel_name=hotel["name"],
        hotel_location=hotel["location"],
        type=room_name,
        room_image=room_image,
        cost=room_price,
        dates=dates,
        num_nights=num_nights,
        cost_of_stay=cost_of_stay,
        ticket_price=ticket_price,
        activity=activity_label,
        activityCost=activity_cost,
        sub_total=sub_total,
        tax=tax,
        total=total,
    )


if __name__ == "__main__":
    app.run(debug=True)
