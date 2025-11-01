# Physics and Planets Guide

## Physics System

The game uses simple projectile physics with constant gravitational acceleration and wraparound boundaries:

```
vx(t) = initial_vx  (constant horizontal velocity)
vy(t) = initial_vy + gravity * time  (accelerating downward)
x(t) = x0 + vx * time  (wraps at screen edges)
y(t) = y0 + vy * time + 0.5 * gravity * time²
```

### Key Parameters

- **Gravity**: Adjusts how quickly snowballs fall
- **Max Throw Power**: 20.0 pixels/frame (adjustable in MAX_THROW_POWER)
- **Max Angle**: ±60 degrees from horizontal
- **Frame Rate**: 60 FPS, physics updates every frame
- **Screen Wraparound**: Horizontal (X) axis wraps; vertical (Y) axis deactivates snowball

### Boundary Behavior

**Horizontal (X-axis):**
- Snowballs that exit the left edge (x < 0) appear on the right edge
- Snowballs that exit the right edge (x ≥ 64) appear on the left edge
- Allows powerful throws to loop across the entire screen

**Vertical (Y-axis):**
- Snowballs that fall past the bottom (y ≥ 32) are deactivated
- No wraparound on vertical axis

### Throw Mechanics

The accelerometer on springs controls throws:

1. **Throw Detection**: Triggered when total acceleration exceeds 2.5g
2. **Power**: Derived from Z-axis acceleration (spring compression)
   - Range: 1.0 to 20.0 pixels/frame
3. **Angle**: Derived from X/Y acceleration vectors
   - Range: -60° to +60° (upward = positive angle)

## Planets

Five playable planets with different gravity values. Values are **tuned for gameplay** (not real physics):

### Earth
- **Gravity**: 0.15 pixels/frame²
- **Background**: Dark blue
- **Difficulty**: Medium
- **Characteristics**: Standard gameplay, most predictable
- **Real-world reference**: 9.8 m/s² ≈ 1g

### Moon
- **Gravity**: 0.025 pixels/frame²
- **Background**: Gray
- **Difficulty**: Very Easy
- **Characteristics**: Very floaty, snowballs travel far
- **Real-world reference**: 1.62 m/s² ≈ 0.16g
- **Gameplay tip**: Throws go much farther; high arc throws work well

### Mars
- **Gravity**: 0.06 pixels/frame²
- **Background**: Brown
- **Difficulty**: Easy
- **Characteristics**: Low gravity, extended flight time
- **Real-world reference**: 3.71 m/s² ≈ 0.38g
- **Gameplay tip**: Good for learning; intermediate difficulty

### Jupiter
- **Gravity**: 0.38 pixels/frame²
- **Background**: Orange
- **Difficulty**: Hard
- **Characteristics**: Heavy gravity, short throws required
- **Real-world reference**: 24.79 m/s² ≈ 2.5g
- **Gameplay tip**: Snowballs drop quickly; fast reflexes needed

### Mercury
- **Gravity**: 0.038 pixels/frame²
- **Background**: Silver-gray
- **Difficulty**: Very Easy
- **Characteristics**: Extremely floaty, similar to Moon but slightly different
- **Real-world reference**: 3.7 m/s² ≈ 0.38g
- **Gameplay tip**: Longest throw distances; very forgiving

## Comparing Planets

| Planet | Gravity | Flight Time | Distance | Difficulty |
|--------|---------|------------|----------|-----------|
| Moon   | 0.025   | Very Long  | Very Far | Trivial   |
| Mercury| 0.038   | Very Long  | Very Far | Trivial   |
| Mars   | 0.06    | Long       | Far      | Easy      |
| Earth  | 0.15    | Normal     | Medium   | Medium    |
| Jupiter| 0.38    | Short      | Close    | Hard      |

## Switching Planets

Use serial commands (115200 baud):

- **N**: Next planet (cycles forward)
- **P**: Previous planet (cycles backward)
- **0-4**: Jump to specific planet
  - 0 = Earth
  - 1 = Moon
  - 2 = Mars
  - 3 = Jupiter
  - 4 = Mercury
- **R**: Reset game (keep current planet)

### Example (Arduino Serial Monitor)
```
Send: n
Response: Planet changed to: Moon (Gravity: 0.025)

Send: 3
Response: Planet changed to: Jupiter (Gravity: 0.38)

Send: r
Response: Game reset!
```

## Tuning Physics

To adjust gameplay feel, modify these values in the code:

### Gravity Values
Edit in `planets[]` array:
```c
const PlanetData planets[5] = {
  {"Earth",   0.15f,  ...},  // Change 0.15f to desired gravity
  // ...
};
```

### Throw Sensitivity
- **Acceleration threshold**: Line 242, change `2.5f` in `checkThrow()`
- **Power multiplier**: Line 253, change `2.0f` multiplier
- **Max power cap**: Line 254, change `MAX_THROW_POWER` (default 20.0f)

### Angle Limits
- Change `MAX_ANGLE` (default 60 degrees)

## Physics Notes

1. **Realistic vs Gameplay**: Values are tuned for fun, not accuracy
2. **Display Scale**: Gravity values are in "pixels/frame²" for screen coordinates
3. **Terrain Interaction**: Collisions currently only check height at snowball X position
4. **Air Resistance**: Not implemented (unrealistic but simpler)
5. **Spin Effects**: Not implemented

## Future Enhancements

- [ ] Wind effects (random horizontal force)
- [ ] Curved trajectory based on spin
- [ ] Variable mass snowballs
- [ ] Terrain deformation
- [ ] Air resistance/drag
