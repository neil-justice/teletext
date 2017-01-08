/* Main module.  The extension is a teletext editor which runs inside the viewer
 * created for the first part of the assignment.  It is mouse and keyboard 
 * enabled and allows input of control codes using a menu.  It also has paste, 
 * undo, and save file abilities.  See ../docs/extension.txt for more detailed
 * information.  The menu system is implemented as a finite state machine.  */
#include "extension.h"

int main(int argc, char **argv)
{
  state currstate;
  cell cellmatrix[H][W];
  display d;
  myUint16 font[FONTNUM][CHARNUM][CELLH];
  interface s;

  init(argc, argv, cellmatrix, &s, &d, font);

  do {
    if (s.cellchanged) {
      setMatrixState(cellmatrix, &currstate);
      setMatrixPixels(cellmatrix, font);
      s.cellchanged = 0;
    }
    dispRenderCellMatrix(&d, cellmatrix);
    stateMachine(&d, &s, font [alphanumeric], cellmatrix);
  }
  while (d.ended == 0);

  freeAll(&s);
  return 0;
}

void init(int argc, char **argv, cell cellmatrix[H][W], interface *s,
  display *d, myUint16 font[FONTNUM][CHARNUM][CELLH])
{
  checkTypedefSizes();
  checkArgs(argc);
  readCodesFromFile(argv[1], cellmatrix);
  
  initInterface(s);
  mainWindowInit(d, s, font, cellmatrix);
  codeMenuInit(s, font[alphanumeric]);
  saveMenuInit(s, font[alphanumeric]);
}

void stateMachine(display *d, interface *s, myUint16 font[CHARNUM][CELLH],
  cell cellmatrix[H][W])
{
  switch(s->currUIfocus) {
    case mainwindow:
      mainWindowEvents(d, s->cur, s, cellmatrix);
      mainWindowLogic(cellmatrix, s, font);
      mainWindowDraw(d, s);
      break;
    case codemenu:
      codeMenuEvents(d, s->menucur, s);
      codeMenuLogic(s, font);
      codeMenuDraw(d, s);
      break;
    case savemenu:
      saveMenuEvents(d, s->savecur, s, font);
      saveMenuLogic(s);
      saveMenuDraw(d, s);
      break;
    case saveconf:
      saveFile(s->savefile, cellmatrix);
      s->nextUIfocus = mainwindow;
      break;
  }
  switchUIFocus(s);
  dispDrawFrame(d);
}

void switchUIFocus(interface *s)
{
  s->currUIfocus = s->nextUIfocus;
}

void freeMessageMem(message *m)
{
  free(m->cells);
  free(m);
}

void freeCursorMem(cursor *c)
{
  free(c);
}

void freeAll(interface *s)
{
  int i;
  
  freeMessageMem(s->infopopup);
  freeMessageMem(s->savemenu);
  for (i = 0; i < CODENUM; i++) {
    freeMessageMem(s->codemenu[i]);
  }
  freeCursorMem(s->cur);
  freeCursorMem(s->menucur);
  freeCursorMem(s->savecur);
}
