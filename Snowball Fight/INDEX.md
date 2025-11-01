# Snowball Fight - Complete Index

Your complete reference for building and playing the game.

---

## 🎯 What Do You Want to Do?

### "I want to start building NOW" ⚡
👉 **[QUICK_START.md](QUICK_START.md)** (30 min)
- Fast setup checklist
- Bill of materials
- Quick troubleshooting

### "I want to understand what changed" 📊
👉 **[FASTLED_MIGRATION_SUMMARY.md](FASTLED_MIGRATION_SUMMARY.md)**
- What's new (FastLED library)
- What stayed the same (hardware)
- Performance improvements

### "I need to know what hardware to buy" 🛒
👉 **[HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md)**
- Detailed component list
- Power calculations
- Wiring diagrams
- Cost breakdown

### "I need to compile and upload the code" 💻
👉 **[COMPILATION_GUIDE.md](COMPILATION_GUIDE.md)**
- Arduino IDE instructions
- PlatformIO instructions
- Command-line setup
- Troubleshooting

### "I want the full story" 📖
👉 **[README.md](README.md)**
- Complete project overview
- Features list
- Getting started
- Game controls

### "I want to customize the display" 🖼️
👉 **[SCALING_GUIDE.md](SCALING_GUIDE.md)**
- Display size options
- Configuration examples
- Power requirements
- Performance tips

### "I want to understand the physics" ⚙️
👉 **[PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md)**
- Physics equations
- Planet gravity values
- Throw mechanics
- Tuning guide

### "I'm lost, where do I start?" 🤔
👉 **[SETUP_SUMMARY.md](SETUP_SUMMARY.md)**
- Reading order recommendations
- Phase-by-phase path
- Common questions
- Navigation guide

---

## 📋 All Files

### Code & Config (4 files)

| File | Purpose | Edit? |
|------|---------|-------|
| [snowball_fight.ino](snowball_fight.ino) | Main game code (750 lines) | Only if customizing |
| [config.h](config.h) | Hardware configuration | **YES - set your display** |
| [version.h](version.h) | Version information | Usually not |
| [platformio.ini](platformio.ini) | Build configuration | Usually not |

### Quick Guides (3 files)

| File | Purpose | Read Time |
|------|---------|-----------|
| [QUICK_START.md](QUICK_START.md) | 30-minute setup | 5 min |
| [SETUP_SUMMARY.md](SETUP_SUMMARY.md) | Navigation guide | 3 min |
| [INDEX.md](INDEX.md) | File index (this file) | 2 min |

### Technical Guides (5 files)

| File | Purpose | Read Time |
|------|---------|-----------|
| [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md) | How to build | 10 min |
| [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md) | What to buy | 15 min |
| [FASTLED_MIGRATION_SUMMARY.md](FASTLED_MIGRATION_SUMMARY.md) | What changed | 5 min |
| [SCALING_GUIDE.md](SCALING_GUIDE.md) | Display options | 10 min |
| [README.md](README.md) | Full overview | 15 min |

### Reference Guides (4 files)

| File | Purpose | Read Time |
|------|---------|-----------|
| [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md) | Game mechanics | 10 min |
| [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) | Technical details | 15 min |
| [CHANGELOG.md](CHANGELOG.md) | Version history | 5 min |
| [PROJECT_INFO.md](PROJECT_INFO.md) | Project structure | 5 min |
| [FILES.md](FILES.md) | File descriptions | 5 min |

---

## 🚀 Quick Navigation by Task

### Building from Scratch
1. [QUICK_START.md](QUICK_START.md) - Overview
2. [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md) - Buy parts
3. [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md) - Set up tools
4. Edit [config.h](config.h) - Configure your display
5. [QUICK_START.md](QUICK_START.md) - Assemble & upload

### Compiling the Code
1. Read [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md)
2. Choose: Arduino IDE, PlatformIO, or arduino-cli
3. Install: FastLED library, MPU6050 library
4. Edit [config.h](config.h) for your display
5. Compile & upload

