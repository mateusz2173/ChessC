#include "alWindow.h"

void runWindow()
{
    initAllegro();
    initImages();
    initComponents();
    al_set_window_title(display, WINDOW_NAME);
    draggedTile = -1;
    perspective = WHITE;
    running = true;
    flip = true;
    bool redraw = false;
    al_start_timer(timer);
    while (running)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = false;
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int tile = getTile(event.mouse.x, event.mouse.y);
            tilePressed(tile);
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            int tile = getTile(event.mouse.x, event.mouse.y);
            tileReleased(tile);
        }
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue))
        {
            redraw = false;
            al_set_target_bitmap(buffer);
            al_clear_to_color(al_map_rgb(255, 255, 255));
            draw();
            al_set_target_backbuffer(display);
            al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
            al_flip_display();
        }
    }
    destroyAllegro();
}

void draw()
{
    drawBoard(c.toMove);
    drawComponents();
    drawDragged();
}

void drawBoard()
{
    int width = al_get_display_width(display) * CHEQUER_SCALE;
    int height = al_get_display_height(display);
    int sq_width = width / 8;
    int sq_height = height / 8;

    bool isWhite = perspective == WHITE ? true : false;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (isWhite)
                al_draw_filled_rectangle(x * sq_width, y * sq_height, (x + 1) * sq_width, (y + 1) * sq_height, light);
            else
                al_draw_filled_rectangle(x * sq_width, y * sq_height, (x + 1) * sq_width, (y + 1) * sq_height, dark);
            if (y == 0)
            {
                char c[1];
                c[0] = FILE_NAME[x];
                al_draw_text(font, lime, x * sq_width, y * sq_height, ALLEGRO_ALIGN_LEFT, c);
            }
            if (x == 7)
            {
                char c[1];
                if(perspective == BLACK)
                    c[0] = RANK_NAME[y];
                else
                    c[0] = RANK_NAME[7 - y];
                al_draw_text(font, lime, (x + 1) * sq_width, y * sq_height, ALLEGRO_ALIGN_LEFT, c);
            }
            isWhite = !isWhite;
        }
        isWhite = !isWhite;
    }
    for (int i = 0; i < 64; i++)
    {
        if (i == draggedTile)
            continue;
        if (!isEmpty(i))
        {
            drawPieceTiled(getPiece(i), i);
        }
    }
}

void initAllegro()
{
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_native_dialog_addon();
    al_install_mouse();
    al_install_keyboard();
    initDisplay();
    loadFonts();

    light = al_map_rgb(240, 217, 181);
    dark = al_map_rgb(181, 136, 99);
    lime = al_map_rgb(0, 0, 0);
    red = al_map_rgb(230, 10, 10);

    queue = al_create_event_queue();
    timer = al_create_timer(1.0f / FPS);
    font = al_load_ttf_font(FONT_PATH, 36, 0);
    menu = al_create_menu();

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_default_menu_event_source());
}

void destroyAllegro()
{
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_uninstall_keyboard();
    al_uninstall_mouse();
}

void initDisplay()
{
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_OPENGL);
    display = al_create_display(BASE_WIDTH, BASE_HEIGHT);

    screenWidth = 1920;
    screenHeight = 1080;
    int windowWidth = al_get_display_width(display);
    int windowHeight = al_get_display_height(display);

    buffer = al_create_bitmap(screenWidth, screenHeight);

    float sx = windowWidth / (float)screenWidth;
    float sy = windowHeight / (float)screenHeight;
    float scale = sx < sy ? sx : sy;

    scaleW = screenWidth * scale;
    scaleH = screenHeight * scale;
    scaleX = (windowWidth - scaleW) / 2;
    scaleY = (windowHeight - scaleH) / 2;
}

