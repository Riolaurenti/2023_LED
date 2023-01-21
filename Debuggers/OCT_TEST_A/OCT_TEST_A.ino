#define USE_OCTOWS2811
#include <OctoWS2811.h>
#include <FastLED.h>
#include <LEDMatrix.h>

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5
#define PANEL_1_DATA_PIN 2
#define PANEL_2_DATA_PIN 14
#define PANEL_3_DATA_PIN 7
#define PANEL_4_DATA_PIN 8
#define PANEL_5_DATA_PIN 6
#define PANEL_6_DATA_PIN 20
#define PANEL_7_DATA_PIN 21
#define PANEL_8_DATA_PIN 5

#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

// declare matrix
#define MATRIX_WIDTH        138 // width of EACH NEOPIXEL MATRIX (not total display)
#define MATRIX_HEIGHT       2 // height of each matrix
#define MATRIX_TILE_H       1  // number of matrices arranged horizontally
#define MATRIX_TILE_V       8  // number of matrices arranged vertically
#define MATRIX_TYPE        HORIZONTAL_ZIGZAG_MATRIX // matrix layout flags, add together as needed
#define MATRIX_SIZE        (MATRIX_WIDTH*MATRIX_HEIGHT)
#define FRAMES_PER_SECOND  120
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE, MATRIX_TILE_H, MATRIX_TILE_V> matrix;
CRGB tst[2176];
void setup() {
  FastLED.addLeds<WS2812B, PANEL_1_DATA_PIN, GRB>(matrix[0], 0, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_2_DATA_PIN, GRB>(matrix[0], 1*MATRIX_SIZE, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_3_DATA_PIN, GRB>(matrix[0], 2*MATRIX_SIZE, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_4_DATA_PIN, GRB>(matrix[0], 3*MATRIX_SIZE, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_5_DATA_PIN, GRB>(matrix[0], 4*MATRIX_SIZE, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_6_DATA_PIN, GRB>(matrix[0], 5*MATRIX_SIZE, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_7_DATA_PIN, GRB>(matrix[0], 6*MATRIX_SIZE, MATRIX_SIZE);
  FastLED.addLeds<WS2812B, PANEL_8_DATA_PIN, GRB>(matrix[0], 7*MATRIX_SIZE, MATRIX_SIZE);
  
  //FastLED.addLeds<OCTOWS2811>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(32);
}
typedef void (*PatternList[])();
PatternList gPatterns = { whiteLights, whiteLights} ; //Short 2
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
    gPatterns[gCurrentPatternNumber](); // Call the current pattern function once, updating the 'leds' array
    FastLED.show();  
    FastLED.delay(1000/FRAMES_PER_SECOND); // insert a delay to keep the framerate modest 
    // Periodic Updates
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
    EVERY_N_SECONDS( 60 ) { nextPattern(); } // will change for menu selection switch/case style selection.
}
/******************************************************* PATTERNS  *************************************************************************/
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
void nextPattern() {
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns); // add one to the current pattern number, and wrap around at the end
}
void rXY() {
  for (int i=0;i<2176;i++){
   matrix(i) = tst[i]; // nMans best botch ever. Oi, f*ck off, be yourself.
   }
}

void whiteLights() { //  speckles and strobes
  fadeToBlackBy( tst, 256, 10);
  int pos = random16(2174);
  tst[pos] += CRGB::White;
 // rXY();
}
/*
void blueLights() { //  speckles and strobes
  fadeToBlackBy( tst, 256, 10);
  int pos = random16(256);
  tst[pos] += CRGB::Blue;
  rXY();
}
*/
