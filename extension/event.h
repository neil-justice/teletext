#include "init.h"

void mainWindowEvents(display *d, cursor *c, interface *s, cell cellmatrix[H][W]);
void mainWindowHandleText(cursor *c, char ch, interface *s);
void mainWindowPaste(cursor *c, interface *s, cell cellmatrix[H][W]);
void mainWindowUndo(stack *stack);
void pop(stack *s);
void push(stack *s, myUint8 prevcode, cell *c);
void moveCursorOnClick(interface *s, cell cellmatrix[H][W]);

void codeMenuEvents(display *d, cursor *c, interface *s);
void moveCursorOnClickCodeMenu(interface *s);

void saveMenuEvents(display *d, cursor *c, interface *s,
  myUint16 font[CHARNUM][CELLH]);
void saveMenuHandleText(cursor *c, char ch, interface *s,
  myUint16 font[CHARNUM][CELLH]);
void saveMenuRemoveChar(cursor *c, interface *s, myUint16 font[CHARNUM][CELLH]);
