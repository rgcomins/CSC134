"""
Honolulu Hotels Booking System (m8)
Author: Richard Comins

Flask web app for planning a Honolulu hotel stay and seeing an
itemized cost breakdown. v3: user picks from a curated menu of
Waikiki hotels, then a room, then sees the chosen-room image +
nightly price on the trip summary.
"""

from datetime import datetime, timedelta
from flask import Flask, render_template, request

app = Flask(__name__)

# Curated Honolulu hotel menu. Single source of truth for the app.
# Room images for the non-Hale-Koa hotels reuse the existing room
# photos as placeholders until licensed art is available.
HOTELS = {
    "hale-koa": {
        "name": "Hale Koa Hotel",
        "tagline": "An armed-forces resort set on 72 oceanfront acres of Waikiki.",
        "location": "Waikiki",
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
        "location": "Waikiki",
        "hero_image": "rainbow_map.jpg",
        "rooms": {
            "Rainbow Tower Ocean Front": {"price": 549, "image": "deluxe.png"},
            "Ali'i Tower Ocean View":    {"price": 489, "image": "ilima.png"},
            "Tapa Tower Partial Ocean":  {"price": 329, "image": "ocean-view-room.png"},
            "Lagoon Tower Resort View":  {"price": 259, "image": "partial-ocean-view-room.png"},
        },
    },
    "royal-hawaiian": {
        "name": "The Royal Hawaiian",
        "tagline": "The Pink Palace of the Pacific, on Waikiki since 1927.",
        "location": "Waikiki",
        "hero_image": "rainbow_map.jpg",
        "rooms": {
            "Historic Tower Suite":     {"price": 829, "image": "deluxe.png"},
            "Mailani Tower Ocean View": {"price": 649, "image": "ilima.png"},
            "Garden View Room":         {"price": 459, "image": "resort-view.png"},
        },
    },
    "moana-surfrider": {
        "name": "Moana Surfrider, A Westin Resort & Spa",
        "tagline": "The First Lady of Waikiki, welcoming guests since 1901.",
        "location": "Waikiki",
        "hero_image": "rainbow_map.jpg",
        "rooms": {
            "Banyan Suite Ocean Front":  {"price": 729, "image": "deluxe.png"},
            "Diamond Wing Ocean View":   {"price": 549, "image": "ocean-view-room.png"},
            "Tower Wing City View":      {"price": 379, "image": "resort-view.png"},
        },
    },
    "sheraton-waikiki": {
        "name": "Sheraton Waikiki",
        "tagline": "Twin towers stepping straight onto the sand of Waikiki Beach.",
        "location": "Waikiki",
        "hero_image": "rainbow_map.jpg",
        "rooms": {
            "Leahi Club Ocean Front": {"price": 599, "image": "deluxe.png"},
            "Deluxe Ocean View":      {"price": 449, "image": "ocean-view-room.png"},
            "Resort View Room":       {"price": 269, "image": "resort-view.png"},
        },
    },
}

FALLBACK_IMAGE = "halekoa_Hotel.webp"
TAX_RATE = 0.1025

ACTIVITIES = [
    ("surfing",    "Surfing",        125),
    ("hiking",     "Hiking",          75),
    ("snorkeling", "Snorkeling",     149),
    ("luau",       "Attend a Luau",  130),
]


def get_hotel(hotel_slug: str):
    return HOTELS.get(hotel_slug)


def starting_price(hotel: dict) -> int:
    return min(room["price"] for room in hotel["rooms"].values())


def get_room_image(hotel_slug: str, room_name: str) -> str:
    hotel = HOTELS.get(hotel_slug)
    if not hotel:
        return FALLBACK_IMAGE
    room = hotel["rooms"].get(room_name)
    return room["image"] if room else hotel.get("hero_image", FALLBACK_IMAGE)


def parse_room_selection(raw: str):
    name, price_str = raw.split("|")
    return name, round(float(price_str), 2)


def parse_activities(raw_list):
    names = []
    total = 0
    for item in raw_list:
        name, cost = item.split("|")
        names.append(name)
        total += int(cost)
    label = ", ".join(names) if names else "None"
    return label, total


def compute_dates(start_date_str: str, num_nights: int) -> str:
    end_date = datetime.strptime(start_date_str, "%Y-%m-%d") + timedelta(days=num_nights)
    return f"{start_date_str} to {end_date.strftime('%Y-%m-%d')}"


def compute_totals(cost_of_stay: float, ticket_price: int, activity_cost: int):
    sub_total = round(cost_of_stay + ticket_price + activity_cost, 2)
    tax = round(sub_total * TAX_RATE, 2)
    total = round(sub_total + tax, 2)
    return sub_total, tax, total


@app.route("/")
def home_page():
    return render_template("index.html")


@app.route("/hotels")
def hotels_menu():
    cards = []
    for slug, hotel in HOTELS.items():
        cards.append({
            "slug": slug,
            "name": hotel["name"],
            "tagline": hotel["tagline"],
            "location": hotel["location"],
            "hero_image": hotel["hero_image"],
            "starting_price": starting_price(hotel),
        })
    return render_template("hotels.html", hotels=cards)


@app.route("/rooms/<hotel_slug>")
def rooms(hotel_slug):
    hotel = get_hotel(hotel_slug)
    if not hotel:
        return render_template("not_found.html"), 404
    return render_template(
        "rooms.html",
        hotel_slug=hotel_slug,
        hotel=hotel,
        activities=ACTIVITIES,
    )


@app.route("/trip_summary", methods=["POST"])
def trip_summary():
    hotel_slug = request.form.get("hotel_slug", "")
    hotel = get_hotel(hotel_slug)
    if not hotel:
        return render_template("not_found.html"), 404

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
