#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

#define N_PANELS 24
#define REPS 3
int lights[3][N_PANELS] = {{8,23,12,21,6,10,4,1,2,-1,-1},{5,10,8,23,19,9,-1,-1,-1,-1,-1},{10,15,7,8,5,13,16,20,4,1,14}};
int lightColor[N_PANELS] = {3,0,2,3,0,2,1,1,0,1,1,3,3,3,2,3,2,1,2,0,1,2,0,0};
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
}

//void loop() {
//  for (int i = 0; i < N_PANELS; i++) {
//    panel(i, strip.Color(255, 0, 255));
//    delay(200);
//    panel(i, strip.Color(0, 0, 0));
//  }
//}

void loop() {
  for (int i = 0; i < REPS; i++) {
    for (int j = 1; j <= lights[i][0]; j++) {
      int lightIdx = lights[i][j];
      int lightColorIdx = lightColor[lightIdx];
      panel(lightIdx, strip.Color(colors[lightColorIdx][0], colors[lightColorIdx][1], colors[lightColorIdx][2]));
    }
    delay(2000);
    for (int j = 1; j <= lights[i][0]; j++) {
      panel(lights[i][j], strip.Color(0, 0, 0));
    }
  }
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