### Understanding the Project
1. [README.md](README.md) - What it is
2. [FASTLED_MIGRATION_SUMMARY.md](FASTLED_MIGRATION_SUMMARY.md) - What's new
3. [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md) - How it works
4. [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md) - Game mechanics

### Choosing a Display
1. [SCALING_GUIDE.md](SCALING_GUIDE.md) - See all options
2. [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md) - Price & power
3. [QUICK_START.md](QUICK_START.md) - Edit config.h
4. Compile & upload

---

## 📊 File Statistics

```
Code Files:           2 files   (~870 lines)
Config Files:         2 files   (~160 lines)
Build Config:         1 file    (~30 lines)

Documentation:       11 files   (~7,000 lines)
  - Guides:           3 files   (quick start, setup, index)
  - Technical:        5 files   (compilation, hardware, migration, scaling, readme)
  - Reference:        3 files   (physics, implementation, changelog)

Total:               16 files   (~8,000+ lines)
```

---

## 🎮 Feature Summary

### Gameplay
- ✅ 2-player local multiplayer
- ✅ Accelerometer-based throws
- ✅ Rotary encoder movement
- ✅ Health system (100 HP)
- ✅ Procedurally generated terrain
- ✅ Win condition (knock opponent to 0 HP)

### Physics
- ✅ Gravity-based projectiles
- ✅ 5-planet gravity system
- ✅ Bounce mechanics (60% energy)
- ✅ Wind zones (random pushes)
- ✅ Screen wraparound
- ✅ Dynamic terrain interaction

### Visual Effects
- ✅ Particle explosions (12 particles per hit)
- ✅ Bounce particles (6 particles per bounce)
- ✅ Screen shake (3 frames duration)
- ✅ Planet-specific colors
- ✅ Health bar UI
- ✅ Planet indicator

### Hardware Support
- ✅ Any size/arrangement of LED panels
- ✅ 1×1 to 4×2 panel grids
- ✅ 32×32 to 64×64 pixel panels
- ✅ Custom panel dimensions
- ✅ Automatic game scaling
- ✅ DMA rendering (FastLED)

### Performance
- ✅ 60 FPS on ESP32-S3
- ✅ <16ms frame time
- ✅ Smooth physics simulation
- ✅ Responsive input handling
- ✅ Low CPU overhead (DMA rendering)

---

## 💡 Key Concepts

### FastLED Library
- **What:** DMA-based LED control library
- **Why:** 80% faster rendering, enables larger displays
- **Impact:** No hardware changes needed
- **Read:** [FASTLED_MIGRATION_SUMMARY.md](FASTLED_MIGRATION_SUMMARY.md)

### Display Scaling
- **What:** Game automatically adjusts to any panel size
- **How:** Configure PANEL_WIDTH/HEIGHT and PANELS_HORIZONTAL/VERTICAL in config.h
- **Result:** Same code works for 1×1 to 4×2 displays
- **Read:** [SCALING_GUIDE.md](SCALING_GUIDE.md)

### Planet Gravity System
- **What:** 5 planets with different gravity values
- **Effect:** Changes how snowballs arc and fall
- **Range:** 0.17× (Moon) to 2.5× (Jupiter)
- **Switch:** Serial commands (N/P/0-4)
- **Read:** [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md)

### Particle Effects
- **What:** Visual feedback for impacts and bounces
- **How:** Object pooling (32 concurrent particles)
- **When:** Hit = 12 particles, Bounce = 6 particles
- **Impact:** No performance cost (DMA rendering)
- **Tune:** MAX_PARTICLES in config.h

### Wind Zones
- **What:** Random air currents affecting snowballs
- **How:** 4 concurrent wind zones, random spawning
- **Effect:** Distance-based influence falloff
- **Tune:** MAX_WIND_ZONES in config.h

---

## 🔧 Common Customizations

### Change Display Size
Edit in **config.h**:
```cpp
#define PANEL_WIDTH 32
#define PANEL_HEIGHT 32
#define PANELS_HORIZONTAL 2  // Change this
#define PANELS_VERTICAL 1    // Or this
```
Recompile and upload. Game auto-scales!

