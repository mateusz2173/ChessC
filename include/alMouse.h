#include "alWindow.h"

int draggedTile;

int getTile(int mouseX, int mouseY);
void drawDragged();
int getMouseX();
int getMouseY();

void tilePressed(int tile);
void tileReleased(int tile);