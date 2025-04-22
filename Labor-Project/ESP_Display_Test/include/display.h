#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <freertos/semphr.h>


#include <lvgl.h>
#include <ui.h>

// MOSI=23, MISO=19, SCK=18
// #define CS_PIN  10
#define BCKLIGHT_PIN 48
#define ROTARY_A 10
#define ROTARY_B 11
#define ROTARY_BUTTON 12

static const uint16_t displayWidth  = 800;
static const uint16_t displayHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ displayWidth * displayHeight / 10 ];

extern TFT_eSPI tft;
extern lv_style_t HighlightStyle;


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
//initialize all display functionality (tft_eSPI, lvgl, SquareLineStudio)
void initTFT();
void focusNext(lv_group_t* group);
void focusPrev(lv_group_t* group);
void moveToScreen1(lv_group_t*& currentGroup, lv_group_t* group1);
void moveToScreen2(lv_group_t*& currentGroup, lv_group_t* group2);
