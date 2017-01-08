#include "event.h"
#include <unistd.h>

#define CURSORTICKSPEED 200 /* speed of cursor flash */

typedef enum cursorWrap { wrapon, wrapoff } cursorWrap;

void codeMenuLogic(interface *s, myUint16 font[CHARNUM][CELLH]);
void mainWindowLogic(cell cellmatrix[H][W], interface *s,
  myUint16 font[CHARNUM][CELLH]);
void saveMenuLogic(interface *s);

void updateCursorAppearance(cursor *c);
void flashCursor(cursor *c);
void moveCursor(int *n, int *dn, int nmax, int nmin, cursorWrap wrap);

void updateCodeMenu(interface *s, myUint16 font[CHARNUM][CELLH]);
void updateInfopopup(cursor *c, message *msg, myUint16 font[CHARNUM][CELLH]);

void saveFile(char *filename, cell cellmatrix[H][W]);
void writeCodesToArray(myUint8 a[H][W], cell cellmatrix[H][W]);
void writeFile(myUint8 a[H][W], char *filename);
