# Quick Start Guide

Get Snowball Fight running in 30 minutes.

---

## 30-Minute Startup

### What You Need
- [ ] ESP32 board (~$10)
- [ ] 2-4 LED panels (~$30-120)
- [ ] MPU6050 accelerometers (x2, ~$8)
- [ ] Rotary encoders (x2, ~$6)
- [ ] 5V power supply (~$30-50)
- [ ] USB cable for programming
- [ ] Basic wiring (wire, connectors, solder)

### Step 1: Choose Your Display Size (2 min)

Pick one:
- **Small:** 1×1 (32×32) - tight but playable
- **Balanced (default):** 2×1 (64×32) - perfect for 2 players
- **Epic:** 2×2 (64×64) - best experience
- **Panoramic:** 3×1 (96×32) - wide gameplay
- **Huge:** 3×2 (96×64) - massive setup

### Step 2: Edit config.h (3 min)

Open `config.h` and update:

```cpp
// Change these to match your setup:
#define PANEL_WIDTH 32          // Width of each LED panel
#define PANEL_HEIGHT 32         // Height of each LED panel
#define PANELS_HORIZONTAL 2     // How many panels wide (1, 2, 3, or 4)
#define PANELS_VERTICAL 1       // How many panels tall (1 or 2)

// If you have standard Adafruit panels and ESP32, these are correct:
#define MATRIX_PIN 5            // Data line GPIO
#define ACCEL_P1_ADDR 0x68      // Player 1 accelerometer
#define ACCEL_P2_ADDR 0x69      // Player 2 accelerometer
```

That's it!

### Step 3: Install Compilation Tools (10 min)

**Option A: Arduino IDE (Easiest)**
1. Download from https://www.arduino.cc/en/software
2. Open, go to **Tools → Board → Boards Manager**
3. Search "ESP32" and install **esp32 by Espressif**
4. Go to **Sketch → Include Library → Manage Libraries**
5. Search and install: **FastLED** and **MPU6050**
6. Done!

**Option B: PlatformIO (Faster, Recommended)**
1. Install VS Code
2. Install **PlatformIO IDE** extension
3. Create new project, select ESP32 Dev Module
4. Copy your `.ino` and `.h` files to `src/` folder
5. PlatformIO auto-installs libraries from `platformio.ini`
6. Done!

### Step 4: Compile Code (5 min)

**Arduino IDE:**
1. Open `snowball_fight.ino`
2. Click **Verify** (checkmark icon)
3. Wait for "Sketch uses X bytes..." message
4. No errors = you're good ✅

**PlatformIO:**
1. Open terminal: `Ctrl + Shift + ~`
2. Type: `pio run`
3. Wait for `[SUCCESS]` message
4. Done! ✅

### Step 5: Assemble Hardware (15 min)

**LED Panels:**
```
ESP32 GPIO5 ──→ LED1 DIN ──→ LED1 DOUT ──→ LED2 DIN ──→ LED2 DOUT
LED1 5V  ──────→ POWER (5V)
LED1 GND ──────→ POWER (GND)
```

**Accelerometers (both on same I2C bus):**
```
ESP32 GPIO21 (SCL) ──→ MPU1 SCL ──→ MPU2 SCL
ESP32 GPIO22 (SDA) ──→ MPU1 SDA ──→ MPU2 SDA
ESP32 3V3     ──→ MPU1 VCC ──→ MPU2 VCC
ESP32 GND     ──→ MPU1 GND ──→ MPU2 GND
(MPU1 AD0 to GND = address 0x68)
(MPU2 AD0 to 3V3 = address 0x69)
```

**Encoders:**
```
P1 CLK → GPIO 26
P1 DT  → GPIO 27
P2 CLK → GPIO 32
P2 DT  → GPIO 33
All GND → ESP32 GND
```

**Power Supply:**
- 5V+ → LED panel power
- GND → Common ground (ESP32 + LED panels)

### Step 6: Upload Code (3 min)

**Arduino IDE:**
1. Connect ESP32 via USB
2. Select **Tools → Port → COM3** (or your port)
3. Click **Upload** (arrow icon)
4. Wait for "Hard resetting via RTS pin..."
5. Done! ✅

