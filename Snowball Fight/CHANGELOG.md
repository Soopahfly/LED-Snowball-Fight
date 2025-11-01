# Changelog

All notable changes to the Snowball Fight game will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- **Flexible LED matrix scaling system** - Support for any panel size and arrangement
- New [config.h](config.h) configuration file for hardware setup
- Support for custom panel dimensions (32x32, 16x16, 64x64, etc.)
- Support for multiple panel grids (1x1, 2x1, 2x2, 3x1, 4x1, etc.)
- Automatic game scaling based on display size
- Multi-planet gravity system with 5 planets (Earth, Moon, Mars, Jupiter, Mercury)
- Planet-specific background colors for visual feedback
- Serial commands to switch planets (N=next, P=previous, 0-4=specific planet)
- Dynamic gravity values affect snowball trajectories
- Yellow planet indicator on UI
- **Wraparound physics**: Snowballs that exit left/right sides loop to the opposite side
- **Particle effects system**: Explosion bursts on hits and bounces
- **Bounce mechanic**: Snowballs bounce off terrain with 60% energy retention
- **Wind system**: Random wind zones push snowballs mid-flight
- **Screen shake**: Impact feedback on player hits (3-frame duration)
- **Hit effects**: Colorful particle explosions when snowballs hit players
- **Bounce particles**: Visual feedback when snowballs bounce off terrain

### Changed
- LED matrix configuration now centralized in [config.h](config.h)
- Player positions dynamically calculated based on game width
- Terrain generation scales to display size
- Physics gravity is now dynamic based on selected planet
- Health bars reduced from 16 to 14 pixels to accommodate planet indicator
- Snowball out-of-bounds detection updated: only deactivates on bottom edge, wraps on sides
- Render function now applies screen shake offset to all game elements
- Snowball drawing includes shake offset for coherent impact feedback
- Player drawing simplified and made display-size agnostic

## [0.1.0] - 2025-11-01

### Added
- Initial game implementation for ESP32
- Two-player snowball throwing mechanics using accelerometer input
- Player movement control via rotary encoders
- Procedurally generated terrain with sine-wave and random variation
- Gravity-based projectile physics for snowballs
- Collision detection for player hits and terrain
- Health system (100 HP per player, 10 damage per hit)
- LED matrix display rendering (64x32 resolution)
- Color-coded players (Blue P1, Orange P2)
- Health bars UI at top of screen
- Serial debug output for troubleshooting

### Technical Details
- Target: ESP32 with 2x 32x32 Adafruit NeoMatrix panels
- Input: 2x MPU6050 accelerometers + 2x rotary encoders
- Game loop: 60 FPS
- Physics timestep: Capped at 0.1s for stability

### Known Issues
- Terrain collision is simplified (only checks height at snowball X position)
- Player sprites are basic 3x3 pixel blocks
- No sound effects implemented yet
- Throw detection requires manual tuning for accelerometer sensitivity
- Display rendering could be optimized for better performance
