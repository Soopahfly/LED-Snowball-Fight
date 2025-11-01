#include <Wire.h>
#include <MPU6050.h>  // Accelerometer library
#include <FastLED.h>  // DMA-based LED control
#include "version.h"
#include "config.h"

// ===== PIN DEFINITIONS =====
#define ACCEL_P1_ADDR 0x68  // MPU6050 for Player 1
#define ACCEL_P2_ADDR 0x69  // MPU6050 for Player 2 (with AD0 pulled high)
#define ENCODER_P1_CLK 26
#define ENCODER_P1_DT 27
#define ENCODER_P2_CLK 32
#define ENCODER_P2_DT 33

// ===== DISPLAY SETUP =====
// FastLED - DMA-based NeoPixel control
#define NUM_LEDS (GAME_WIDTH * GAME_HEIGHT)
CRGB leds[NUM_LEDS];

// ===== COLOR DEFINITIONS =====
// FastLED uses CRGB format
#define COLOR_P1 CRGB(0, 100, 255)       // Blue
#define COLOR_P2 CRGB(255, 100, 0)       // Orange
#define COLOR_SNOW CRGB(200, 200, 200)   // Light gray
#define COLOR_TERRAIN CRGB(100, 100, 100) // Dark gray
#define COLOR_BG CRGB(10, 10, 30)         // Dark blue background
#define COLOR_PLANET CRGB(255, 255, 100)  // Yellow planet indicator

// ===== GAME CONSTANTS (Dynamic based on display size) =====
// Player starting positions - adjust based on game width
#define PLAYER1_START_X (GAME_WIDTH / 8)           // 1/8 from left
#define PLAYER2_START_X (GAME_WIDTH - GAME_WIDTH / 8) // 1/8 from right

// ===== PLANET DEFINITIONS =====
enum Planet {
  EARTH = 0,
  MOON = 1,
  MARS = 2,
  JUPITER = 3,
  MERCURY = 4
};

struct PlanetData {
  const char* name;
  float gravity;      // pixels/frame^2
  CRGB color;         // Background color
};

const PlanetData planets[5] = {
  {"Earth",   GRAVITY_EARTH,       CRGB(10, 10, 30)},      // Dark blue - normal gameplay
  {"Moon",    GRAVITY_EARTH * 0.17f, CRGB(50, 50, 50)},      // Gray - very floaty
  {"Mars",    GRAVITY_EARTH * 0.4f,  CRGB(139, 69, 19)},     // Brown - low grav
  {"Jupiter", GRAVITY_EARTH * 2.5f,  CRGB(200, 100, 50)},    // Orange - high gravity
  {"Mercury", GRAVITY_EARTH * 0.25f, CRGB(128, 128, 128)}    // Silver-gray - very floaty
};

// Global game variables
Planet currentPlanet = EARTH;
float gravity = GRAVITY_EARTH;

// ===== DATA STRUCTURES =====
struct Player {
  float x;
  int health;
  int score;
  int encoderPos;
};

struct Snowball {
  float x, y;
  float vx, vy;
  bool active;
  int owner;  // 0 for player 1, 1 for player 2
};

struct Terrain {
  uint8_t heights[GAME_WIDTH];
};

struct AccelReading {
  float x, y, z;
};

// ===== EFFECTS STRUCTURES =====
#define MAX_PARTICLES 32
#define MAX_WIND_ZONES 4

struct Particle {
  float x, y;
  float vx, vy;
  int lifetime;      // frames remaining
  CRGB color;
  bool active;
};

struct WindZone {
  float x, y;        // Center position
  float strength;    // Wind force magnitude (-10 to 10)
  int lifetime;      // frames remaining
  bool active;
};

struct ScreenShake {
  int intensity;     // Shake amount in pixels
  int duration;      // frames remaining
};

// ===== GLOBAL VARIABLES =====
Player player1, player2;
Snowball snowballs[2];  // One per player
Terrain terrain;
AccelReading accel1, accel2;
MPU6050 mpu1, mpu2;
unsigned long lastUpdateTime = 0;
int gameState = 0;  // 0 = playing, 1 = p1 wins, 2 = p2 wins
unsigned long planetSwitchTime = 0;

// Effects
Particle particles[MAX_PARTICLES];
WindZone winds[MAX_WIND_ZONES];
ScreenShake screenShake = {0, 0};
unsigned long windSpawnTimer = 0;

// Encoder state
volatile int encoder1Count = 0;
volatile int encoder2Count = 0;

