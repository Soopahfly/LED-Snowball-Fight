# LED Matrix Scaling Guide

The Snowball Fight game now supports **flexible LED matrix configurations**. You can use any size and arrangement of panels without changing the game code!

---

## Quick Start

1. Edit [config.h](config.h)
2. Set your panel size and arrangement
3. Upload - game automatically scales!

No other code changes needed.

---

## Configuration Options

### Panel Dimensions

```cpp
#define PANEL_WIDTH 32    // Width of each physical panel
#define PANEL_HEIGHT 32   // Height of each physical panel
```

**Common Panel Sizes:**
- 16x16 pixels
- 32x32 pixels (most common)
- 64x64 pixels
- Custom sizes

### Grid Layout

```cpp
#define PANELS_HORIZONTAL 2  // Panels left to right
#define PANELS_VERTICAL 1    // Panels top to bottom
```

**Result:** Game board is `(PANEL_WIDTH * PANELS_HORIZONTAL) x (PANEL_HEIGHT * PANELS_VERTICAL)`

---

## Configuration Examples

### Single 32x32 Panel

**Use case:** Desktop version, small display

```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 1
#define PANELS_VERTICAL 1
```

**Result:** 32x32 game area

**Features:**
- Tight gameplay
- Smaller players, snowballs
- Good for testing
- Minimal power draw (~3A)

---

### Two 32x32 Panels Side-by-Side (DEFAULT)

**Use case:** Large 2-player arcade display

```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 2
#define PANELS_VERTICAL 1
```

**Result:** 64x32 game area

**Features:**
- Wide gameplay field
- Players separated by 32px
- Good for 2-player distance
- Power draw: ~6A

---

### Two 32x32 Panels Stacked

**Use case:** Tall vertical display, tournament screen

```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 1
#define PANELS_VERTICAL 2
```

**Result:** 32x64 game area

**Features:**
- More vertical space
- Taller gameplay arena
- Wind effects more dramatic
- Power draw: ~6A

---

### Four 32x32 Panels (2x2 Grid)

**Use case:** Large installation, arcade cabinet

```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 2
#define PANELS_VERTICAL 2
```

**Result:** 64x64 game area

**Features:**
- Maximum standard size
- Huge visible details
- Epic gameplay
- Power draw: ~12A (use good PSU!)

---

### Three Panels Wide

**Use case:** Ultra-wide panoramic display

```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 3
#define PANELS_VERTICAL 1
```

**Result:** 96x32 game area

**Features:**
- Very wide field
- Players far apart
- Great for spectators
- Power draw: ~9A

---

### Four Panels Wide

**Use case:** Massive installation, showpiece

```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 4
#define PANELS_VERTICAL 1
```

**Result:** 128x32 game area

**Features:**
- Huge horizontal space
- Wrapping becomes frequent
- Requires multiple controllers potentially
- Power draw: ~12A+

---

### Single Large 64x64 Panel

**Use case:** High-res arcade, premium display

```cpp
#define PANEL_WIDTH 64
#define PANEL_HEIGHT 64
#define PANELS_HORIZONTAL 1
#define PANELS_VERTICAL 1
```

**Result:** 64x64 game area

**Features:**
- Same area as 2x2 grid but single panel
- Better quality than chaining panels
- Easier wiring
- Power draw: ~12A

---

### Multiple 16x16 Panels (4x2 Grid)

**Use case:** Experimental small display, LED badge

```cpp
#define PANEL_WIDTH 16
#define PANEL_HEIGHT 16
#define PANELS_HORIZONTAL 4
#define PANELS_VERTICAL 2
```

**Result:** 64x32 game area (same as 2x1 32x32)

**Features:**
- More panels but smaller
- Higher refresh rate
- Low power consumption (~3A)
- Good for testing

---

## Automatic Scaling

The game **automatically adjusts** for any configuration:

### Player Positioning
```
Player 1 starts at: GAME_WIDTH / 8 (from left)
Player 2 starts at: GAME_WIDTH - GAME_WIDTH / 8 (from right)
```
- 32px wide: Players at 4px and 28px
- 64px wide: Players at 8px and 56px
- 96px wide: Players at 12px and 84px

### Terrain Generation
- Scales to full game width
- Maintains same proportions
- Same difficulty across all sizes

### Physics
- Gravity remains consistent
- Throw distances scale naturally
- Wind effects adapt to arena size

