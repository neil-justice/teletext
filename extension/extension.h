#include "extdisplay.h"

void init(int argc, char **argv, cell cellmatrix[H][W], interface *s,
  display *d, myUint16 font[FONTNUM][CHARNUM][CELLH]);

void switchUIFocus(interface *s);

void stateMachine(display *d, interface *s, myUint16 font[CHARNUM][CELLH],
  cell cellmatrix[H][W]);

void freeCursorMem(cursor *c);
void freeMessageMem(message *m);
void freeAll(interface *s);
