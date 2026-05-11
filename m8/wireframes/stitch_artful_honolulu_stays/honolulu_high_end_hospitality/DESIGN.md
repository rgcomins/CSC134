---
name: Honolulu High-End Hospitality
colors:
  surface: '#fdfae7'
  surface-dim: '#dddbc8'
  surface-bright: '#fdfae7'
  surface-container-lowest: '#ffffff'
  surface-container-low: '#f7f4e1'
  surface-container: '#f1eedb'
  surface-container-high: '#ece9d6'
  surface-container-highest: '#e6e3d0'
  on-surface: '#1c1c11'
  on-surface-variant: '#3f484c'
  inverse-surface: '#313124'
  inverse-on-surface: '#f4f1de'
  outline: '#6f797c'
  outline-variant: '#bfc8cc'
  surface-tint: '#13677b'
  primary: '#004655'
  on-primary: '#ffffff'
  primary-container: '#005f73'
  on-primary-container: '#91d7ee'
  inverse-primary: '#8bd1e8'
  secondary: '#9b4500'
  on-secondary: '#ffffff'
  secondary-container: '#fc8a40'
  on-secondary-container: '#672c00'
  tertiary: '#00474c'
  on-tertiary: '#ffffff'
  tertiary-container: '#136066'
  on-tertiary-container: '#95d8df'
  error: '#ba1a1a'
  on-error: '#ffffff'
  error-container: '#ffdad6'
  on-error-container: '#93000a'
  primary-fixed: '#b2ebff'
  primary-fixed-dim: '#8bd1e8'
  on-primary-fixed: '#001f27'
  on-primary-fixed-variant: '#004e5f'
  secondary-fixed: '#ffdbc9'
  secondary-fixed-dim: '#ffb68d'
  on-secondary-fixed: '#331200'
  on-secondary-fixed-variant: '#763300'
  tertiary-fixed: '#abeef5'
  tertiary-fixed-dim: '#8fd2d8'
  on-tertiary-fixed: '#002022'
  on-tertiary-fixed-variant: '#004f54'
  background: '#fdfae7'
  on-background: '#1c1c11'
  surface-variant: '#e6e3d0'
typography:
  display-lg:
    fontFamily: Playfair Display
    fontSize: 64px
    fontWeight: '700'
    lineHeight: '1.1'
    letterSpacing: -0.02em
  display-lg-mobile:
    fontFamily: Playfair Display
    fontSize: 40px
    fontWeight: '700'
    lineHeight: '1.2'
  headline-lg:
    fontFamily: Playfair Display
    fontSize: 48px
    fontWeight: '600'
    lineHeight: '1.2'
  headline-lg-mobile:
    fontFamily: Playfair Display
    fontSize: 32px
    fontWeight: '600'
    lineHeight: '1.2'
  headline-md:
    fontFamily: Playfair Display
    fontSize: 32px
    fontWeight: '500'
    lineHeight: '1.3'
  body-lg:
    fontFamily: Plus Jakarta Sans
    fontSize: 18px
    fontWeight: '400'
    lineHeight: '1.6'
  body-md:
    fontFamily: Plus Jakarta Sans
    fontSize: 16px
    fontWeight: '400'
    lineHeight: '1.6'
  label-lg:
    fontFamily: Plus Jakarta Sans
    fontSize: 14px
    fontWeight: '600'
    lineHeight: '1.2'
    letterSpacing: 0.05em
  label-sm:
    fontFamily: Plus Jakarta Sans
    fontSize: 12px
    fontWeight: '500'
    lineHeight: '1.2'
rounded:
  sm: 0.25rem
  DEFAULT: 0.5rem
  md: 0.75rem
  lg: 1rem
  xl: 1.5rem
  full: 9999px
spacing:
  base: 8px
  container-max: 1280px
  gutter: 24px
  margin-desktop: 64px
  margin-mobile: 20px
  section-gap-lg: 120px
  section-gap-sm: 64px
---

## Brand & Style

The brand personality is a sophisticated blend of tropical warmth and premium tranquility. It targets discerning travelers seeking an authentic yet elevated Hawaiian experience. This design system moves away from clinical booking engines toward an editorial, immersive journey that evokes the "Aloha" spirit through tactile digital experiences.

The visual style is **Organic Minimalism with Glassmorphic accents**. It prioritizes heavy whitespace (using the sandy neutral as a base) to let botanical imagery breathe. Interactions should feel fluid and rhythmic, mirroring the movement of the ocean. The aesthetic avoids sharp edges and harsh transitions, favoring soft, overlapping layers that create a sense of depth and discovery.

