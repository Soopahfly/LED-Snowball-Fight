# Snowball Fight - Project Information

## Overview
A 2-player interactive snowball fight game on ESP32 with 2x 32x32 LED matrix display and motion-controlled throwing mechanics.

## Current Version
**v0.1.0** (Release Date: 2025-11-01)

## Project Structure
```
Snowball Fight/
├── snowball_fight.ino      # Main game code
├── version.h               # Version definitions
├── CHANGELOG.md            # Version history and changes
├── PROJECT_INFO.md         # This file
└── README.md               # Setup and wiring guide (if exists)
```

## Hardware Requirements
- **Microcontroller**: ESP32
- **Display**: 2x Adafruit 32x32 NeoPixel Matrix (WS2812B)
- **Input Sensors**: 2x MPU6050 Accelerometers + 2x Rotary Encoders
- **Power Supply**: 5V minimum 10A (LED matrices are power-hungry)

## Dependencies
- `Wire.h` (built-in)
- `Adafruit_NeoPixel.h`
- `Adafruit_NeoMatrix.h`
- `MPU6050.h`

## Version History Quick Reference
- **v0.1.0** (2025-11-01) - Initial release with core gameplay

## How to Update Version
1. Edit `version.h` and update `VERSION_MAJOR`, `VERSION_MINOR`, or `VERSION_PATCH`
2. Update `BUILD_DATE` in `version.h`
3. Add entry to top of `CHANGELOG.md` with changes
4. Follow [Semantic Versioning](https://semver.org/):
   - **MAJOR**: Breaking changes to gameplay/hardware interface
   - **MINOR**: New features (backwards compatible)
   - **PATCH**: Bug fixes

## Development Roadmap (Future Versions)
- [ ] v0.2.0: Better terrain collision, sound effects
- [ ] v0.3.0: Power-ups and special snowball types
- [ ] v0.4.0: Multiple game modes (survival, time attack)
- [ ] v1.0.0: Full release with optimized rendering

## Contributing Notes
- Keep changelog up-to-date with all changes
- Update version.h when releasing
- Test on actual hardware before committing
- Document any hardware modifications needed
