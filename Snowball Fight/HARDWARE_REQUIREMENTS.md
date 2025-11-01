# Hardware Requirements - Complete Guide

Detailed hardware specifications and how FastLED affects your setup.

---

## TL;DR: FastLED Changes

**The FastLED migration changes:**
- ✅ What displays are *practical* (larger ones now work)
- ❌ What displays *work* (all WS2812B types still work)

**Hardware you need to buy - SAME as before**

---

## Microcontroller

### Recommended: ESP32-S3
**Best performance, modern, widely available**
- Dual-core 240 MHz CPU
- 512 KB SRAM (plenty for this game)
- Native USB support (no extra cable needed)
- DMA support (critical for FastLED)

Where to buy:
- Amazon: "ESP32-S3 DevKit"
- Adafruit: ESP32-S3 Feather
- AliExpress: ESP32-S3-DevKitC-1

Price: $8-15

### Alternative: Standard ESP32
**Older, still works perfectly**
- Single-core or dual-core 160/240 MHz
- 160 KB SRAM (still enough)
- Requires CH340 USB driver on some boards
- DMA support (slightly slower than S3)

Price: $5-10

### Not Recommended: ESP32-P4
**Overkill and harder to source**
- Quad-core 360 MHz
- Designed for 4K video, not needed here
- Price: $15-25
- Only use if you want 4×4 displays (not practical anyway)

### Board Specifications (All variants)
| Feature | Required | Actual |
|---------|----------|--------|
| GPIO pins | 11 | 50+ available |
| I2C support | Yes | Native |
| SPI support | No | Has it anyway |
| USB programming | Yes | Native |
| Memory | 20KB | 160KB-512KB |

---

## LED Display

### Panel Types (ALL compatible with FastLED)

**WS2812B** (Most common)
- 5V logic
- ~1.2W per pixel @ full white
- 800 kHz data rate
- Works perfectly with FastLED

**SK6812 (RGBW)**
- Drop-in replacement for WS2812B
- Includes white LED per pixel
- Same power/timing
- Fully compatible

**WS2811** (Older)
- Works but slower (400 kHz)
- Less common
- Fully compatible

**APA102** (SPI-based)
- Requires 2 data lines
- NOT compatible with current setup (uses single data line)
- Would need code changes

### Panel Sizes (ALL compatible with FastLED)

**16×16 panels**
- 256 pixels per panel
- Power: ~1.5A @ full brightness
- Good for: Testing, small arcade cabinets
- Drawback: Tight gameplay, small sprites

**32×32 panels** (Recommended)
- 1,024 pixels per panel
- Power: ~5A @ full brightness
- Good for: Perfect balance of size/power
- Standard Adafruit matrix size
- Most affordable

**64×64 panels**
- 4,096 pixels per panel
- Power: ~20A @ full brightness
- Good for: High-res display, premium arcade
- Single panel = 2×2 grid equivalent
- Harder to source, more expensive

**Custom sizes**
- 32×16, 16×64, etc.
- Fully supported
- Calculate power: `(pixels ÷ 1024) × 5A`

---

## Display Configuration Impact

### FastLED Enables Larger Displays

**Before FastLED:**
```
2×2 (64×64)  → 60 FPS ✅
3×2 (96×64)  → 40 FPS ❌ (not playable)
```

**After FastLED:**
```
2×2 (64×64)  → 60 FPS ✅ (very comfortable)
3×2 (96×64)  → 60 FPS ✅ (NOW VIABLE)
4×1 (128×32) → 60 FPS ✅ (NOW VIABLE)
```

### Panel Arrangement Options

All of these work perfectly now:

| Config | Dimensions | Total Pixels | Power Draw | Gameplay | Status |
|--------|-----------|---------|------------|----------|--------|
| 1×1 32×32 | 32×32 | 1,024 | 5A | Tight | ✅ Small |
| 2×1 32×32 | 64×32 | 2,048 | 10A | Balanced | ✅ **Default** |
| 1×2 32×32 | 32×64 | 2,048 | 10A | Vertical | ✅ Tall |
| 2×2 32×32 | 64×64 | 4,096 | 20A | Epic | ✅ **Recommended** |
| 3×1 32×32 | 96×32 | 3,072 | 15A | Very wide | ✅ Panoramic |
| 4×1 32×32 | 128×32 | 4,096 | 20A | Extremely wide | ⚠️ Edge case |
| 3×2 32×32 | 96×64 | 6,144 | 30A | Massive | ✅ **NOW VIABLE** |
| 1×1 64×64 | 64×64 | 4,096 | 20A | Epic | ✅ Premium |
| 2×2 16×16 | 64×32 | 4,096 | 6A | Low-res | ✅ Low power |

