# DESIGN.md — Creative Vision

**Project:** Honolulu Hotels Booking System (m8)
**Author:** Richard Comins
**Companion docs:** `PRD.md` (what the app does), `design_doc.md` (how the code is shaped). This file is about how the app should *feel*.

---

## 0. North Star

> When a visitor lands on the site, they should believe — within two seconds — that they are looking at a real Honolulu hospitality brand. Not a class project, not a placeholder. A real resort site.

The current UI (lime-green nav link, cyan submit button, tomato/steel-blue/lime radio buttons) is intentionally a placeholder. None of it survives this redesign. Every screen gets re-skinned to feel calm, premium, and rooted in place.

---

## 1. Mood & References

The visual language draws from the upper end of Waikiki hospitality marketing — the kind of site you'd land on from a Google search for "Waikiki resort" and not immediately bounce from.

**Mood words:** warm, calm, breezy, premium, place-aware, uncluttered.

**Reference patterns** (high-level — we're not copying, we're learning from):
- Large, quiet hero photography that does most of the talking.
- Generous white space; the page breathes.
- A single, restrained accent color rather than a rainbow of buttons.
- Serif display type for moments that should feel like a name plaque; clean sans-serif for everything else.
- Booking affordances that are obvious without shouting.

**What we are explicitly *not* doing:** stock-photo collage, gradient buttons, neon CTAs, drop-shadowed cards on a textured background, animated marquees, autoplaying audio.

---

## 2. Color Palette

A small, place-rooted palette. No more than three colors carry meaning on any single screen.

| Role | Name | Hex | Notes |
|---|---|---|---|
| Background (primary) | Coral Sand | `#F7F1E8` | Off-white with a warm sand cast. Replaces hard white. |
| Surface (cards) | Paper | `#FFFFFF` | Used sparingly, for cards and the booking form. |
| Ink (primary text) | Deep Lava | `#1F1A17` | Near-black with a warm undertone. Replaces pure black. |
| Ink (secondary text) | Driftwood | `#6B5E54` | Captions, meta, labels. |
| Accent (primary) | Pacific | `#0E5B72` | One deep ocean teal. Used for primary CTAs and links. |
| Accent (hover) | Pacific Deep | `#08465A` | CTA hover/active. |
| Highlight | Hibiscus | `#C8553D` | Used **once per screen at most** — for the price or a single accent. Never on body text. |
| Divider | Mist | `#E5DDD2` | Hairline dividers between sections. |

**Rules:**
- One primary CTA per view, in Pacific. Secondary actions are text links or outlined buttons in Driftwood.
- Hibiscus is a spice, not a base ingredient. If you find yourself using it twice on a screen, remove one.
- All text on photographic backgrounds gets a subtle gradient scrim underneath so contrast clears WCAG AA at all viewport sizes.

---

## 3. Typography

Two families, used with discipline.

- **Display / headings:** a quiet serif — Cormorant Garamond, Playfair Display, or the system fallback `Georgia, serif`. Used for hotel names, screen titles, the grand-total figure on the summary.
- **Body / UI:** a modern humanist sans-serif — Inter, or the system fallback `system-ui, -apple-system, "Segoe UI", Roboto, sans-serif`. Used for everything else.

**Scale** (mobile / desktop):
- Display XL — 40px / 64px — hero headlines.
- Display L — 28px / 40px — hotel card name, summary title.
- Display M — 22px / 28px — section titles.
- Body — 16px / 17px — running text.
- Caption — 13px / 14px — meta, labels, footnotes.

**Treatment:**
- Headings have generous letter-spacing (-0.5px to -1px on large display sizes).
- Body line-height is `1.6`. Headings line-height is `1.15`.
- Numbers (prices, totals) use tabular figures so columns of money align.

---

## 4. Layout System

