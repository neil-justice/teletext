/* State Module.  Contains functiosn for reading binary (m7) files and writing 
 * the state (eg.foreground colour, text height) of each cell based on the 
 * binary data.  Also runs basic usage validation.  */
#include "state.h"

FILE *openFile(char *filename, char *mode)
{
  FILE *file = fopen(filename, mode);

  if (file == NULL) {
    throwError(fatal,
      "ERROR: unable to open file:\nCheck filename and path.\n");
  }

  return file;
}

void checkArgs(int argc)
{
  if ( (argc != 2) )  {
    throwError(fatal,"ERROR: Incorrect usage:\nOnly 1 argument is required.\n");
  }
}

void checkTypedefSizes(void)
{
  if (sizeof(myUint8) != 1) {
    throwError(warning,
      "WARNING: Unexpected size of type.  This program may not function properly on this system.\n");
  }
  if (sizeof(myUint16) != 2) {
    throwError(warning,
      "WARNING: Unexpected size of type.  This program may not function properly on this system.\n");  
  }

}

void readCodesFromFile(char *filename, cell cellmatrix[H][W])
{
  myUint8 a[H][W];
  FILE *file = openFile(filename, "rb");
  int h, w;
  size_t itemcnt = fread(a, sizeof(myUint8), CELLCNT, file);

  if (itemcnt != CELLCNT) {
    throwError(fatal,"ERROR: Incorrect filesize.  Failed to read file\n");
  }
  fclose(file);

  for (h = 0; h < H; h++) {
    for (w = 0; w < W; w++) {
      cellmatrix[h][w].code = setParityBit(a[h][w]);
    }
  }
}

myUint8 setParityBit(myUint8 i)
{
  if (i < MSBVAL) {
    i += MSBVAL;
  }

  return i;
}

void initState(state *s)
{
  s->fgcolour = white;
  s->bgcolour = black;
  s->dismode = alphanumeric;
  s->height = single;
  s->holdgraphics = release;
}

void setMatrixState(cell cellmatrix[H][W], state *currstate)
{
  int h, w;

  for (h = 0; h < H; h++) {
    initState(currstate); /* Re-init every newline */
    for (w = 0; w < W; w++) {
      setMode(cellmatrix[h][w].code, currstate);
      if (h > 0 && currstate->height == doubletop
      && cellmatrix[h - 1][w].s.height == doubletop) {
        currstate->height = doublebottom;
      }
      setCellState(&cellmatrix[h][w], currstate);
    }
  }
}

void setCellState(cell *c, state *currState)
{
  c->s.fgcolour = currState->fgcolour;
  c->s.bgcolour = currState->bgcolour;
  c->s.dismode = currState->dismode;
  c->s.height = currState->height;
  c->s.holdgraphics = currState->holdgraphics;
}

void setMode(myUint8 code, state *s)
{
  switch ((controlCode) code) {
    /* Alphanumeric colour codes. */
    case redalpha:
      s->dismode  = alphanumeric;
      s->fgcolour = red;
      break;
    case greenalpha:
      s->dismode  = alphanumeric;
      s->fgcolour = green;
      break;
    case yellowalpha:
      s->dismode  = alphanumeric;
      s->fgcolour = yellow;
      break;
    case bluealpha:
      s->dismode  = alphanumeric;
      s->fgcolour = blue;
      break;
    case magentaalpha:
      s->dismode  = alphanumeric;
      s->fgcolour = magenta;
      break;
    case cyanalpha:
      s->dismode  = alphanumeric;
      s->fgcolour = cyan;
      break;
    case whitealpha:
      s->dismode  = alphanumeric;
      s->fgcolour = white;
      break;

    /* Graphical colour codes.  I have assumed that changing the display mode
     * automatically resets contiguosity as well - otherwise the hold graphics
     * rainbow in test.m7 displays as separated.  */
    case redgraphics:
      s->dismode  = contiguous;
      s->fgcolour = red;
      break;
    case greengraphics:
      s->dismode  = contiguous;
      s->fgcolour = green;
      break;
    case yellowgraphics:
      s->dismode  = contiguous;
      s->fgcolour = yellow;
      break;
    case bluegraphics:
      s->dismode  = contiguous;
      s->fgcolour = blue;
      break;
    case magentagraphics:
      s->dismode  = contiguous;
      s->fgcolour = magenta;
      break;
    case cyangraphics:
      s->dismode  = contiguous;
      s->fgcolour = cyan;
      break;
    case whitegraphics:
      s->dismode  = contiguous;
      s->fgcolour = white;
      break;

    /* Contiguous and separate graphics. */
    case contgraphics:
      s->dismode  = contiguous;
      break;
    case sepgraphics:
      s->dismode  = separate;
      break;

    /* Single and double height. Double height works with both contiguous and
     * separated graphics.  Though it is not explicitly stated in the brief that
     * this is required, at http://www.bbcbasic.co.uk/tccgen/manual/tcgen2.html
     * it does say so. */
    case singleheight:
      s->height = single;
      break;
    case doubleheight:
      s->height = doubletop;
      break;

    /* Background colour */
    case blckbackground:
      s->bgcolour = black;
      break;
    case newbackground:
      s->bgcolour = s->fgcolour;
      break;
      
    /* Hold and release graphics. */
    case holdgraphics:
      s->holdgraphics = hold;
      break;
    case relgraphics:
      s->holdgraphics = release;
      break;
    default:
      break;
  }
}