void loadFonts()
{
    for (int i = 0; i < FONTS_SIZE; i++)
    {
        fonts[i] = al_load_ttf_font(FONT_PATH, i, 0);
        if (!fonts[i])
        {
            running = false;
            printf("\bNie udalo sie zaladowac czcionki!");
            return;
        }
    }
}
void initComponents()
{
    float windowWidth = al_get_display_width(display);
    float windowHeight = al_get_display_height(display);

    leave_btn = (ui_Button){0};
    leave_btn.img = LEAVE_BTN;
    leave_btn.visible = true;
    leave_btn.size_x = al_get_bitmap_width(LEAVE_BTN);
    leave_btn.size_y = al_get_bitmap_height(LEAVE_BTN);
    leave_btn.position_x = screenWidth * CENTER_SCALE - leave_btn.size_x/2;
    leave_btn.position_y = screenHeight * 0.96;
    leave_btn.on_release = leave_btn_click;

    new_game_btn = (ui_Button){0};
    new_game_btn.visible = true;
    new_game_btn.size_x = al_get_bitmap_width(NEW_GAME_BTN);
    new_game_btn.size_y = al_get_bitmap_height(NEW_GAME_BTN);
    new_game_btn.position_x = windowWidth * (0.78f);
    new_game_btn.position_y = windowHeight * (0.5f);
    new_game_btn.on_release = startNewGame;
    new_game_btn.img = NEW_GAME_BTN;

    undo_btn = (ui_Button){0};
    undo_btn.visible = true;
    undo_btn.size_x = al_get_bitmap_width(UNDO_RED_BTN);
    undo_btn.size_y = al_get_bitmap_height(UNDO_RED_BTN);
    undo_btn.position_x = windowWidth * (0.9f);
    undo_btn.position_y = windowHeight * (0.5f);
    undo_btn.on_release = undo_btn_click;
    undo_btn.img = UNDO_RED_BTN;

    flip_btn = (ui_Button){0};
    flip_btn.size_x = al_get_bitmap_width(FLIP_RED_BTN);
    flip_btn.size_y = al_get_bitmap_height(FLIP_RED_BTN);
    flip_btn.visible = true;
    flip_btn.position_x = windowWidth * 0.84;
    flip_btn.position_y = windowHeight * 0.4;
    flip_btn.on_release = flip_btn_click;
    flip_btn.img = FLIP_GREEN_BTN;

    int sizeX = al_get_bitmap_width(PIECES_IMG[wQ]);
    int sizeY = al_get_bitmap_height(PIECES_IMG[wQ]);
    
    queen_btn = (ui_Button){0};
    queen_btn.size_x = sizeX;
    queen_btn.size_y = sizeY;
    queen_btn.position_x = screenWidth * 0.78 + 0 * sizeX;
    queen_btn.position_y = screenHeight * 0.08;
    queen_btn.visible = false;
    queen_btn.on_release = promote_btn_click;
    queen_btn.img = PIECES_IMG[wQ];

    rook_btn = (ui_Button){0};
    rook_btn.size_x = sizeX;
    rook_btn.size_y = sizeY;
    rook_btn.position_x = screenWidth * 0.78 + 1 * sizeX;
    rook_btn.position_y = screenHeight * 0.08;
    rook_btn.visible = false;
    rook_btn.on_release = promote_btn_click;
    rook_btn.img = PIECES_IMG[wR];

    bishop_btn = (ui_Button){0};
    bishop_btn.size_x = sizeX;
    bishop_btn.size_y = sizeY;
    bishop_btn.position_x = screenWidth * 0.78 + 2 * sizeX;
    bishop_btn.position_y = screenHeight * 0.08;
    bishop_btn.visible = false;
    bishop_btn.on_release = promote_btn_click;
    bishop_btn.img = PIECES_IMG[wB];

    knight_btn = (ui_Button){0};
    knight_btn.size_x = sizeX;
    knight_btn.size_y = sizeY;
    knight_btn.position_x = screenWidth * 0.78 + 3 * sizeX;
    knight_btn.position_y = screenHeight * 0.08;
    knight_btn.visible = false;
    knight_btn.on_release = promote_btn_click;
    knight_btn.img = PIECES_IMG[wN];

    result_label.position_x = screenWidth * 0.8;
    result_label.position_y = screenHeight * 0.75;
    result_label.fontSize = 35;
    result_label.text = "Biale wygrywają!";
    result_label.visible = false;
}

void drawComponents()
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    ui_Button_update(&leave_btn, mouse_state);
    ui_Button_update(&undo_btn, mouse_state);
    ui_Button_update(&new_game_btn, mouse_state);
    ui_Button_update(&flip_btn, mouse_state);
    ui_Button_update(&queen_btn, mouse_state);
    ui_Button_update(&rook_btn, mouse_state);
    ui_Button_update(&bishop_btn, mouse_state);
    ui_Button_update(&knight_btn, mouse_state);

    ui_Button_draw(&leave_btn);
    ui_Button_draw(&undo_btn);
    ui_Button_draw(&new_game_btn);
    ui_Button_draw(&flip_btn);
    ui_Button_draw(&queen_btn);
    ui_Button_draw(&rook_btn);
    ui_Button_draw(&bishop_btn);
    ui_Button_draw(&knight_btn);

    ui_Label_draw(&result_label);
}

void undo_btn_click()
{
    if (undoMove() && flip)
    {
        if (perspective == WHITE)
            perspective = BLACK;
        else perspective = WHITE;
    }
    if(moveCount == 0)
    {
        undo_btn.img = UNDO_RED_BTN;
    }
    else
    {
        undo_btn.img = UNDO_GREEN_BTN;
    }
    
}

void new_game_btn_click()
{
    startNewGame();
}

void promote_btn_click(ui_Button* btn)
{
    if(promote_tile == -1) return;
    int piece = 0;
    if(btn == &queen_btn)
    {
        if(promote_team == WHITE) piece = wQ;
        else piece = bQ;
    }
    else if(btn == &rook_btn)
    {
        if(promote_team == WHITE) piece = wR;
        else piece = bR;
    }
    else if(btn == &bishop_btn)
    {
        if(promote_team == WHITE) piece = wB;
        else piece = bB;
    }
    else if(btn == &knight_btn)
    {
        if(promote_team == WHITE) piece = wN;
        else piece = bN;
    }

    setTile(promote_tile, piece);
    promote_tile = -1;
    hide_promote();
    paused = false;

    checkGameState();
}

void show_promote(int team)
{
    if(team == WHITE)
    {
        queen_btn.img = PIECES_IMG[wQ];
        rook_btn.img = PIECES_IMG[wR];
        bishop_btn.img = PIECES_IMG[wB];
        knight_btn.img = PIECES_IMG[wN];
    }
    else
    {
        queen_btn.img = PIECES_IMG[bQ];
        rook_btn.img = PIECES_IMG[bR];
        bishop_btn.img = PIECES_IMG[bB];
        knight_btn.img = PIECES_IMG[bN];       
    }

    queen_btn.visible = true;
    rook_btn.visible = true;
    bishop_btn.visible = true;
    knight_btn.visible = true;
    
}

void hide_promote()
{
    queen_btn.visible = false;
    rook_btn.visible = false;
    bishop_btn.visible = false;
    knight_btn.visible = false;
}

void flip_btn_click()
{
    if(flip == false)
    {
        flip = true;
        flip_btn.img = FLIP_GREEN_BTN;
    }
    else
    {
        flip = false;
        flip_btn.img = FLIP_RED_BTN;
    }
    
}

void leave_btn_click()
{
    running = false;
}