- **Grid:** a 12-column grid with a max content width of `1200px`. Side gutters of `24px` mobile, `48px` desktop.
- **Vertical rhythm:** sections separated by `96px` desktop / `64px` mobile of breathing room. The page should feel like it has space to walk around in.
- **Cards:** white surface, `1px` Mist border, `12px` radius, no drop shadow at rest. On hover/focus, a soft `0 12px 32px rgba(31,26,23,0.08)` shadow and a `4px` lift. Never two competing card styles on one page.
- **Buttons:**
  - Primary: solid Pacific, white text, 14px vertical / 24px horizontal padding, `999px` (pill) radius, no border. Hover: Pacific Deep.
  - Secondary: transparent, Pacific text, `1px` Pacific border, same padding/radius.
  - Tertiary: text-only link in Pacific, underline on hover.
- **Forms:** label above input, `14px` gap. Inputs have a `1px` Mist border, `8px` radius, `12px` vertical padding. Focused state: Pacific border + a subtle Pacific glow. No placeholder-only labels.

---

## 5. Photography & Imagery

The hero image *is* the design on most screens. Photography rules:

- **Subject:** real-place imagery — beach, palm canopy, lobby light, balcony view. Aspirational but not surreal.
- **Composition:** wide, horizon-anchored, leave room for type to sit on the image without crowding.
- **Tone:** warm, slightly desaturated. Avoid heavy filters, Instagram presets, or HDR over-processing.
- **Treatment:** every image used behind text gets a vertical scrim — a 0–40% Deep Lava gradient from bottom — so headlines stay legible without needing a tinted overlay over the whole image.
- **Fallback:** when real art isn't available yet, use a single neutral fallback (current `halekoa_Hotel.webp`). Never use clip art, illustrations, or icon-only cards as a substitute for photography.

For the five hotels, each gets one hero shot and one room shot per room type. Until licensed art is in place, we use placeholder photos consistent with the above mood.

---

## 6. Screen-by-Screen Direction

### 6.1 Landing Page (`/`)
- Full-bleed hero image (Waikiki sunset or palm canopy).
- Single display-XL headline at lower-left: *"Find your stay in Honolulu."* in serif, white, with scrim.
- One primary CTA below the headline: *Browse Hotels →* (Pacific pill, white text).
- Subtle scroll indicator. No nav bar, no second CTA, no carousel.

### 6.2 Hotel Menu (`/hotels`)
- Page title in serif: *"Five places to stay in Honolulu."* Subtitle in sans: *"Curated for this trip."*
- Responsive grid of five hotel cards. Three columns desktop, two columns tablet, one column mobile.
- Each card:
  - Hotel photo (16:10 ratio).
  - Hotel name in serif (Display L).
  - One-line tagline in Driftwood.
  - Location + starting price on one row: *Waikiki · from $189/night*.
  - "Choose this hotel →" as a text link in Pacific (the whole card is also clickable).
- Cards hover with a 4px lift + soft shadow. The image gets a barely-perceptible zoom (`scale(1.02)`) on hover.

### 6.3 Room Selection (`/rooms/<hotel_slug>`)
- Hotel banner at top: full-bleed hero image at `40vh` with the hotel name (serif, white, scrim) overlaid bottom-left.
- Under the banner, a one-line breadcrumb back: *← All hotels*.
- Below: a two-column layout on desktop —
  - **Left (60%):** room gallery. Each room is its own row: a 4:3 image on the left and the room name, nightly price, and a one-line description on the right. The selected room highlights with a Pacific border on its row.
  - **Right (40%):** sticky booking form. White card, Mist border, organized with clear section headings: *Your trip*, *Add activities*, *Travel style*. The Submit button is a Pacific pill that says *See trip summary →*. No cyan, no orange reset button; reset is a tertiary text link under the submit.
- On mobile, gallery stacks above form.

### 6.4 Trip Summary (`/trip_summary`)
- Page opens with a hero card spanning the content width:
  - Left half: chosen room photo (rounded 12px, no shadow).
  - Right half: hotel name in serif (Display L), room name in sans, nightly price in Hibiscus (the one place Hibiscus shows up).
