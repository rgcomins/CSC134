# DESIGN.md — Aloha Escapes Visual Direction

**Project:** Honolulu Hotels Booking System (m8) — branded as "Aloha Escapes"
**Author:** Richard Comins
**Companion docs:** `PRD.md` (what the app does), `design_doc.md` (how the code is shaped). This file points at the canonical design source and explains how each screen of our Flask app maps to it.

---

## 1. Canonical Design Source

The full graphic design system — color palette, typography, spacing, components, elevation rules — lives in **`wireframes/stitch_artful_honolulu_stays/honolulu_high_end_hospitality/DESIGN.md`**. That file plus the two reference HTML mocks at:

- `wireframes/stitch_artful_honolulu_stays/homepage_honolulu_hotels/code.html` (+ `screen.png`)
- `wireframes/stitch_artful_honolulu_stays/hotel_detail_honolulu_hotels/code.html` (+ `screen.png`)

…are the canonical artifacts. If anything in this document conflicts with the wireframes, the wireframes win.

This file's job is to (a) summarize the design language at a glance and (b) explain how each of our five Flask pages adapts the wireframes.

---

## 2. North Star

> "Organic minimalism with glassmorphic accents." Sophisticated tropical warmth, premium tranquility, editorial pacing. Heavy whitespace lets botanical imagery breathe. The aesthetic avoids sharp edges and harsh transitions, favoring soft, overlapping layers.

Brand mark: **ALOHA ESCAPES** (Playfair Display, uppercase, Deep Ocean Blue, tracked tight).

---

## 3. Design Tokens (Summary)

These tokens are encoded directly in `templates/base.html`'s Tailwind config so they're addressable from any template as utility classes.

### Colors

| Token | Hex | Role |
|---|---|---|
| `surface` / `background` | `#fdfae7` | Sandy Neutral — the canvas |
| `surface-container-lowest` | `#ffffff` | Cards and lifted surfaces |
| `on-surface` | `#1c1c11` | Body text |
| `on-surface-variant` | `#3f484c` | Secondary text, captions |
| `primary` | `#004655` | Deep Ocean Blue — headlines, brand, structure |
| `primary-container` | `#005f73` | Slightly lighter Ocean Blue |
| `secondary` | `#9b4500` | Deep Sunset Orange — active nav, label accents |
| `secondary-container` | `#fc8a40` | Sunset Orange container |
| `tertiary` | `#00474c` | Palm Green — soft icons and borders |
| `outline-variant` | `#bfc8cc` | Hairline dividers |
| (literal) | `#FF8C42` | Sunset Orange CTAs (used as a hard hex for the primary action color) |

60-30-10 distribution: Sandy Neutral (60), Deep Ocean Blue (30), Sunset Orange (10).

### Typography

- **Playfair Display** — display + headlines (`font-display`)
- **Plus Jakarta Sans** — body + UI (`font-body`)
- Scale tokens: `text-display-lg`, `text-display-lg-mobile`, `text-headline-lg(-mobile)`, `text-headline-md`, `text-body-lg`, `text-body-md`, `text-label-lg`, `text-label-sm`
- Uppercase label-lg with `0.05em` tracking is the signature "small caps" treatment used on nav links and section eyebrows.

### Spacing

- 8-pt base grid
- Layout: `container-max` 1280px, `margin-desktop` 64px, `margin-mobile` 20px, `gutter` 24px
- Section rhythm: `section-gap-lg` 120px, `section-gap-sm` 64px

### Shape language

- `rounded-lg` (0.5rem) for standard inputs and buttons
- `rounded-xl` / `2xl` / `3xl` for featured containers
- `organic-shape` (custom CSS) for asymmetric decorative blobs

### Elevation

- `shadow-ambient` and `shadow-ambient-sm` — soft, Ocean-Blue-tinted shadows lifting cards off the sandy surface
- `.glass-panel` (custom CSS) — `backdrop-filter: blur(20px)` over a 70% Sandy Neutral fill

### Iconography

- Material Symbols Outlined — referenced by name (`pool`, `spa`, `restaurant`, `calendar_today`, `king_bed`, etc.)

---

## 4. Component → Screen Map

| Wireframe screen | Our Flask page | Adaptations |
|---|---|---|
| Homepage hero with glass search panel | `/` (`index.html`) | Replaced the search inputs with a glass CTA panel — same visual language, simpler interaction. Routes to `/hotels`. |
| (No wireframe — invented for our flow) | `/hotels` (`hotels.html`) | Editorial card grid in 1/2/3 columns. Each card uses the same shape language and Sunset Orange "Choose →" link as the wireframe's CTAs. |
| Hotel detail with bento + sticky booking widget | `/rooms/<hotel_slug>` (`rooms.html`) | 1:1 match: breadcrumb, name + rating header, bento gallery (hero + 3 room photos), 8/4 main grid with About + Tags + Pick Your Room + Amenities on the left, sticky glass booking widget on the right. Widget contains the full booking form (hidden `hotel_slug`, dates, nights, room, traveler name, airfare, activities, style, notes). |
| (No wireframe) | `/trip_summary` (POST) (`trip_summary.html`) | Hero card pattern (image + Sunset Orange price), two-column trip details + cost breakdown, text-link footer actions. |
| (No wireframe) | 404 (`not_found.html`) | Centered Playfair fallback with one Sunset Orange CTA back to `/hotels`. |

Shared chrome (`_nav.html`, `_footer.html`) is rendered on every page so the visual rhythm stays consistent.

---

## 5. Where the Implementation Lives

- `templates/base.html` — fonts + Tailwind config + custom CSS link
- `templates/_nav.html`, `templates/_footer.html` — shared chrome
- `static/styles.css` — only the things Tailwind can't express:
  - `.glass-panel` (backdrop blur)
  - `.organic-shape` (asymmetric radius)
  - Material Symbols default variation settings
  - `.bg-pattern` (subtle Palm Green dot pattern)
  - `.tabular` (tabular-nums for prices)
- Templates use Tailwind utility classes directly so the design tokens are addressable inline.

---

## 6. Future Work

- Replace the placeholder hero images for four of the five hotels with real or licensed photography.
- Build a real interactive map component for hotel locations.
- Add a date picker modal sized like the wireframe's "Calendar View" event.
- Filter/sort the destinations grid (price, neighborhood, tags).
- Run an accessibility pass: focus states, alt text, color contrast on the photographic backgrounds.
