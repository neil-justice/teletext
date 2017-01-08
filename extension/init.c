/* This is the initialisation module.  It initialises the UI menus and cursors*/
#include "init.h"

void initInterface(interface *s)
{
  s->currUIfocus = s->nextUIfocus = mainwindow;
  s->cellchanged = 1;
  memset(s->savefile,'\0',FILENAMEMAX);
  s->prevactions.top = 0;
}

void mainWindowInit(display *d, interface *s,
    myUint16 font[FONTNUM][CHARNUM][CELLH], cell cellmatrix[H][W])
{
  loadFonts(font);
  dispInit(d);
  SDL_StartTextInput();

  s->infopopup = newMessage(0,H - 1, CNTRLSTR, W, font[alphanumeric]);
  s->cur = newCursor(0,0,&cellmatrix[0][0]);
}

void codeMenuInit(interface *s, myUint16 font[CHARNUM][CELLH])
{
  int i;
  char str[CODENUM][CNTRLCODESTRLEN + MENUPAD] = {""};

  /* Pads strings with spaces to make menu rectangular: */
  for (i = 0; i < CODENUM; i++) {
    sprintf(str[i],"( )%*s",CNTRLCODESTRLEN,
      controlCodeLookup(0, i, indexlookup)->str);
  }

  for (i = 0; i < CODENUM; i++) {
    s->codemenu[i] = newMessage(MENUX, MENUY + i, str[i],
      CNTRLCODESTRLEN + MENUPAD, font);
  }

  s->menucur = newCursor(MENUX + MENUCURPOS, MENUY,
    &s->codemenu[0]->cells[MENUCURPOS]);
}

void saveMenuInit(interface *s, myUint16 font[CHARNUM][CELLH])
{
  char str[SAVEMENUWIDTH];

  sprintf(str,"%*s", -SAVEMENUWIDTH, SAVEPROMPTSTR);
  s->savemenu  = newMessage(MENUX,MENUY, str, SAVEMENUWIDTH, font);

  s->savecur = newCursor(MENUX + SAVECURPOS, MENUY,
    &s->savemenu->cells[SAVECURPOS]);
}


cursor *newCursor(int x, int y, cell *target)
{
  cursor *c;

  c = (cursor *)malloc(sizeof(cursor));
  if (!c) {
    throwError(fatal, "ERROR: Cursor malloc failed.\n");
  }

  c->x = x;
  c->y = y;
  c->dx = c->dy = 0;
  c->target = target;

  initState(&c->appearance.s);
  c->appearance.code = c->target->code;
  memset(c->appearance.ch,0, sizeof(myUint16) * CELLH);

  return c;
}

message *newMessage(int x, int y, char *s, int msglen,
  myUint16 font[CHARNUM][CELLH])
{
  message *m;

  m = (message *)malloc(sizeof(message));
  if (!m) {
    throwError(fatal, "ERROR: Message malloc failed.\n");
  }
  m->cells = (cell *)malloc(sizeof(cell) * msglen);
  if (!m->cells) {
    throwError(fatal, "ERROR: Msg string malloc failed.\n");
  }
  initCells(m->cells, msglen);

  m->maxlen = msglen;
  m->x = x;
  m->y = y;
  strcpy(m->str, s);

  fillMessageCells(m, s, font);

  return m;
}

void initCells(cell *a, int n)
{
  int i;

  for (i = 0; i < n; i++) {
    initState(&a[i].s);
  }
}

void fillMessageCells(message *m, char *s, myUint16 font[CHARNUM][CELLH])
{
  int i = 0;

  while (s[i]) {
    m->cells[i].code = (s[i] + MSBVAL);
    setCellPixels(font,&m->cells[i]);
    i++;
  }
}
