"""
Hale Koa Hotel Booking System (m8)
Author: Richard Comins

Flask web app for planning a Hale Koa stay and seeing an itemized
cost breakdown. v2: email confirmation removed; the chosen-room
image and nightly price are featured on the trip summary page.
"""

from datetime import datetime, timedelta
from flask import Flask, render_template, request

app = Flask(__name__)

# Single source of truth for room display name -> price + image filename.
ROOMS = {
    "Deluxe Ocean Front":  {"price": 395, "image": "deluxe.png"},
    "Ilima Ocean West":    {"price": 345, "image": "ilima.png"},
    "Ocean View":          {"price": 295, "image": "ocean-view-room.png"},
    "Partial Ocean View":  {"price": 219, "image": "partial-ocean-view-room.png"},
    "Resort View":         {"price": 189, "image": "resort-view.png"},
}

FALLBACK_IMAGE = "halekoa_Hotel.webp"
TAX_RATE = 0.1025


def get_room_image(room_name: str) -> str:
    room = ROOMS.get(room_name)
    return room["image"] if room else FALLBACK_IMAGE


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
    return render_template("index.html", hotelname="Hale Koa Hotel")


@app.route("/rooms")
def rooms():
    return render_template("ROOMS.html", rooms=ROOMS)


@app.route("/trip_summary", methods=["POST"])
def trip_summary():
    room_name, room_price = parse_room_selection(request.form.get("Rooms"))
    room_image = get_room_image(room_name)

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
