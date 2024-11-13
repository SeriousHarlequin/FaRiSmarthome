#define BLACK 0x0000
#define WHITE 0xFFFF

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>
#include <ui.h>

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

// MOSI=23, MISO=19, SCK=18
#define CS_PIN  10

XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2

static const uint16_t screenWidth  = 800;
static const uint16_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

int16_t h;
int16_t w;

void setup() {
  Serial.begin(115200);

  tft.init();
  h = tft.height();
  w = tft.width();

  tft.setRotation(3); 
  tft.fillScreen(TFT_BLACK);

  ts.begin();
  ts.setRotation(1);

  
  lv_init();

  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

  /*Initialize the display*/
   static lv_disp_drv_t disp_drv;
   lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
   disp_drv.hor_res = screenWidth;
   disp_drv.ver_res = screenHeight;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register( &disp_drv );

  ui_init();

  Serial.println("Setup done");

}

/***********************************************************************************************************************************/
void loop() {

  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    if (p.z > 1950){
      Serial.print("Pressure = ");
      Serial.print(p.z);
      Serial.print(", x = ");//620 to 3600
      Serial.print(p.x);
      Serial.print(", y = ");//380 to 3600
      Serial.print(p.y);
      Serial.println();

    }
    delay(30);
  }
  lv_timer_handler(); /* let the GUI do its work */
  



}

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

