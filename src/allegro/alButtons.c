#include "alButtons.h"

void ui_Button_update(ui_Button *btn, ALLEGRO_MOUSE_STATE mouse_state)
{
    bool was_pressed = btn->_pressed;

    if (btn->position_x <= mouse_state.x && mouse_state.x <= btn->position_x + btn->size_x)
    {
        if (btn->position_y <= mouse_state.y && mouse_state.y <= btn->position_y + btn->size_y)
        {
            btn->_mouse_over = true;
            if (al_mouse_button_down(&mouse_state, 1))
            {
                btn->_pressed = true;
            }
            else btn->_pressed = false;
        }
    }
    else
    {
        btn->_pressed = false;
    }

    if (was_pressed)
    {
        if (!btn->_pressed && btn->on_release != NULL)
        {
            btn->on_release(btn);
            btn->_pressed = false;
        }
    }
    else
    {
        if (btn->_pressed && btn->on_press != NULL)
        {
            btn->on_press(btn);
        }
    }
}

void ui_Button_draw(ui_Button *btn)
{
    if (btn->visible)
    {
        al_draw_bitmap(btn->img, btn->position_x, btn->position_y, 0);
    }
}

void ui_Label_draw(ui_Label* label)
{
    if(label->visible)
        al_draw_text(fonts[label->fontSize], dark, label->position_x, label->position_y, 0, label->text);
}