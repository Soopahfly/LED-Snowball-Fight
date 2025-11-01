# ❄️ Snowball Fight - LED Matrix Game

A 2-player interactive snowball throwing game on ESP32, controlled via accelerometers mounted on springs and rotary encoders. Play across 5 different planets with varying gravity!

**Current Version:** 0.1.0+effects
**Target Hardware:** ESP32 + 2x 32x32 Adafruit NeoMatrix panels

---

## 🎮 Features

### Gameplay
- **2-Player Local Multiplayer** - Compete against another player in real-time
- **Accelerometer Controls** - Spring-mounted accelerometers detect throw power and angle
- **Rotary Encoder Movement** - Smooth player positioning control
- **Procedurally Generated Terrain** - Unique landscape each game
- **Health System** - 100 HP per player, 10 damage per hit
- **Win Condition** - First player to reduce opponent to 0 HP wins

### Physics & Effects
- **Multi-Planet Gravity System** - 5 planets with different gravity values:
  - 🌍 **Earth** - Normal gameplay (0.15g)
  - 🌙 **Moon** - Very floaty (0.025g)
  - 🔴 **Mars** - Low gravity (0.06g)
  - 🟠 **Jupiter** - Heavy gravity (0.38g)
  - ☿️ **Mercury** - Extremely floaty (0.038g)
- **Wraparound Boundaries** - Throw hard enough and snowballs loop around edges
- **Bounce Physics** - Snowballs bounce off terrain with energy loss
- **Wind System** - Random wind zones push snowballs mid-flight
- **Particle Effects** - Explosion bursts on hits, bounce effects on terrain
- **Screen Shake** - Impact feedback when snowballs hit players

### Visual Polish
- **Planet-Specific Colors** - Background changes per planet
- **Health Bars** - Real-time health display for both players
- **Dynamic Particles** - Burst effects and bounce particles
- **Smooth Animations** - 60 FPS gameplay

---

## 🔧 Hardware Requirements

### Microcontroller
- **ESP32** (or compatible variant)

### Display - Flexible & Scalable
The game supports **any size and arrangement** of LED panels!

**Default Configuration (2x1):**
- **2x Adafruit 32x32 NeoPixel Matrix**
  - WS2812B addressable LEDs
  - Total resolution: 64x32 pixels
  - Requires good 5V power supply (minimum 10A recommended)

**Other Supported Configurations:**
- 1x1: Single 32x32 panel (32x32 game)
- 1x2: Two 32x32 stacked (32x64 game)
- 2x2: Four 32x32 in grid (64x64 game)
- 3x1: Three 32x32 wide (96x32 game)
- 4x1: Four 32x32 wide (128x32 game)
- 16x16 panels, 64x64 panels, custom sizes, etc.

