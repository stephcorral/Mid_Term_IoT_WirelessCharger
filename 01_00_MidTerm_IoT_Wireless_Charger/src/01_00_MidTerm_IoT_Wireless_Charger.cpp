/* 
 * Project 01_00_Wireless Charger 
 * Author: Steph
 * Date: 03-06-2025
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Photodiode.h"
#include "Colors.h"
#include "neopixel.h"
#include "math.h"

const int OLED_RESET=-1;
Adafruit_SSD1306 display(OLED_RESET);
 
#if(SSD1306_LCDHEIGHT !=64)
#error ("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


//creating my variables
//photodiode variables
const int PHOTODIODE = A1;
Photodiode photoD(PHOTODIODE);

//neopixel set up
const int PIXELCOUNT = 4;
int mode = 0;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);

const unsigned char bitmap_bolt[] PROGMEM = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,
  0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
  0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
  0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x0F,0xFC,0x00,0x00,0x00,0x00,0x1F,0xFF,0xE0,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x1F,0xFF,0xF8,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x01,0xFF,0xF0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x0F,0xFF,0xE0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x7F,0xFF,0x80,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x1F,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x07,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x1F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x3F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x0F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xC0,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0x80,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0x80,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x1F,0xFF,0xF0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x3F,0xFF,0x80,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x00,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,
  0x7F,0x80,0x00,0x00,0x00,0x01,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xF8,
  0x7F,0x80,0x00,0x00,0x00,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xE0,
  0x7F,0x80,0x00,0x00,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x0F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,
  0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
  0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
  0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
  0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,
  0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void setup() {
  //set up serial
    Serial.begin(9600);
    waitFor(Serial.isConnected, 10000);

  //set up pixels
    pixel.begin();
    pixel.setBrightness(15);
    pixel.show();
    pixel.setPixelColor(4,purple);




    // shows lighting bolt:
    // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    // display.clearDisplay();
    // display.drawBitmap(0,0, bitmap_bolt, 128, 64, 1);
    // display.display();

    
}

void loop() {

  //seeing if the photodiode is being affected
  Serial.printf("Photodiode = %i\n", photoD.inputValue());
  delay(600);

  pixel.clear();
  pixel.show();
  if(photoD.isOn()){
    for(int i =0; i<=4;i++){
      pixel.setPixelColor(i,blue);
      pixel.show();
      Serial.printf("Photodiode is covered");
    }
    
  }else{
    for(int i =0; i<=4;i++){
      pixel.setPixelColor(i,red);
      pixel.show();
      Serial.printf("Photodiode is NOOOTTTT covered");

    }
  }
}
