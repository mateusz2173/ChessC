#ifndef AL_BUTTONS
#define AL_BUTTONS

typedef struct ui_Button ui_Button;
typedef struct ui_Label ui_Label;

#include "alWindow.h"

struct ui_Button
{
    float position_x;
    float position_y;
    float size_x;
    float size_y;

    ALLEGRO_BITMAP *img;

    bool visible;

    bool _mouse_over;
    bool _pressed;

    void (*on_press)(struct ui_Button *in);
    void (*on_release)(struct ui_Button *in);
};

struct ui_Label
{
    float position_x;
    float position_y;

    bool visible;

    int fontSize;
    char* text;
};

void ui_Button_update(ui_Button *thiz, ALLEGRO_MOUSE_STATE mouse_state);
void ui_Button_draw(ui_Button *thiz);
void ui_Label_draw(ui_Label  *label);

#endif