---

## Wiring & Power Considerations

### LED Power Draw

Each 32x32 panel at full brightness: ~5A
Each 16x16 panel: ~1.5A
Each 64x64 panel: ~20A

**Recommended Power Supplies:**

| Config | Power Draw | PSU Recommendation |
|--------|------------|-------------------|
| 1x1 (32x32) | ~5A | 5V/5A |
| 2x1 (64x32) | ~10A | 5V/15A |
| 2x2 (64x64) | ~20A | 5V/25A |
| 3x1 (96x32) | ~15A | 5V/20A |
| 4x1 (128x32) | ~20A | 5V/25A |

**Pro Tip:** Use good quality power supplies to avoid voltage sag and noise.

---

## Panel Chaining

### Data Line Connection
The game uses a single data line from ESP32 GPIO 5.

For multiple panels:
1. Connect first panel's DIN to GPIO 5
2. Connect first panel's DOUT to second panel's DIN
3. Continue chaining all panels
4. Last panel's DOUT is unused

### Important Notes
- NeoMatrix library handles addressing automatically
- Panel order matters! (configure via `MATRIX_CONFIG` in config.h)
- Current configuration assumes left-to-right, top-to-bottom addressing

---

## Testing Your Configuration

After uploading, check the Serial Monitor (115200 baud):

```
=== SNOWBALL FIGHT ===
Version: 0.1.0+effects
Build Date: 2025-11-01
Starting...
Game initialized!
Starting planet: Earth
```

The game should auto-detect and use your configured display size.

**If you see weird display behavior:**
1. Check `MATRIX_CONFIG` in config.h matches your panel arrangement
2. Test with Adafruit NeoMatrix example first
3. Verify all panels are receiving power
4. Check data line continuity

---

## LED Brightness Control

To reduce power draw and heat, lower brightness:

```cpp
#define LED_BRIGHTNESS 128  // 0-255, default 255
```

In the setup function, you can add:
```cpp
matrix.setBrightness(LED_BRIGHTNESS);
```

**Power vs. Brightness:**
- 255 (full): Max power, best visibility
- 200: ~80% power, still very bright
- 128: ~50% power, good for indoors
- 64: ~25% power, visible in dark
- 32: ~12% power, low visibility

---

## Performance Tips

**For large displays (2x2 or larger):**

1. **Reduce particle effects:**
   ```cpp
   #define MAX_PARTICLES 16  // Instead of 32
   ```

2. **Reduce wind zones:**
   ```cpp
   #define MAX_WIND_ZONES 2  // Instead of 4
   ```

3. **Lower brightness:**
   ```cpp
   #define LED_BRIGHTNESS 200  // Good compromise
   ```

4. **Reduce frame rate if needed:**
   ```cpp
   #define FPS 45  // Instead of 60
   ```

---

## Troubleshooting Display Configurations

### Only one panel lights up
- Check MATRIX_CONFIG in config.h
- Verify panel chaining order
- Test individual panels with Adafruit examples

### Some panels show wrong colors
- Check LED color order (usually GRB for WS2812B)
- Verify all panels are same type
- Check for power supply sagging

### Game doesn't fill entire display
- Verify PANEL_WIDTH and PANEL_HEIGHT match your panels
- Check PANELS_HORIZONTAL and PANELS_VERTICAL
- Confirm GAME_WIDTH and GAME_HEIGHT calculate correctly

### Too much lag on large displays
- Reduce MAX_PARTICLES
- Lower LED_BRIGHTNESS
- Reduce MAX_WIND_ZONES
- Check power supply isn't sagging

---

## Custom Arrangements

If you have an unusual panel arrangement, you may need to modify `MATRIX_CONFIG`:

```cpp
// Standard left-to-right, top-to-bottom
#define MATRIX_CONFIG (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + \
                       NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE)

// Other options available:
// NEO_MATRIX_RIGHT, NEO_MATRIX_BOTTOM
// NEO_MATRIX_COLUMNS
// NEO_MATRIX_ZIGZAG
```

See Adafruit NeoMatrix documentation for more options.

---

## Questions?

Check these files:
- [README.md](README.md) - General setup
- [config.h](config.h) - All configuration options
- [snowball_fight.ino](snowball_fight.ino) - Game code
- [CHANGELOG.md](CHANGELOG.md) - Recent changes