- Below the hero, a two-column breakdown:
  - **Left:** trip details (dates, traveler name, nights, activities).
  - **Right:** cost table. Each row aligned with tabular numerals. Subtotal and tax in Driftwood; **Grand Total** in Deep Lava, serif, Display M.
- Bottom: two text-link actions — *Book another hotel →* (to `/hotels`) and *Return home* (to `/`). No big buttons; this is a reading page, not an action page.

### 6.5 Not-Found (`/rooms/<unknown>`)
- Centered serif headline: *"We couldn't find that hotel."*
- One-line sans subtitle in Driftwood.
- A single Pacific text link: *← Back to all hotels*.
- No 404 graphic, no humor. Quiet and useful.

---

## 7. Motion & Micro-interactions

Motion is restrained. Every animation should feel like the room reacting to the user — not the page performing.

- Hover lift on cards: `transform: translateY(-4px)` + shadow, transitioned over `200ms ease-out`.
- Hover zoom on hero images inside cards: `scale(1.02)` over `400ms ease-out`.
- Page transitions: a `120ms` fade-in on `main` content. No slide transitions, no full-screen overlays.
- Form submit button: a brief Pacific Deep flash on click; no spinners (the server response is instant).

**No:** parallax, scroll-jacking, auto-playing video, particle effects, "scroll to reveal" cascading entrance animations.

---

## 8. Accessibility Floor

Non-negotiable.

- All text meets WCAG AA contrast on its background, including text over scrimmed photos.
- Every image has an `alt` describing the room or hotel, not just "image".
- Every form input has a real `<label>` associated by `for`/`id`.
- Focus states are visible (Pacific glow ring, never `outline: none` without a replacement).
- The hotel cards on `/hotels` are real `<a>` elements wrapping the card content, so keyboard tab order works.
- The site is usable on a 320px-wide screen with no horizontal scroll.

---

## 9. What This Replaces

| Old (placeholder) | New (this design) |
|---|---|
| Lime-green "Rooms" link on hero | Pacific pill CTA "Browse Hotels →" |
| Cyan submit button (`#00ced1`) | Pacific pill submit *See trip summary →* |
| Orange-red reset button (`#ff4500`) | Tertiary text link "Clear form" |
| Tomato / steel-blue / lime travel-style radios | Three uniform pill chips in Mist, selected state in Pacific |
| Lightgreen comments textarea | Paper background, Mist border, focus in Pacific |
| Pure white background | Coral Sand `#F7F1E8` |
| Pure black text | Deep Lava `#1F1A17` |
| Bordered table of room images | Two-column gallery rows, no table borders |
| YouTube promo embed in the middle of the booking form | Removed from the booking flow (optional re-introduction on each hotel's landing banner) |

---

## 10. Implementation Order

This is the order in which to apply the redesign once we're building. Each step is shippable on its own — the site should look better at every commit, not only at the end.

1. Adopt the color palette and typography as CSS variables in a single shared stylesheet.
2. Re-skin the landing page (`/`) with the new hero treatment and Pacific CTA.
3. Build the hotel menu (`/hotels`) using the new card system.
4. Re-skin the room page (`/rooms/<hotel_slug>`) with the banner + two-column layout.
5. Re-skin the trip summary (`/trip_summary`) with the hero card + breakdown layout.
6. Replace placeholder room/hotel imagery as real photography becomes available.

---

## 11. Open Questions (to discuss)

- **Hotel set:** are the five Waikiki properties listed in the PRD the right curated set, or should we include a Kahala / North Shore option to show range?
- **Photography:** OK to use representative public-domain Waikiki photography for the placeholder pass, with a clear plan to swap to licensed shots later?
- **Type loading:** acceptable to pull serif/sans from Google Fonts, or do we want to bundle a single font file to keep this fully offline-runnable?
- **Scope of redesign in this iteration:** all five screens, or land the hotel-menu work first and re-skin in a follow-up?