---

## Power Supply Requirements

### Critical: You MUST have adequate power

LED panels draw significant current. Under-powering causes:
- Flickering display
- Brown-out resets
- Corrupted data
- Shortened LED lifespan

### Power Supply Sizing

**Calculation:**
```
Power (A) = (Total Pixels ÷ 1024) × 5A
Safety Factor: Multiply by 1.2-1.5 for headroom
```

**Examples:**
- 1×1 32×32: 1024 px → 5A × 1.5 = **7.5A PSU** (recommend 10A)
- 2×1 32×32: 2048 px → 10A × 1.5 = **15A PSU**
- 2×2 32×32: 4096 px → 20A × 1.5 = **30A PSU**
- 3×2 32×32: 6144 px → 30A × 1.5 = **45A PSU**

### Recommended Power Supplies

| Setup | Panel Count | PSU Size | Notes |
|-------|------------|----------|-------|
| Single 32×32 | 1 | 5V/10A | Cheap, easy |
| 2×1 or 1×2 32×32 | 2 | 5V/15A | Balanced |
| 2×2 32×32 | 4 | 5V/25A | Popular arcade |
| 3×2 32×32 | 6 | 5V/40A | Large, needs quality PSU |
| Large single 64×64 | 1 | 5V/25A | Easier than 2×2 |

### Quality is Critical
- **Don't use:** Cheap laptop chargers, unreliable knockoffs
- **Do use:** Industrial 5V supplies (Meanwell, CBI, etc.)
- **Check:** Can it sustain full current for hours?

**Red flag:** If PSU is cheaper than panels, it's probably bad

---

## Input Devices

### Accelerometers: MPU6050

**Quantity:** 2 (one per player)
**Interface:** I2C (2-wire)
**Addresses:** 0x68, 0x69 (configurable)
**Pins needed:** GPIO 21 (SCL), GPIO 22 (SDA) - both shared
**Power:** 3.3V (with regulator) or 5V (with level shifter)

**Wiring:**
```
ESP32  ←→  MPU6050 #1        ESP32  ←→  MPU6050 #2
3V3    ←→  VCC               3V3    ←→  VCC
GND    ←→  GND               GND    ←→  GND
GPIO21 ←→  SCL               GPIO21 ←→  SCL
GPIO22 ←→  SDA               GPIO22 ←→  SDA
               ←→  AD0=GND                   ←→  AD0=3V3
```

**Address Configuration:**
- Default (AD0 to GND): 0x68
- High (AD0 to 3V3): 0x69
- Different addresses on each board = no conflicts ✅

**Spring Mount:**
- Accelerometer on spring-loaded button
- Pressing down = throw action
- Z-axis detects compression
- XY axes detect angle

**Cost:** $2-5 per board

### Rotary Encoders

**Quantity:** 2 (one per player)
**Type:** Mechanical encoder with push button
**Interface:** GPIO pins (interrupt-driven)
**Pins per encoder:** 2 (CLK, DT)

**Wiring:**
```
Player 1            Player 2
GPIO26  ←→  CLK     GPIO32  ←→  CLK
GPIO27  ←→  DT      GPIO33  ←→  DT
GND     ←→  GND     GND     ←→  GND
```

**Characteristics:**
- 20 detents per rotation common
- Interrupt-driven (low CPU overhead)
- Tactile feedback good for games
- Build quality varies

**Cost:** $1-3 per encoder

---

## Wiring & Cable Requirements

### Data Line (LED panels → ESP32)

**Signal:** WS2812B digital data
**Pin:** GPIO 5 (MATRIX_PIN in config)
**Cable:** ~1m (4-wire):
- 5V power (2-gauge)
- GND (2-gauge)
- Data (22-gauge)
- GND return

**Wiring topology:**
```
ESP32 GPIO5 ─→ Panel1 DIN ─→ Panel1 DOUT ─→ Panel2 DIN ─→ Panel2 DOUT
                 Panel1 Power ←─────────────────→ common ground
```

**Important:**
- Keep data cable SHORT (<0.5m if possible)
- Data line can't be TOO long without signal conditioning
- Ground all panels together

### I2C Bus (Accelerometers)

