# Aloha Escapes — Honolulu Hotels Booking System (m8)

A small Flask web app that lets a visitor browse a curated menu of five Waikiki hotels, choose a room and trip dates, and see an itemized cost summary for the stay.

This is the Project 4 submission for CSC 134.

---

## What it does

1. **Landing page** — editorial hero with a "Browse Hotels" call to action.
2. **Hotel menu** — five Honolulu properties (Hale Koa, Hilton Hawaiian Village, The Royal Hawaiian, Moana Surfrider, Sheraton Waikiki).
3. **Hotel detail** — bento gallery, hotel description, room list, and a sticky booking widget with all trip-planning inputs.
4. **Trip summary** — itemized cost breakdown (stay + airfare + activities + 10.25% tax) rendered after the form is submitted.

---

## Tech stack

- **Flask 3.x** — Python web framework
- **Jinja2** — template engine (bundled with Flask)
- **Tailwind CSS** (via CDN) — utility styling, configured inline in `templates/base.html`
- **Google Fonts** — Playfair Display + Plus Jakarta Sans
- **Material Symbols Outlined** — iconography

No build step. No database. No JavaScript framework. Everything runs server-side.

---

## Running it locally

From inside the `m8/` directory:

```bash
python app.py
```

The dev server starts on **http://127.0.0.1:5000/**. Debug mode is on, so edits to templates or `app.py` reload automatically.

If Flask isn't installed yet:

```bash
pip install flask
```

---

## Routes

| Method | Path | What it renders |
|---|---|---|
| GET | `/` | Landing hero (`index.html`) |
| GET | `/hotels` | Curated hotel menu (`hotels.html`) |
| GET | `/rooms/<hotel_slug>` | Hotel detail + booking form (`rooms.html`) |
| POST | `/trip_summary` | Itemized cost summary (`trip_summary.html`) |

Valid hotel slugs: `hale-koa`, `hilton-hawaiian-village`, `royal-hawaiian`, `moana-surfrider`, `sheraton-waikiki`. Any other slug renders a friendly 404 page (`not_found.html`).

---

## Project files

```
m8/
├── app.py                   # Flask routes + HOTELS data + cost math
├── README.md                # this file
├── PRD.md                   # product requirements
├── design_doc.md            # code-side design (data + functions + flow)
├── DESIGN.md                # visual design vision; points at wireframes/
├── project4_brief.md        # the original assignment brief
├── static/
│   ├── styles.css           # custom CSS (glass panel, organic shape, etc.)
│   └── *.jpg / *.png / *.webp  # hotel + room photography
├── templates/
│   ├── base.html            # shared head, fonts, Tailwind config
│   ├── _nav.html            # glassmorphic top nav
│   ├── _footer.html         # shared footer
│   ├── index.html           # landing
│   ├── hotels.html          # hotel menu
│   ├── rooms.html           # hotel detail + booking widget
│   ├── trip_summary.html    # cost summary
│   └── not_found.html       # 404 fallback
└── wireframes/              # canonical design source (Stitch mockups + DESIGN.md)
```

---

## Image credits

Non-Hale-Koa photography comes from **Wikimedia Commons** under Creative Commons (CC BY, CC BY-SA) and Public Domain licenses. Full attribution for every image lives as a comment block at the top of `app.py` near the `HOTELS` dict, per the license terms.

Source: [commons.wikimedia.org](https://commons.wikimedia.org/)
