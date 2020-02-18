#ifndef ALWINDOW_H
#define ALWINDOW_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include "alImages.h"
#include "alMouse.h"
#include "board.h"
#include "math.h"
#include "alButtons.h"

#include "time.h"

/* DEFINES */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define FPS 75.0f
#define WINDOW_NAME "SzachyC"
#define BASE_WIDTH 1920
#define BASE_HEIGHT 1080
#define CHEQUER_SCALE 0.7
#define CENTER_SCALE (1 - ((1 - CHEQUER_SCALE) / 2))
#define FONTS_SIZE 100

#define FONT_PATH "res/fonts/Raleway-Medium.ttf"

/* ALLEGRO VARS */

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT event;
ALLEGRO_BITMAP *buffer;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_FONT *font;
ALLEGRO_FONT *small_font;

ALLEGRO_FONT *fonts[FONTS_SIZE];

ALLEGRO_MENU *menu;
ALLEGRO_MENU *file_menu;

ALLEGRO_COLOR light, dark, lime, red;

/* COMPONENTS */

ui_Button leave_btn;
ui_Button undo_btn;
ui_Button new_game_btn;
ui_Button flip_btn;
ui_Button queen_btn;
ui_Button bishop_btn;
ui_Button knight_btn;
ui_Button rook_btn;

ui_Label result_label;

/* VARS */

bool running;
bool flip;
int perspective;
int scaleW, scaleH, scaleX, scaleY;
int screenWidth, screenHeight;
int box_id;

/* FUNCTIONS */

void runWindow();
void initDisplay();
void markTile(int tile, ALLEGRO_COLOR color);
void initAllegro();
void destroyAllegro();
void draw();
void drawBoard();
void logic();
void loadFonts();
void drawComponents();
void initComponents();
void undo_btn_click();
void new_game_btn_click();
void promote_btn_click();
void show_promote(int team);
void hide_promote();
void flip_btn_click();
void leave_btn_click();

#endif