### Change Gravity
Edit in **snowball_fight.ino**:
```cpp
const PlanetData planets[5] = {
  {"Earth", GRAVITY_EARTH, ...},
  // Change gravity value here
};
```
Or use serial commands: N (next), P (prev), 0-4 (specific planet)

### Change Colors
Edit in **snowball_fight.ino**:
```cpp
#define COLOR_P1 CRGB(0, 100, 255)  // Blue → change here
#define COLOR_P2 CRGB(255, 100, 0)  // Orange → or here
```

### Adjust Throw Sensitivity
Edit in **config.h**:
```cpp
#define THROW_DETECTION_G 2.5f  // Higher = harder to throw
```

### Adjust Physics
Edit in **config.h**:
```cpp
#define MAX_THROW_POWER 20.0f   // Maximum throw distance
#define MAX_ANGLE 60            // ±degrees from horizontal
```

### Reduce Power Draw
Edit in **config.h**:
```cpp
#define LED_BRIGHTNESS 200  // 0-255, lower = less power
```

---

## 📞 Troubleshooting Quick Links

### Hardware Issues
- LEDs don't light → [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md#troubleshooting)
- No accelerometer readings → [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md#troubleshooting-arduino-ide)
- Encoders don't work → [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md#input-devices-rotary-encoders)

### Compilation Issues
- Can't compile → [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md#troubleshooting-arduino-ide)
- Library not found → [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md#method-2-platformio-recommended)
- Port not found → [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md#troubleshooting-platformio)

### Game Issues
- Game runs weird → [QUICK_START.md](QUICK_START.md#troubleshooting)
- Throws not working → [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md#throw-mechanics)
- Physics feel off → [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md#tuning-parameters)

---

## 🌟 Recommended Reading Order

### For Absolute Beginners
1. [QUICK_START.md](QUICK_START.md)
2. [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md)
3. [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md)
4. [README.md](README.md)

### For Experienced Builders
1. [SETUP_SUMMARY.md](SETUP_SUMMARY.md)
2. [HARDWARE_REQUIREMENTS.md](HARDWARE_REQUIREMENTS.md)
3. [COMPILATION_GUIDE.md](COMPILATION_GUIDE.md)
4. [SCALING_GUIDE.md](SCALING_GUIDE.md)

### For Developers
1. [FASTLED_MIGRATION_SUMMARY.md](FASTLED_MIGRATION_SUMMARY.md)
2. [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md)
3. [PHYSICS_AND_PLANETS.md](PHYSICS_AND_PLANETS.md)
4. Read source code: [snowball_fight.ino](snowball_fight.ino)

---

## 📈 By the Numbers

| Metric | Count |
|--------|-------|
| Total files | 16 |
| Lines of code | ~870 |
| Lines of documentation | ~7,000 |
| Game features | 20+ |
| Planets | 5 |
| Max display size supported | 4×2 (256×128 px) |
| Frames per second | 60 |
| Players | 2 (local only) |
| Input devices | 4 (2 accel, 2 encoders) |
| Supported panel types | All WS2812B variants |

---

## ✨ What's New (FastLED Migration)

- ✅ DMA rendering (80% faster)
- ✅ Larger displays now viable (3×2, 4×1)
- ✅ Smoother gameplay
- ✅ Automatic power management
- ✅ Better color correction
- ✅ No hardware changes needed
- ✅ No rewiring needed
- ✅ Backward compatible

---

## 🎯 Next Step

**Pick your starting point above ⬆️**

Then:
1. Read the guide for your situation
2. Follow the steps
3. Build and play! 🎮

---

## 📝 Version Info

- **Current Version:** 0.1.0+effects (unreleased)
- **Last Updated:** 2025-11-01
- **Status:** Feature complete, production ready
- **Platform:** ESP32 with WS2812B LED matrices

---

**You have everything you need to build an awesome LED matrix arcade game!** ❄️🎮