## Colors

The palette is rooted in the natural landscape of Honolulu. 
- **Deep Ocean Blue (#005F73)** serves as the primary brand color, used for core UI elements and deep-contrast backgrounds to establish a premium feel.
- **Sunset Orange (#FF8C42)** acts as a high-vibrancy accent for primary actions and calls-to-action (CTAs), capturing the energy of the golden hour.
- **Lush Palm Green (#065A60)** is used for iconography and decorative botanical elements, grounding the digital space in nature.
- **Sandy Neutral (#F4F1DE)** is the canvas of the design system, used for large background areas to provide a softer, more organic alternative to pure white.

Use a "60-30-10" distribution rule: Sandy Neutral for the majority of the interface, Deep Ocean Blue for structural secondary elements, and Sunset Orange for precise, high-impact focus points.

## Typography

This design system utilizes a high-contrast typographic pairing to balance tradition with modernity. 

**Playfair Display** is the artistic voice of the system. It should be used for large, expressive headlines and editorial quotes. Its high-contrast serifs convey luxury and heritage. For the most premium sections, use "Display" sizes with tight letter-spacing.

**Plus Jakarta Sans** provides a clean, contemporary counterpoint. Its soft, rounded terminals echo the "welcoming" nature of the brand. It is used for all functional UI elements, body copy, and metadata to ensure maximum legibility and a friendly tone. Use the uppercase `label-lg` style for navigation and small headers to add a touch of modern sophistication.

## Layout & Spacing

The layout philosophy follows a **Fixed Grid with Fluid Margins**. Content is centered within a 1280px container on desktop, utilizing a 12-column grid. On mobile, the system shifts to a single-column layout with 20px side margins.

To maintain the "lush" and "organic" feel, the design system employs generous vertical spacing (`section-gap-lg`). Elements should not feel cramped; white space is a deliberate design feature that signifies luxury. Use asymmetrical layouts (e.g., an image offset against a text block) to mimic the irregular beauty of nature. Components like cards or images can occasionally break the grid to create a "scrapbook" or "travelogue" aesthetic.

## Elevation & Depth

Depth is achieved through **Soft Ambient Shadows** and **Glassmorphic Overlays**, rather than hard borders or intense shadows.

- **Surface Layers:** Use very soft, diffused shadows with a slight tint of Deep Ocean Blue (#005F73) at low opacity (5-8%) to lift cards off the Sandy Neutral background.
- **Glassmorphism:** Navigation bars and search filters should use a backdrop blur effect (20px) with a semi-transparent white fill (opacity 70%). This allows botanical background imagery to peek through, maintaining the "lush" feel even when UI elements are present.
- **Tonal Depth:** Use subtle variations of the Sandy Neutral to define different content zones without needing physical dividers.

## Shapes

The shape language is strictly **Rounded and Organic**. Sharp corners are avoided to maintain the "soft" and "welcoming" brand promise.

- **Standard Elements:** Buttons and input fields use a medium radius (0.5rem) to feel approachable yet structured.
- **Featured Containers:** Large imagery, "Book Now" modules, and highlighted testimonials should use `rounded-xl` (1.5rem) or custom asymmetrical radii (e.g., top-left and bottom-right rounded, others sharp) to mimic the shape of tropical leaves or smoothed beach stones.
- **Iconography:** Icons should feature rounded caps and corners, avoiding any aggressive points.

## Components

- **Buttons:** Primary buttons use the Sunset Orange (#FF8C42) with white text for maximum visibility. Secondary buttons should use Deep Ocean Blue outlines with a subtle Sandy Neutral hover state. Use a slight scale-up transform (1.02x) on hover to create a tactile feel.
- **Input Fields:** Search inputs (e.g., date pickers, guest counters) should be large and airy. Use a 1px border in a muted version of Palm Green (#065A60) that thickens slightly on focus.
- **Cards:** Property and room cards should be borderless, utilizing the soft ambient shadows defined in Elevation. Image headers within cards should have a subtle zoom effect on hover.
- **Chips & Tags:** Use low-opacity versions of the Palm Green and Ocean Blue for category tags (e.g., "Ocean View," "Luxury Suite"), keeping the text in the dark primary color for accessibility.
- **Date Picker:** An essential component for this design system. It should be presented as a full-screen or large-modal "Calendar View" using Playfair Display for the month headings, ensuring the booking process feels like an event, not a chore.
- **Botanical Accents:** Use SVG leaf patterns or organic "blobs" as background decorations behind components to break the monotony of the grid.