// ===== INTERRUPT HANDLERS =====
void IRAM_ATTR encoder1ISR() {
  int clk = digitalRead(ENCODER_P1_CLK);
  int dt = digitalRead(ENCODER_P1_DT);
  if (clk == dt) {
    encoder1Count++;
  } else {
    encoder1Count--;
  }
}

void IRAM_ATTR encoder2ISR() {
  int clk = digitalRead(ENCODER_P2_CLK);
  int dt = digitalRead(ENCODER_P2_DT);
  if (clk == dt) {
    encoder2Count++;
  } else {
    encoder2Count--;
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\n=== SNOWBALL FIGHT ===");
  Serial.printf("Version: %s\n", VERSION_STRING);
  Serial.printf("Build Date: %s\n", BUILD_DATE);
  Serial.println("Starting...");

  // Initialize FastLED with DMA
  FastLED.addLeds<WS2812B, MATRIX_PIN, GRB>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVolts(5, 60);  // 60A safe power limit
  FastLED.setBrightness(LED_BRIGHTNESS);

  // Fill with background color
  fill_solid(leds, NUM_LEDS, COLOR_BG);
  FastLED.show();

  // Initialize I2C for accelerometers
  Wire.begin();
  delay(100);

  // Initialize accelerometers
  if (!mpu1.begin(ACCEL_P1_ADDR)) {
    Serial.println("MPU6050 #1 not found!");
  } else {
    Serial.println("MPU6050 #1 initialized");
  }

  if (!mpu2.begin(ACCEL_P2_ADDR)) {
    Serial.println("MPU6050 #2 not found!");
  } else {
    Serial.println("MPU6050 #2 initialized");
  }

  // Initialize encoders
  pinMode(ENCODER_P1_CLK, INPUT_PULLUP);
  pinMode(ENCODER_P1_DT, INPUT_PULLUP);
  pinMode(ENCODER_P2_CLK, INPUT_PULLUP);
  pinMode(ENCODER_P2_DT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_P1_CLK), encoder1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_P2_CLK), encoder2ISR, CHANGE);

  // Initialize game state
  initializeGame();
}

// ===== EFFECTS SYSTEM =====
void spawnParticles(float x, float y, uint32_t color, int count, float speedVariance) {
  for (int i = 0; i < count && i < MAX_PARTICLES; i++) {
    // Find first inactive particle slot
    for (int j = 0; j < MAX_PARTICLES; j++) {
      if (!particles[j].active) {
        particles[j].x = x + random(-2, 3);
        particles[j].y = y + random(-2, 3);

        // Random burst direction
        float angle = (i * 360.0f / count) + random(-10, 11);
        float rad = radians(angle);
        float speed = 1.0f + (random(0, 100) / 100.0f) * speedVariance;

        particles[j].vx = cos(rad) * speed;
        particles[j].vy = sin(rad) * speed;
        particles[j].lifetime = 20 + random(0, 10);  // 0.3-0.5 seconds
        particles[j].color = color;
        particles[j].active = true;
        break;
      }
    }
  }
}

void updateParticles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!particles[i].active) continue;

    // Apply gravity to particles
    particles[i].vy += gravity * 0.5f;

    // Update position
    particles[i].x += particles[i].vx;
    particles[i].y += particles[i].vy;

    // Decrease lifetime
    particles[i].lifetime--;
    if (particles[i].lifetime <= 0) {
      particles[i].active = false;
    }

    // Out of bounds check
    if (particles[i].x < 0 || particles[i].x >= GAME_WIDTH || particles[i].y >= GAME_HEIGHT) {
      particles[i].active = false;
    }
  }
}

void spawnWindZone() {
  // Randomly spawn a wind zone with occasional winds
  if (random(0, 100) < 15) {  // 15% chance each frame
    for (int i = 0; i < MAX_WIND_ZONES; i++) {
      if (!winds[i].active) {
        winds[i].x = random(10, GAME_WIDTH - 10);
        winds[i].y = 8;  // Upper area where snowballs fly
        winds[i].strength = random(-6, 7) * 0.5f;  // -3 to 3 strength
        winds[i].lifetime = 120;  // 2 seconds
        winds[i].active = true;
        break;
      }
    }
  }
}

void updateWindZones() {
  for (int i = 0; i < MAX_WIND_ZONES; i++) {
    if (!winds[i].active) continue;

    winds[i].lifetime--;
    if (winds[i].lifetime <= 0) {
      winds[i].active = false;
    }
  }
}

