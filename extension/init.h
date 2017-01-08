#include "utility.h"

#define MENUCURPOS 1 /* horizontal position of cursor in code menu */
#define SAVECURPOS (strlen(SAVEPROMPTSTR)) /* Starting position of save menu cursor */

#define CNTRLSTR "Control code: " /* String to display before control code name. */

#define MENUPAD 4 /* padding in control code menu */
#define MENUX 4 /* top-left corner of menus */
#define MENUY 2
#define MENUXP (CELLW * MENUX) /* top-left corner of menus in pixels */
#define MENUYP (CELLH * MENUY)

#define SAVEPROMPTSTR "Save file as:"
#define SAVEMENUWIDTH (W - MENUX - 1)
#define FILENAMEMAX 20

#define STACKSIZE 50

/* Used to say what currently has focus: */
typedef enum UIfocus { mainwindow, codemenu, savemenu, saveconf } UIfocus;

typedef struct cursor {
  cell *target;
  cell appearance;
  int x, y, dx, dy;
} cursor;

typedef struct message {
  cell *cells;
  char str[W];
  int maxlen, x, y;
} message;

/* These structs are used for "undo" functionality: */
typedef struct action {
  myUint8 prevcode;
  cell *c;
} action;

typedef struct stack {
  action elem[STACKSIZE];
  int top;
} stack;

typedef struct interface {
  UIfocus currUIfocus;
  UIfocus nextUIfocus; /* The window/menu which will have focus next step */

  message *infopopup, *codemenu[CODENUM], *savemenu;
  cursor *cur, *menucur, *savecur;
  
  stack prevactions;
  int cellchanged; /* whether or not the cellmatrix needs to be recalculated */
  char savefile[FILENAMEMAX];

} interface;

void initInterface(interface *s);

void mainWindowInit(display *d, interface *s,
    myUint16 font[FONTNUM][CHARNUM][CELLH], cell cellmatrix[H][W]);
void codeMenuInit(interface *s, myUint16 font[CHARNUM][CELLH]);
void saveMenuInit(interface *s, myUint16 font[CHARNUM][CELLH]);

cursor *newCursor(int x, int y, cell *target);
message *newMessage(int x, int y, char *s, int msglen, myUint16 font[CHARNUM][CELLH]);
void initCells(cell *a, int n);

void fillMessageCells(message *m, char *s, myUint16 font[CHARNUM][CELLH]);

void extDispInit(display *d, myUint16 font[FONTNUM][CHARNUM][CELLH]);