**Pins:** GPIO 21 (SCL), GPIO 22 (SDA)
**Voltage:** 3.3V
**Cable:** Twisted pair, ~1m max safe
**Termination:** Pull-up resistors (built-in on most MPU6050 boards)

**Can daisy-chain multiple devices on same I2C bus**

### Encoder Pins

**GPIO pins:** 26, 27, 32, 33
**Voltage:** 3.3V
**Cable:** Standard hookup wire
**Protection:** Pull-up resistors (INPUT_PULLUP in code)

---

## Total Bill of Materials

### Minimum Setup (2×1 display)

| Item | Quantity | Cost | Where to buy |
|------|----------|------|--------------|
| ESP32-S3 DevKit | 1 | $10 | Amazon |
| Adafruit 32×32 NeoMatrix | 2 | $60 | Adafruit.com |
| 5V/15A Power Supply | 1 | $30 | Amazon |
| MPU6050 modules | 2 | $8 | AliExpress |
| Rotary encoders | 2 | $6 | AliExpress |
| Wiring & connectors | - | $15 | Amazon |
| **Total** | - | **~$130** | - |

### Recommended Setup (2×2 display)

| Item | Quantity | Cost | Where to buy |
|------|----------|------|--------------|
| ESP32-S3 DevKit | 1 | $10 | Amazon |
| Adafruit 32×32 NeoMatrix | 4 | $120 | Adafruit.com |
| 5V/25A Power Supply | 1 | $50 | Amazon |
| MPU6050 modules | 2 | $8 | AliExpress |
| Rotary encoders | 2 | $6 | AliExpress |
| Wiring & connectors | - | $20 | Amazon |
| **Total** | - | **~$215** | - |

---

## What FastLED Doesn't Change

### Hardware Compatibility ✅
- All WS2812B panels work
- All ESP32 variants work
- Power requirements per pixel unchanged (5A per 1024 pixels)
- Wiring stays identical
- Pin assignments work as-is

### Performance Benefits from FastLED

| Metric | Impact | Hardware Change? |
|--------|--------|-----------------|
| Rendering speed | 80% faster | NO |
| Larger displays | Now viable | NO (same panels) |
| Frame consistency | Much better | NO |
| Power draw | IDENTICAL | NO |
| LED panel voltage | IDENTICAL | NO |
| Pin usage | IDENTICAL | NO |

### What Actually Changed

**Software only:**
- Library (Adafruit → FastLED)
- Rendering method (bit-bang → DMA)
- CPU time per frame (50-80 → 5-10 cycles/pixel)

**Hardware:** Nothing. Same panels, same power, same wiring.

---

## Practical Limits

### Absolute Maximum (Still 60 FPS)
- **4×1 (128×32):** Viable but very wide
- **3×2 (96×64):** Viable but expensive
- **2×2 (64×64):** Recommended sweet spot
- **Beyond:** Frame rate drops (not recommended)

### Practical Recommended
- **Start with:** 2×1 (64×32) - default config
- **Upgrade to:** 2×2 (64×64) - epic experience
- **Consider:** 3×1 (96×32) - panoramic, crowd-friendly

---

## FAQ

**Q: Do I need to buy new LED panels for FastLED?**
A: NO. Existing WS2812B panels work perfectly.

**Q: Does FastLED need more power?**
A: NO. Power requirements unchanged (5A per 1024 pixels).

**Q: Can I use different panel sizes together?**
A: Technically yes, but not recommended (confusing gameplay).

**Q: What's the cheapest setup?**
A: 1×1 32×32 (~$70) - tight but playable.

**Q: What's the best value setup?**
A: 2×1 32×32 (~$130) - balanced gameplay and cost.

**Q: What's the "wow" setup?**
A: 2×2 32×32 (~$215) - epic arcade experience.

**Q: Can I build this incrementally?**
A: Yes! Start with 1×1, add panels later by updating config.h and code.

---

## Summary

### Hardware Required (Unchanged)
- 1× ESP32-S3 ($10)
- 2-4× WS2812B LED panels ($30-120)
- 5V power supply scaled to panel count ($30-50)
- 2× MPU6050 accelerometers ($8)
- 2× Rotary encoders ($6)
- Wiring ($15-20)

### Total Cost
- Minimum: ~$130 (playable)
- Recommended: ~$215 (epic)
- Maximum (3×2): ~$350+ (massive)

### FastLED Impact on Hardware
- ✅ Makes larger displays practical
- ❌ Doesn't require ANY new hardware
- ✅ Same power delivery works
- ❌ No rewiring needed

**You're ready to build!** 🎮