**PlatformIO:**
1. Connect ESP32 via USB
2. Terminal: `pio run -t upload`
3. Done! ✅

### Step 7: Test (2 min)

1. Open Serial Monitor (115200 baud)
2. You should see:
   ```
   === SNOWBALL FIGHT ===
   Version: 0.1.0+effects
   Starting...
   Game initialized!
   Starting planet: Earth
   ```
3. LED panels should light up with blue background
4. Accelerometer values should appear in Serial
5. You're ready to play! 🎮

---

## Controls

| Input | Action |
|-------|--------|
| Accelerometer (Player 1) | Throw snowballs at Player 2 |
| Accelerometer (Player 2) | Throw snowballs at Player 1 |
| Rotary Encoder (Player 1) | Move left/right |
| Rotary Encoder (Player 2) | Move left/right |
| Serial 'N' | Next planet |
| Serial 'P' | Previous planet |
| Serial '0-4' | Jump to planet (0=Earth, 1=Moon, etc.) |
| Serial 'R' | Reset game |

---

## Troubleshooting

### LEDs don't light up
- Check GPIO 5 connection to LED panel
- Verify 5V power to panels
- Try Adafruit NeoPixel example to test panels separately

### No accelerometer readings
- Check I2C wiring (GPIO 21 SCL, GPIO 22 SDA)
- Verify 3.3V power to MPU6050 boards
- Try I2C scanner to find device addresses

### Can't compile
- Make sure FastLED is installed
- Make sure MPU6050 is installed
- Check for typos in config.h

### Can't upload to board
- Check USB cable (try different port)
- Install CH340 USB driver if needed
- Select correct COM port in IDE

### Game runs but looks weird
- Check PANELS_HORIZONTAL and PANELS_VERTICAL in config.h
- Verify panel dimensions (PANEL_WIDTH, PANEL_HEIGHT)
- Make sure panels are connected in order (left-to-right, top-to-bottom)

---

## What's Next?

### Configuration
- Read [config.h](config.h) for physics and performance tuning
- Read [SCALING_GUIDE.md](SCALING_GUIDE.md) to try different display sizes
- Read [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md) to understand gravity

### Customization
- Change colors in snowball_fight.ino (COLOR_P1, COLOR_P2, etc.)
- Adjust throw sensitivity: `THROW_DETECTION_G` in config.h
- Adjust gravity: planet definitions in snowball_fight.ino
- Adjust particle count: `MAX_PARTICLES` in config.h

### Hardware Scaling
- Start with 2×1, upgrade to 2×2 later
- Just update config.h and recompile
- No code changes needed, game auto-scales

### Documentation
- [README.md](README.md) - Full feature overview
- [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md) - Detailed build instructions
- [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md) - Bill of materials
- [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) - Technical deep dive

---

## Common Questions

**Q: What's the cheapest way to start?**
A: 1×1 32×32 display (~$70 total). Tight gameplay but works!

**Q: What's the best value?**
A: 2×1 32×32 display (~$130). Balanced experience, reasonable cost.

**Q: Do I need expensive panels?**
A: No. Standard Adafruit or any WS2812B panels work fine.

**Q: Can I upgrade the display later?**
A: Yes! Just buy more panels and update config.h.

**Q: How long to assemble?**
A: 2-4 hours depending on your soldering skills.

**Q: How long to get a game running?**
A: 30 minutes if you have hardware ready!

---

## Bill of Materials (2×1 Default Setup)

| Item | Qty | Cost | Where |
|------|-----|------|-------|
| ESP32-S3 DevKit | 1 | $10 | Amazon |
| Adafruit 32×32 NeoMatrix | 2 | $60 | Adafruit.com |
| 5V/15A Power Supply | 1 | $30 | Amazon |
| MPU6050 Module | 2 | $8 | AliExpress |
| Rotary Encoder | 2 | $6 | AliExpress |
| Wiring & connectors | - | $15 | Amazon |
| **Total** | - | **~$130** | - |

---

## Let's Go! 🚀

1. Get your hardware together
2. Edit config.h for your display
3. Compile the code
4. Upload to ESP32
5. Wire it up
6. Play!

Questions? See the detailed guides:
- [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md)
- [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md)
- [README.md](README.md)

Enjoy! ❄️🎮

