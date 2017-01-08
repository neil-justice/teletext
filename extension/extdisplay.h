#include "logic.h"

#define MSDELAY 10 /* value for SDL_Delay */

void mainWindowDraw(display *d, interface *s);
void codeMenuDraw(display *d, interface *s);
void saveMenuDraw(display *d, interface *s);

void drawInfoPopup(display *d, cursor *c, message *msg);
void drawMessage(display *d, message *m);
