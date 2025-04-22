#include "display.h"

TFT_eSPI tft = TFT_eSPI(displayWidth, displayHeight);
lv_style_t HighlightStyle;


void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    pinMode(BCKLIGHT_PIN, OUTPUT);
    digitalWrite(BCKLIGHT_PIN, HIGH);
    lv_disp_flush_ready( disp );
}

void initTFT(){
    lv_init();

    tft.init();
    tft.setRotation(1); 
    // tft->fillScreen(TFT_BLACK);

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, displayWidth * displayHeight / 10 );
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = displayWidth;
    disp_drv.ver_res = displayHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    ui_init();

    //init style for the focused object
    lv_style_init(&HighlightStyle);
    lv_style_set_outline_color(&HighlightStyle, lv_color_hex(0x00FF00)); // Green outline
    lv_style_set_outline_width(&HighlightStyle, 5); // Outline width
    lv_style_set_outline_opa(&HighlightStyle, LV_OPA_COVER); // Fully opaque outline
}
void focusNext(lv_group_t* group){
    if (group == nullptr) return;

    lv_obj_t* focused_obj = lv_group_get_focused(group);
    if (focused_obj != nullptr) {
        lv_obj_remove_style(focused_obj, &HighlightStyle, LV_PART_ANY | LV_STATE_ANY);
    }

    lv_group_focus_next(group);

    focused_obj = lv_group_get_focused(group);
    if (focused_obj != nullptr) {
        lv_obj_add_style(focused_obj, &HighlightStyle, 0);
    }
}

void focusPrev(lv_group_t* group){
    if (group == nullptr) return;

    lv_obj_t* focused_obj = lv_group_get_focused(group);
    if (focused_obj != nullptr) {
        lv_obj_remove_style(focused_obj, &HighlightStyle, LV_PART_ANY | LV_STATE_ANY);
    }

    lv_group_focus_prev(group);

    focused_obj = lv_group_get_focused(group);
    if (focused_obj != nullptr) {
        lv_obj_add_style(focused_obj, &HighlightStyle, 0);
    }
}

void moveToScreen1(lv_group_t*& currentGroup, lv_group_t* group1){
    lv_obj_remove_style(ui_Button4, &HighlightStyle, 0);
    lv_event_send(lv_group_get_focused(currentGroup), LV_EVENT_CLICKED, NULL);
    currentGroup = group1;
    lv_group_focus_obj(ui_Button1);
    lv_obj_add_style(lv_group_get_focused(currentGroup), &HighlightStyle, 0);
}

void moveToScreen2(lv_group_t*& currentGroup, lv_group_t* group2) {
    lv_obj_remove_style(ui_Button3, &HighlightStyle, 0);
    lv_event_send(lv_group_get_focused(currentGroup), LV_EVENT_CLICKED, NULL);
    currentGroup = group2;
    lv_group_focus_obj(ui_Button4);
    lv_obj_add_style(lv_group_get_focused(currentGroup), &HighlightStyle, 0);
}