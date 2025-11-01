#ifndef CONFIG_H
#define CONFIG_H

// ===== LED MATRIX CONFIGURATION =====
// Flexible panel configuration - customize for your hardware setup

// Panel dimensions
#define PANEL_WIDTH 32      // Width of each LED panel (pixels)
#define PANEL_HEIGHT 32     // Height of each LED panel (pixels)

// Panel grid layout - how many panels in each dimension
#define PANELS_HORIZONTAL 2 // Number of panels left-to-right
#define PANELS_VERTICAL 1   // Number of panels top-to-bottom

// Calculated game dimensions (automatically calculated from above)
#define GAME_WIDTH (PANEL_WIDTH * PANELS_HORIZONTAL)
#define GAME_HEIGHT (PANEL_HEIGHT * PANELS_VERTICAL)

// LED matrix pin configuration
#define MATRIX_PIN 5        // GPIO pin for NeoMatrix data line
#define LED_BRIGHTNESS 255  // 0-255, lower = less power draw but dimmer

// ===== SUPPORTED CONFIGURATIONS =====
// Examples of common setups:

// 1x1 Panel (single 32x32):
//    #define PANELS_HORIZONTAL 1
//    #define PANELS_VERTICAL 1
//    Result: 32x32 game area

// 2x1 Panel (two 32x32 side-by-side) - DEFAULT:
//    #define PANELS_HORIZONTAL 2
//    #define PANELS_VERTICAL 1
//    Result: 64x32 game area

// 1x2 Panel (two 32x32 stacked):
//    #define PANELS_HORIZONTAL 1
//    #define PANELS_VERTICAL 2
//    Result: 32x64 game area

// 2x2 Panel (four 32x32 in grid):
//    #define PANELS_HORIZONTAL 2
//    #define PANELS_VERTICAL 2
//    Result: 64x64 game area

// 3x1 Panel (three 32x32 wide):
//    #define PANELS_HORIZONTAL 3
//    #define PANELS_VERTICAL 1
//    Result: 96x32 game area

// 4x1 Panel (four 32x32 wide):
//    #define PANELS_HORIZONTAL 4
//    #define PANELS_VERTICAL 1
//    Result: 128x32 game area

// Different panel sizes:
// For 16x16 panels:
//    #define PANEL_WIDTH 16
//    #define PANEL_HEIGHT 16
//    #define PANELS_HORIZONTAL 4
//    #define PANELS_VERTICAL 2
//    Result: 64x32 game area

// For 64x64 panels:
//    #define PANEL_WIDTH 64
//    #define PANEL_HEIGHT 64
//    #define PANELS_HORIZONTAL 1
//    #define PANELS_VERTICAL 1
//    Result: 64x64 game area

// ===== MATRIX TYPE CONFIGURATION =====
// Choose based on your specific panel arrangement
// This tells NeoMatrix how your panels are physically connected

// For side-by-side horizontal arrangement (2x1):
#define MATRIX_CONFIG (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + \
                       NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE)

// For vertical stacked arrangement (1x2):
// #define MATRIX_CONFIG (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + \
//                        NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE)

// For 2x2 grid:
// #define MATRIX_CONFIG (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + \
//                        NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE)

// ===== GAME PHYSICS CONSTANTS =====
// These can be tuned based on your display size for better gameplay

#define MAX_THROW_POWER 20.0f    // Base power (scales with display)
#define MAX_ANGLE 60             // ±degrees from horizontal
#define GRAVITY_EARTH 0.15f       // Base gravity value
#define THROW_DETECTION_G 2.5f    // G-force threshold to trigger throw

// ===== PERFORMANCE TUNING =====
#define MAX_PARTICLES 32   // Increase for more visual effects
#define MAX_WIND_ZONES 4   // Increase for more wind variety
#define FPS 60             // Target frames per second

#endif // CONFIG_H