See [config.h](#configuration) for setup details

### Input Sensors
- **2x MPU6050 Accelerometers**
  - One for each player
  - Mounted on springs (DIY or custom enclosure)
  - Detect throw power (Z-axis) and angle (X/Y-axis)

- **2x Rotary Encoders**
  - One for each player
  - Control left/right movement

### Power
- **5V Power Supply** - Minimum 10A (LED matrices draw significant current)
- **USB/Barrel Jack** for ESP32 programming and power

---

## 🔌 Wiring Guide

### LED Matrix
```
ESP32 GPIO 5  → NeoMatrix Data (DIN)
ESP32 GND     → NeoMatrix GND
5V Supply     → NeoMatrix +5V (use dedicated power!)
```

### I2C Accelerometers (Shared Bus)
```
ESP32 GPIO 21 (SDA) → Both MPU6050 SDA
ESP32 GPIO 22 (SCL) → Both MPU6050 SCL
ESP32 GND           → Both MPU6050 GND
ESP32 3.3V          → Both MPU6050 VCC

Address Configuration:
- Player 1: 0x68 (AD0 = GND)
- Player 2: 0x69 (AD0 = 3.3V)
```

### Rotary Encoders
```
Player 1:
  ESP32 GPIO 26 ← Encoder CLK
  ESP32 GPIO 27 ← Encoder DT
  ESP32 GND     ← Encoder GND

Player 2:
  ESP32 GPIO 32 ← Encoder CLK
  ESP32 GPIO 33 ← Encoder DT
  ESP32 GND     ← Encoder GND
```

---

## 📦 Dependencies

Install via Arduino Library Manager:
- `Adafruit_NeoPixel`
- `Adafruit_NeoMatrix`
- `MPU6050` (by InvenSense)

Or add to `platformio.ini`:
```ini
lib_deps =
    adafruit/Adafruit NeoPixel
    adafruit/Adafruit NeoMatrix
    jrowberg/MPU6050
```

---

## ⚙️ Configuration

### LED Matrix Scaling

Edit [config.h](config.h) to customize your display:

```cpp
// Panel dimensions
#define PANEL_WIDTH 32      // Pixel width of each panel
#define PANEL_HEIGHT 32     // Pixel height of each panel

// Panel grid layout
#define PANELS_HORIZONTAL 2 // Number of panels left-to-right
#define PANELS_VERTICAL 1   // Number of panels top-to-bottom
```

**Examples:**

**Single Panel (32x32):**
```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 1
#define PANELS_VERTICAL 1
// Result: 32x32 game area
```

**Wide Layout (96x32):**
```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 3
#define PANELS_VERTICAL 1
// Result: 96x32 game area
```

**2x2 Grid (64x64):**
```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 2
#define PANELS_VERTICAL 2
// Result: 64x64 game area (4 panels total)
```

**Large Single Panel (64x64):**
```cpp
#define PANEL_WIDTH 64
#define PANEL_HEIGHT 64
#define PANELS_HORIZONTAL 1
#define PANELS_VERTICAL 1
// Result: 64x64 game area
```

The game **automatically scales** to your configuration:
- Player positions adapt to board width
- Terrain generation scales to board size
- Physics remain balanced across all sizes
- No code changes needed - just edit config.h!

---

## 🚀 Getting Started

### 1. Upload the Code
```bash
# Using Arduino IDE
# File → Open → snowball_fight.ino
# Select ESP32 board and COM port
# Upload

# Or using PlatformIO
platformio run -t upload
```

### 2. Hardware Assembly
- Mount both accelerometers on springs in controllers
- Connect rotary encoders to GPIO pins
- Wire LED matrices in series
- Connect 5V power supply

### 3. Serial Control
Open Serial Monitor (115200 baud) to:
- **N** - Next planet (cycles through all 5)
- **P** - Previous planet
- **0-4** - Jump to specific planet
- **R** - Reset game (keeps current planet)

### 4. Play!
- Compress spring to throw (power increases with spring force)
- Angle your throw with X/Y acceleration
- Use rotary encoder to move left/right
- First player to 0 HP loses

---

## ⚙️ Configuration

Edit physics and performance in [config.h](config.h):

```cpp
// Physics
#define MAX_THROW_POWER 20.0f       // Base throw distance
#define MAX_ANGLE 60                 // ±degrees from horizontal
#define GRAVITY_EARTH 0.15f          // Base gravity value
#define THROW_DETECTION_G 2.5f       // G-force threshold to trigger throw

// Performance
#define MAX_PARTICLES 32   // Increase for more visual effects
#define MAX_WIND_ZONES 4   // Increase for more wind variety
#define LED_BRIGHTNESS 255 // 0-255, lower = less power draw
```

### Advanced Tuning

**In [snowball_fight.ino](snowball_fight.ino):**
- **Throw sensitivity:** Modify `THROW_DETECTION_G` in config.h
- **Gravity values:** Edit planet definitions (line ~51)
- **Encoder sensitivity:** Adjust `int newPos = encoderCount / 2` (line ~359)
- **Bounce physics:** Change coefficient `0.6f` (line ~243)
- **Wind strength:** Modify `random(-6, 7) * 0.5f` in `spawnWindZone()`

---

## 📚 Documentation

- **[CHANGELOG.md](CHANGELOG.md)** - Version history and features
- **[PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md)** - Detailed physics guide
- **[PROJECT_INFO.md](PROJECT_INFO.md)** - Project structure and roadmap
- **[version.h](version.h)** - Version information

---

## 🎨 Visual Design

### Colors
- **Player 1:** Blue (0, 100, 255)
- **Player 2:** Orange (255, 100, 0)
- **Snowballs:** Light gray (200, 200, 200)
- **Terrain:** Dark gray (100, 100, 100)
- **Planet Indicator:** Yellow (255, 255, 100)

### Particle Effects
- **Hit explosions:** Player colors, 12 particles bursting outward
- **Bounce effects:** Snowball color, 6 particles on terrain collision
- **All particles:** Affected by current planet gravity

---

## 🛠️ Troubleshooting

### No display output
- Check LED matrix power supply (needs good 5V)
- Verify GPIO 5 connected to data line
- Test with Adafruit example first

### Accelerometers not reading
- Check I2C addresses (use I2C scanner)
- Verify pull-up resistors on SDA/SCL (typically 4.7kΩ)
- Ensure both MPU6050s at different addresses (0x68 and 0x69)

### Throws not detecting
- Open Serial Monitor and check accelerometer values
- Increase throw detection threshold in `checkThrow()`
- Check spring force/responsiveness

### Rotary encoders skipping
- Add debouncing delay
- Check encoder wiring (CLK/DT order)
- Verify encoder is compatible with interrupt pins

---

## 🔮 Future Roadmap

- [ ] Sound effects (piezo buzzer)
- [ ] Power-ups (shield, double damage, speed boost)
- [ ] Asteroid obstacles on certain planets
- [ ] Multiple game modes (time attack, survival)
- [ ] Combo counter and scoring
- [ ] Victory animation
- [ ] Web-based configuration tool
- [ ] Level editor for terrain generation

---

## 📝 License

This project is open source. Feel free to modify and improve!

---

## 🤝 Contributing

Have improvements or bug fixes? Feel free to:
1. Test on your hardware
2. Report issues on GitHub
3. Submit pull requests with enhancements

---

## 🎯 Game Tips

### For Beginners
- Start on **Earth** for normal difficulty
- **Moon** and **Mercury** are forgiving with long throws
- Use terrain to your advantage - hide behind peaks

### For Advanced Players
- Master **Jupiter's** high gravity for precise, fast throws
- Use **wind zones** to curve your throws
- Bounce off terrain for trick shots
- Wraparound throws to catch opponents off-guard

### Strategy
- Watch your opponent's position
- Adjust throw angle for terrain obstacles
- Bounce off hills to lob over obstacles
- Use high-angle throws on low-gravity planets

---

## 📞 Support

Having issues? Check:
1. [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md) for game mechanics
2. Hardware wiring against [Hardware Requirements](#-hardware-requirements)
3. Serial output for debug messages
4. GitHub Issues for known problems

---

**Made with ❄️ for 2-player arcade fun!**
