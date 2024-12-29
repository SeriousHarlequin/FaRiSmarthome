#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#include <lvgl.h>
#include <ui.h>

// MOSI=23, MISO=19, SCK=18
// #define CS_PIN  10

static const uint16_t displayWidth  = 800;
static const uint16_t displayHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ displayWidth * displayHeight / 10 ];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
//initialize all display functionality (tft_eSPI, lvgl, SquareLineStudio)
void initTFT(TFT_eSPI *tft);