void applyWind(Snowball* ball) {
  // Apply wind force to active snowballs
  for (int i = 0; i < MAX_WIND_ZONES; i++) {
    if (!winds[i].active) continue;

    // Only apply wind if snowball is near the wind zone
    float dist = abs(ball->x - winds[i].x);
    if (dist < 20) {
      float influence = 1.0f - (dist / 20.0f);  // Falloff with distance
      ball->vx += winds[i].strength * influence * 0.1f;
    }
  }
}

void triggerScreenShake(int intensity) {
  screenShake.intensity = intensity;
  screenShake.duration = intensity;  // Shake for N frames
}

// ===== MAIN LOOP =====
void loop() {
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastUpdateTime) / 1000.0f;
  if (deltaTime > 0.1f) deltaTime = 0.1f;  // Cap delta time
  lastUpdateTime = currentTime;

  // Check for serial commands to switch planets
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'n' || cmd == 'N') {
      nextPlanet();
    } else if (cmd == 'p' || cmd == 'P') {
      previousPlanet();
    } else if (cmd >= '0' && cmd <= '4') {
      setPlanet((Planet)(cmd - '0'));
    } else if (cmd == 'r' || cmd == 'R') {
      initializeGame();
      Serial.println("Game reset!");
    }
  }

  if (gameState == 0) {  // Playing
    readAccelerometers();
    updatePlayerPositions();
    updateSnowballs(deltaTime);
    applyWindToSnowballs();
    checkCollisions();
    updateTerrain();

    // Update effects
    updateParticles();
    updateWindZones();
    spawnWindZone();

    // Update screen shake
    if (screenShake.duration > 0) {
      screenShake.duration--;
    }

    render();
  }

  delay(16);  // ~60 FPS
}

// ===== INPUT FUNCTIONS =====
void readAccelerometers() {
  int16_t ax, ay, az;

  // Read player 1 accelerometer
  mpu1.getAcceleration(&ax, &ay, &az);
  accel1.x = ax / 16384.0f;
  accel1.y = ay / 16384.0f;
  accel1.z = az / 16384.0f;

  // Read player 2 accelerometer
  mpu2.getAcceleration(&ax, &ay, &az);
  accel2.x = ax / 16384.0f;
  accel2.y = ay / 16384.0f;
  accel2.z = az / 16384.0f;

  Serial.printf("P1: %.2f, %.2f, %.2f | P2: %.2f, %.2f, %.2f\n",
    accel1.x, accel1.y, accel1.z, accel2.x, accel2.y, accel2.z);
}

void updatePlayerPositions() {
  // Update player 1 position from encoder
  int newPos1 = encoder1Count / 2;  // Scale down encoder counts
  float p1MinX = 2;
  float p1MaxX = GAME_WIDTH / 2 - 4;
  player1.x = constrain(PLAYER1_START_X + newPos1, p1MinX, p1MaxX);

  // Update player 2 position from encoder
  int newPos2 = encoder2Count / 2;
  float p2MinX = GAME_WIDTH / 2 + 4;
  float p2MaxX = GAME_WIDTH - 2;
  player2.x = constrain(PLAYER2_START_X - newPos2, p2MinX, p2MaxX);
}

// ===== THROW MECHANICS =====
void checkThrow(int playerNum) {
  AccelReading accel = (playerNum == 1) ? accel1 : accel2;
  Player* player = (playerNum == 1) ? &player1 : &player2;
  Snowball* ball = &snowballs[playerNum - 1];

  // Check if player is throwing (sudden acceleration)
  float totalAccel = sqrt(accel.x*accel.x + accel.y*accel.y + accel.z*accel.z);
  if (totalAccel > 2.5f && !ball->active) {
    // Calculate throw power from Z acceleration (spring compression)
    float power = constrain(abs(accel.z) * 2.0f, 1.0f, MAX_THROW_POWER);

    // Calculate angle from X/Y acceleration
    float angleRad = atan2(accel.y, accel.x);
    float angleDeg = degrees(angleRad);
    angleDeg = constrain(angleDeg, -MAX_ANGLE, MAX_ANGLE);

    // Launch snowball
    ball->x = player->x;
    ball->y = 28;  // Near ground level
    ball->vx = power * cos(radians(angleDeg)) * (playerNum == 1 ? 1 : -1);
    ball->vy = -power * sin(radians(angleDeg));
    ball->active = true;
    ball->owner = playerNum - 1;

    Serial.printf("Player %d throws! Power: %.2f, Angle: %.1f\n", playerNum, power, angleDeg);
  }
}

