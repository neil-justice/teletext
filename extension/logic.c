/* Logic module - updates the location of cursors and the contents of menus or
 * message popups.  */
#include "logic.h"

void mainWindowLogic(cell cellmatrix[H][W], interface *s,
  myUint16 font[CHARNUM][CELLH])
{
  moveCursor(&s->cur->x, &s->cur->dx, W - 1, 0, wrapon);
  moveCursor(&s->cur->y, &s->cur->dy, H - 1, 0, wrapon);
  s->cur->target = &cellmatrix[s->cur->y][s->cur->x];

  updateCursorAppearance(s->cur);
  flashCursor(s->cur);
  updateInfopopup(s->cur, s->infopopup, font);
}

void codeMenuLogic(interface *s, myUint16 font[CHARNUM][CELLH])
{
  /* can only move up and down: */
  moveCursor(&s->menucur->y,&s->menucur->dy, MENUY + CODENUM - 1, MENUY, wrapon);
  s->menucur->target = &s->codemenu[s->menucur->y - MENUY]->cells[MENUCURPOS];

  updateCursorAppearance(s->menucur);
  updateCodeMenu(s, font);
}

void saveMenuLogic(interface *s)
{
  int xmin = MENUX + SAVECURPOS;
  int xmax = xmin + strlen(s->savefile);

  /* can only move left and right: */
  moveCursor(&s->savecur->x, &s->savecur->dx, xmax, xmin, wrapoff);
  s->savecur->target = &s->savemenu->cells[s->savecur->x - MENUX];

  updateCursorAppearance(s->savecur);
  flashCursor(s->savecur);
}

void moveCursor(int *n, int *dn, int nmax, int nmin, cursorWrap wrap)
{
  if ((*n + *dn) > nmax) {
    if (wrap == wrapon) {
      *n = nmin;
    }
  }
  else if ((*n + *dn) < nmin) {
    if (wrap == wrapon) {
      *n = nmax;
    }
  }
  else {
    *n += *dn;
  }
  *dn = 0;
}

void updateCursorAppearance(cursor *c)
{
  int i;

  initState(&c->appearance.s);
  c->appearance.code = c->target->code;

  for (i = 0; i < CELLH; i++) {
    c->appearance.ch[i] = ~c->target->ch[i];
  }
}

void flashCursor(cursor *c)
{
  static unsigned int toggleflash = 0, prevtime = 0;
  unsigned int currtime = SDL_GetTicks();

  if (toggleflash == 0) {
    c->appearance.s.fgcolour = c->target->s.fgcolour;
    c->appearance.s.bgcolour = c->target->s.bgcolour;
  }
  else {
    c->appearance.s.fgcolour = black;
    c->appearance.s.bgcolour = white;
  }
  if (currtime > (prevtime + CURSORTICKSPEED)) {
    toggleflash = !toggleflash;
    prevtime = currtime;
  }
}

void updateInfopopup(cursor *c, message *msg, myUint16 font[CHARNUM][CELLH])
{
  if (c->target->code < relgraphics) { /* if code is a control code */
    strcat(msg->str, controlCodeLookup(c->target->code, 0, codelookup)->str);
    fillMessageCells(msg, msg->str, font); /* updates msg with new string */
    /* reset message position */
    msg->y = H - 1;
    /* try not to hide the cursor behind the msg: */
    if (c->y == msg->y && c->x < (int)(msg->x + strlen(msg->str)) ) {
      msg->y -= 1;
    }
  }
}

void updateCodeMenu(interface *s, myUint16 font[CHARNUM][CELLH])
{
  int i;

  for (i = 0; i < CODENUM; i++) {
    if (s->cur->target->code == controlCodeLookup(0, i, indexlookup)->code) {
      s->codemenu[i]->str[1] = 'x'; /* mark current code of cell */
      fillMessageCells(s->codemenu[i], s->codemenu[i]->str, font);
    }
    else {
      s->codemenu[i]->str[1] = ' ';
      fillMessageCells(s->codemenu[i], s->codemenu[i]->str, font);
    }
  }
}


void saveFile(char *filename, cell cellmatrix[H][W])
{
  myUint8 a[H][W];

  /* Check if file exists: */
  if (access(filename, F_OK ) == -1) {
    writeCodesToArray(a, cellmatrix);
    writeFile(a,filename);
  }
}

void writeFile(myUint8 a[H][W], char *filename)
{
  FILE *file = openFile(filename, "wb");
  size_t itemcnt = fwrite(a, sizeof(myUint8), CELLCNT, file);

  if (itemcnt != CELLCNT) {
    throwError(fatal, "ERROR: Failed to write binary file\n");
  }
  fclose(file);
}

void writeCodesToArray(myUint8 a[H][W], cell cellmatrix[H][W])
{
  int h, w;

  for (h = 0; h < H; h++) {
    for (w = 0; w < W; w++) {
      a[h][w] = cellmatrix[h][w].code;
    }
  }
}
