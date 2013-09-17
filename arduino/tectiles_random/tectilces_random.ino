#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

#define LIGHTS_ON 10
#define N_PANELS 24
#define REPS 100
int seq[REPS] = {4,0,12,10,11,2,6,8,20,17,13,15,23,12,0,1,5,21,16,7,22,9,19,18,14,3,12,8,10,1,0,20,4,5,11,14,2,9,23,16,19,0,22,12,20,17,1,5,4,11,6,0,15,14,10,22,3,7,21,13,4,16,18,23,19,8,10,6,3,14,2,17,4,21,20,11,12,7,22,9,6,15,17,19,23,21,18,20,18,22,7,5,2,13,13,10,9,16,6,17};
int lightColor[N_PANELS] = {2,2,0,3,2,1,1,3,3,3,2,2,1,1,0,3,1,0,1,0,3,0,0,2};
int colors[4][3] = {{ 131, 201, 183 }, { 253, 252, 229 }, { 252, 176, 60 }, { 237, 28, 36 }};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PANELS * 16, PIN, NEO_GRB + NEO_KHZ800);

#define BRIGHTNESS 0.5
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      colors[i][j] = (int) (BRIGHTNESS * colors[i][j]);
    }
  }
  
  for (int i = REPS-LIGHTS_ON; i < REPS; i++) {
    turnPanelOn(seq[i]);
  }
}

void loop() {
  for (int i = 0; i < REPS; i++) {
    int offIdx = i - LIGHTS_ON;
    if (offIdx < 0) {
      offIdx += REPS;
    }
    
    if (seq[offIdx] != seq[i]) {
      turnPanelOff(seq[offIdx]);
      turnPanelOn(seq[i]);
    }
    
    delay(200);
  }
}

void turnPanelOn(int i) {
  panel(i, strip.Color(colors[lightColor[i]][0], colors[lightColor[i]][1], colors[lightColor[i]][2]));
}

void turnPanelOff(int i) {
  panel(i, strip.Color(0, 0, 0));
}

void panel(uint8_t panel, uint32_t c) {
  for (int i = panel << 4; i < (panel+1) << 4; i++) {
    strip.setPixelColor(i, c);
  }
  
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

