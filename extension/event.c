/* This is the event-handler module.  It handles keyboard and mouse input and
 * prepares state changes for the UI FSM. */
#include "event.h"
void mainWindowEvents(display *d, cursor *c, interface *s, cell cellmatrix[H][W])
{
  SDL_Event event;

  while (SDL_PollEvent(&event)) 
  {
    switch (event.type) {
      case SDL_QUIT:
        d->ended = 1;
         break;
      case SDL_MOUSEBUTTONDOWN:
        moveCursorOnClick(s, cellmatrix);
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            d->ended = 1;
            break;
          case SDLK_LEFT:
            c->dx = -1;
            break;
          case SDLK_RIGHT:
            c->dx = 1;
            break;
          case SDLK_UP:
            c->dy = -1;
            break;
          case SDLK_DOWN:
            c->dy = 1;
            break;
          case SDLK_RETURN:
            s->nextUIfocus = codemenu;
            break;
          case SDLK_s:
            if (SDL_GetModState() & KMOD_CTRL) { /* if "ctrl + s" is pressed */
              s->nextUIfocus = savemenu;
            }
            break;
          case SDLK_v:
            if (SDL_GetModState() & KMOD_CTRL) { /* if "ctrl + v" is pressed */
              mainWindowPaste(c, s, cellmatrix);
            }
            break;
          case SDLK_z:
            if (SDL_GetModState() & KMOD_CTRL) { /* if "ctrl + z" is pressed */
              mainWindowUndo(&s->prevactions);
              s->cellchanged = 1;
            }
            break;
          case SDLK_BACKSPACE:
            push(&s->prevactions, c->target->code, c->target);
            c->target->code = ' ' + MSBVAL;
            c->dx = -1;
            s->cellchanged = 1;
            break;
          case SDLK_DELETE:
            push(&s->prevactions, c->target->code, c->target);
            c->target->code = ' ' + MSBVAL;
            s->cellchanged = 1;
            break;
        }
      case SDL_TEXTINPUT:
        mainWindowHandleText(c, event.text.text[0], s);
        break;

    }
  }
}

void mainWindowHandleText(cursor *c, char ch, interface *s)
{
  if (isprint(ch)) {
    push(&s->prevactions, c->target->code, c->target);
    c->target->code = ch + MSBVAL;
    c->dx = 1;
    s->cellchanged = 1;
  }
}

void mainWindowPaste(cursor *c, interface *s, cell cellmatrix[H][W])
{
  char str[W];
  int i = 0;

  memset(str,'\0',W);
  strncpy(str,SDL_GetClipboardText(), W - c->x - 1);
  printf("str: %s\n", str);

  while(str[i]) {
    push(&s->prevactions, cellmatrix[c->y][c->x + i].code,
      &cellmatrix[c->y][c->x + i]);
    cellmatrix[c->y][c->x + i].code = str[i] + MSBVAL;
    printf("cellcodes: %x  ", cellmatrix[c->y][c->x + i].code);
    printf("str: %x\n", str[i] + MSBVAL);
    i++;
  }
  c->dx = i;
  s->cellchanged = 1;
}

void mainWindowUndo(stack *stack)
{
  pop(stack);
}

void push(stack *s, myUint8 prevcode, cell *c)
{
  if (s->top == STACKSIZE) {
    memmove(&s->elem[0],&s->elem[1], sizeof(action) * STACKSIZE);
    s->top--;
  }
  s->elem[s->top].prevcode = prevcode;
  s->elem[s->top].c = c;
  s->top++;
}

void pop(stack *s)
{
  if (s->top == 0) {
    return;
  }
  s->top--;
  s->elem[s->top].c->code = s->elem[s->top].prevcode;
}

void moveCursorOnClick(interface *s, cell cellmatrix[H][W])
{
  SDL_Point mousepos;

  SDL_GetMouseState(&mousepos.x, &mousepos.y );

  s->cur->x = mousepos.x / CELLW;
  s->cur->y = mousepos.y / CELLH;
  s->cur->target = &cellmatrix[s->cur->y][s->cur->x];
}

void codeMenuEvents(display *d, cursor *c, interface *s)
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type) {
      case SDL_QUIT:
        d->ended = 1;
         break;
      case SDL_MOUSEBUTTONDOWN:
         moveCursorOnClickCodeMenu(s);
         break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            s->nextUIfocus = mainwindow;
            break;
          case SDLK_UP:
            c->dy = -1;
            break;
          case SDLK_DOWN:
            c->dy = 1;
            break;
          case SDLK_RETURN:
            push(&s->prevactions, s->cur->target->code, s->cur->target);
            s->cur->target->code =
              controlCodeLookup(0,c->y - MENUY, indexlookup)->code;
            s->nextUIfocus = mainwindow;
            s->cellchanged = 1;
            break;
        }
    }
  }
}

void moveCursorOnClickCodeMenu(interface *s)
{
  SDL_Point mousepos;

  SDL_GetMouseState(&mousepos.x, &mousepos.y );

  if (mousepos.x > MENUXP
  && mousepos.x < (MENUX + CNTRLCODESTRLEN + MENUPAD) * CELLW
  && mousepos.y > MENUYP
  && mousepos.y < (MENUY + CODENUM) * CELLH) {
    s->menucur->y = mousepos.y / CELLH;
    s->menucur->target = &s->codemenu[s->menucur->y]->cells[MENUCURPOS];
  }
}

void saveMenuEvents(display *d, cursor *c, interface *s,
  myUint16 font[CHARNUM][CELLH])
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type) {
      case SDL_QUIT:
        d->ended = 1;
         break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            s->nextUIfocus = mainwindow;
            break;
          case SDLK_LEFT:
            c->dx = -1;
            break;
          case SDLK_RIGHT:
            c->dx = 1;
            break;
          case SDLK_RETURN:
            s->nextUIfocus = saveconf;
            break;
          case SDLK_BACKSPACE:
            saveMenuRemoveChar(c, s, font);
            break;
          case SDLK_DELETE:
            saveMenuRemoveChar(c, s, font);
            break;
        }
      case SDL_TEXTINPUT:
        saveMenuHandleText(c, event.text.text[0], s, font);
        break;
    }
  }
}

void saveMenuHandleText(cursor *c, char ch, interface *s,
  myUint16 font[CHARNUM][CELLH])
{
  int namelen = strlen(s->savefile);

  if (isprint(ch) && namelen < FILENAMEMAX) {
    c->dx = 1;
    s->savemenu->str[SAVECURPOS + namelen] = ch;
    s->savefile[namelen] = ch;
    fillMessageCells(s->savemenu, s->savemenu->str, font);
  }
}

void saveMenuRemoveChar(cursor *c, interface *s, myUint16 font[CHARNUM][CELLH])
{
  char str[SAVEMENUWIDTH] = "";

  if (c->x > (int)SAVECURPOS + MENUX) {
    memmove(&s->savefile[c->x - SAVECURPOS - MENUX - 1],
      &s->savefile[c->x - SAVECURPOS - MENUX],
      FILENAMEMAX - (c->x - SAVECURPOS - MENUX - 1));

    sprintf(str,"%s", SAVEPROMPTSTR);
    strcat(str, s->savefile);
    sprintf(str,"%*s", -SAVEMENUWIDTH, str);
    strcpy(s->savemenu->str, str);
    fillMessageCells(s->savemenu, str, font);
    c->dx = -1;
  }
}