// ===== PHYSICS =====
void updateSnowballs(float dt) {
  for (int i = 0; i < 2; i++) {
    if (!snowballs[i].active) continue;

    // Check for throw
    checkThrow(i + 1);

    // Apply gravity
    snowballs[i].vy += gravity;  // Use dynamic gravity

    // Update position
    snowballs[i].x += snowballs[i].vx * dt * 10;
    snowballs[i].y += snowballs[i].vy * dt * 10;

    // Wraparound: snowballs loop around the screen horizontally
    if (snowballs[i].x < 0) {
      snowballs[i].x += GAME_WIDTH;  // Wrap from left to right
    } else if (snowballs[i].x >= GAME_WIDTH) {
      snowballs[i].x -= GAME_WIDTH;  // Wrap from right to left
    }

    // Bounce off terrain
    int terrainHeight = terrain.heights[(int)snowballs[i].x];
    if (snowballs[i].y >= GAME_HEIGHT - terrainHeight && snowballs[i].vy > 0) {
      // Bounce with energy loss
      snowballs[i].vy = -snowballs[i].vy * 0.6f;  // 60% energy retention
      snowballs[i].y = GAME_HEIGHT - terrainHeight - 1;

      // Create bounce particles
      spawnParticles(snowballs[i].x, snowballs[i].y, COLOR_SNOW, 6, 1.5f);
    }

    // Deactivate if snowball falls off bottom after losing energy
    if (snowballs[i].y >= GAME_HEIGHT) {
      snowballs[i].active = false;
    }
  }
}

void applyWindToSnowballs() {
  // Apply wind to both snowballs
  for (int i = 0; i < 2; i++) {
    if (snowballs[i].active) {
      applyWind(&snowballs[i]);
    }
  }
}

void checkCollisions() {
  // Check if snowballs hit players
  for (int i = 0; i < 2; i++) {
    if (!snowballs[i].active) continue;

    Player* target = (i == 0) ? &player2 : &player1;
    uint32_t targetColor = (i == 0) ? COLOR_P2 : COLOR_P1;

    // Simple collision: check if snowball is near target player
    if (abs(snowballs[i].x - target->x) < 3 && snowballs[i].y > 26) {
      target->health -= 10;
      snowballs[i].active = false;

      // HIT EFFECTS:
      // 1. Explosion particles at hit location
      spawnParticles(target->x, 28, targetColor, 12, 2.5f);
      // 2. Screen shake
      triggerScreenShake(3);

      Serial.printf("Player hit! Health: %d\n", target->health);

      if (target->health <= 0) {
        gameState = (i == 0) ? 1 : 2;  // Player 1 or 2 wins
        Serial.printf("Player %d wins!\n", gameState);
      }
    }
  }
}

// ===== TERRAIN GENERATION =====
void generateTerrain(int seed) {
  srand(seed);

  for (int x = 0; x < GAME_WIDTH; x++) {
    // Simple sine wave with random peaks
    float baseHeight = 4 + 2 * sin(x * 0.1f);
    float randomNoise = random(-2, 3);
    terrain.heights[x] = constrain(baseHeight + randomNoise, 1, 8);
  }
}

void updateTerrain() {
  // Terrain doesn't change during gameplay, but you could add wind effects here
}

// ===== RENDERING =====
void render() {
  CRGB bgColor = getPlanetColor();
  fill_solid(leds, NUM_LEDS, bgColor);

  // Apply screen shake offset (jitter for impact effects)
  int shakeX = 0, shakeY = 0;
  if (screenShake.duration > 0) {
    shakeX = random(-screenShake.intensity, screenShake.intensity + 1);
    shakeY = random(-screenShake.intensity, screenShake.intensity + 1);
  }

  // Draw terrain
  drawTerrain();

  // Draw players
  drawPlayer(&player1, shakeX);  // Player 1 with shake
  drawPlayer(&player2, shakeX);  // Player 2 with shake

  // Draw snowballs
  for (int i = 0; i < 2; i++) {
    if (snowballs[i].active) {
      drawSnowball(&snowballs[i], shakeX, shakeY);
    }
  }

  // Draw particles (explosion effects, bounces, etc)
  drawParticles(shakeX, shakeY);

  // Draw UI (health)
  drawUI();

  // DMA transfer (non-blocking)
  FastLED.show();
}

