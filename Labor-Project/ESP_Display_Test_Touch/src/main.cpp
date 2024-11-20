#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>
#include <ui.h>


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
void touch_calibrate();

// TOUCH: MOSI=23, MISO=19, SCK=18
#define CS_PIN  10
XPT2046_Touchscreen ts(CS_PIN);
TS_Point p;


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

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );
  //touch_calibrate();
  uint16_t calData[5] = { 357, 3567, 236, 3340, 7 };
  tft.setTouch(calData);

  ui_init();

  Serial.println("Setup done");

}

/***********************************************************************************************************************************/
void loop() {

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

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX = 0, touchY = 0;
 
    if( !ts.touched() || p.z < 1950 )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;
 
        p = ts.getPoint();

        /*Set the coordinates*/
        data->point.x = p.x;
        data->point.y = p.y;
 
        Serial.print( "Data x " );
        Serial.println(data->point.x-700);
 
        Serial.print( "Data y " );
        Serial.println(data->point.y);
    }
}
 

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  // tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup():");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");

  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.print(calData[i]);
    if (i < 4) Serial.print(", ");
  }

  Serial.println(" };");
  Serial.print("  tft.setTouch(calData);");
  Serial.println(); Serial.println();

  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Calibration complete!");
  tft.println("Calibration code sent to Serial port.");

  delay(4000);
}


