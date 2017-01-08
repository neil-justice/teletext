/* Display module.  Uses pixel coordinates rather than cell coordinates, unlike
 * the other modules.  */
#include "extdisplay.h"

void mainWindowDraw(display *d, interface *s)
{
  drawInfoPopup(d, s->cur, s->infopopup);
  dispRenderCell(d, &s->cur->appearance, s->cur->x * CELLW, s->cur->y * CELLH);
}

void codeMenuDraw(display *d, interface *s)
{
  int i;

  for (i = 0; i < CODENUM; i++) {
    drawMessage(d, s->codemenu[i]);
  }
  dispRenderCell(d, &s->menucur->appearance, s->menucur->x * CELLW,
    s->menucur->y * CELLH);
}

void saveMenuDraw(display *d, interface *s)
{
  drawMessage(d, s->savemenu);
  dispRenderCell(d, &s->savecur->appearance, s->savecur->x * CELLW,
    s->savecur->y * CELLH);
}

void drawInfoPopup(display *d, cursor *c, message *msg)
{
  if (c->target->code < relgraphics) { /* if code is a control code */
    drawMessage(d, msg);
    strcpy(msg->str, CNTRLSTR); /* reset message contents */
  }
}

void drawMessage(display *d, message *m)
{
  unsigned int i;

  for (i = 0; i < strlen(m->str); i++) {
    dispRenderCell(d, &m->cells[i], (m->x * CELLW) + (i * CELLW), (m->y * CELLH));
  }
}