void drawTerrain() {
  for (int x = 0; x < GAME_WIDTH; x++) {
    int height = terrain.heights[x];
    for (int y = GAME_HEIGHT - height; y < GAME_HEIGHT; y++) {
      leds[y * GAME_WIDTH + x] = COLOR_TERRAIN;
    }
  }
}

void drawPlayer(Player* player, int shakeX) {
  // Simple 3x3 player sprite
  int displayX = (int)player->x + shakeX;
  int displayY = GAME_HEIGHT - 4;  // Near bottom of screen

  CRGB color = (player == &player1) ? COLOR_P1 : COLOR_P2;

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      int x = displayX + dx;
      int y = displayY + dy;
      if (x >= 0 && x < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT) {
        leds[y * GAME_WIDTH + x] = color;
      }
    }
  }
}

void drawSnowball(Snowball* ball, int shakeX, int shakeY) {
  int x = (int)ball->x + shakeX;
  int y = (int)ball->y + shakeY;

  if (x >= 0 && x < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT) {
    leds[y * GAME_WIDTH + x] = COLOR_SNOW;
    // Draw a 2x2 snowball
    if (x + 1 < GAME_WIDTH) leds[y * GAME_WIDTH + (x + 1)] = COLOR_SNOW;
    if (y + 1 < GAME_HEIGHT) leds[(y + 1) * GAME_WIDTH + x] = COLOR_SNOW;
    if (x + 1 < GAME_WIDTH && y + 1 < GAME_HEIGHT) leds[(y + 1) * GAME_WIDTH + (x + 1)] = COLOR_SNOW;
  }
}

void drawParticles(int shakeX, int shakeY) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!particles[i].active) continue;

    int x = (int)particles[i].x + shakeX;
    int y = (int)particles[i].y + shakeY;

    if (x >= 0 && x < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT) {
      // Fade particles based on remaining lifetime
      CRGB color = particles[i].color;
      // Optional: could dim color as lifetime decreases
      leds[y * GAME_WIDTH + x] = color;
    }
  }
}

void drawUI() {
  // Draw health bars at top
  // Player 1 health (left side)
  int health1Bar = map(player1.health, 0, 100, 0, 14);
  for (int x = 0; x < health1Bar; x++) {
    leds[0 * GAME_WIDTH + x] = COLOR_P1;
  }

  // Player 2 health (right side)
  int health2Bar = map(player2.health, 0, 100, 0, 14);
  for (int x = 0; x < health2Bar; x++) {
    leds[0 * GAME_WIDTH + (GAME_WIDTH - 1 - x)] = COLOR_P2;
  }

  // Draw planet indicator in middle (tiny 2px wide)
  // Use yellow indicator for current planet
  int midX = GAME_WIDTH / 2;
  leds[0 * GAME_WIDTH + (midX - 1)] = COLOR_PLANET;
  leds[0 * GAME_WIDTH + midX] = COLOR_PLANET;
}

// ===== PLANET MANAGEMENT =====
void setPlanet(Planet newPlanet) {
  if (newPlanet < 0 || newPlanet >= 5) return;

  currentPlanet = newPlanet;
  gravity = planets[newPlanet].gravity;

  Serial.printf("Planet changed to: %s (Gravity: %.4f)\n",
    planets[newPlanet].name, gravity);
}

void nextPlanet() {
  int nextIndex = (currentPlanet + 1) % 5;
  setPlanet((Planet)nextIndex);
}

void previousPlanet() {
  int prevIndex = (currentPlanet - 1 + 5) % 5;
  setPlanet((Planet)prevIndex);
}

CRGB getPlanetColor() {
  return planets[currentPlanet].color;
}

// ===== INITIALIZATION =====
void initializeGame() {
  // Initialize players
  player1.x = PLAYER1_START_X;
  player1.health = 100;
  player1.score = 0;
  player1.encoderPos = 0;

  player2.x = PLAYER2_START_X;
  player2.health = 100;
  player2.score = 0;
  player2.encoderPos = 0;

  // Initialize snowballs
  for (int i = 0; i < 2; i++) {
    snowballs[i].active = false;
    snowballs[i].owner = i;
  }

  // Initialize planet system
  setPlanet(EARTH);
  planetSwitchTime = millis();

  // Generate initial terrain
  generateTerrain(millis());

  Serial.println("Game initialized!");
  Serial.printf("Starting planet: %s\n", planets[currentPlanet].name);
}
