/* Cell module.  Each cell contains an array of CELLH myUint16s, which is
 * treated as a 2D array of bits.  This module fills the contents of this
 * array based on the internal state of the cell, such as its graphics mode,
 * height, and so on. */
#include "cell.h"

void readFont(myUint16 font[CHARNUM][CELLH], char *filename)
{
  FILE *file = openFile(filename, "rb");
  size_t itemcnt = fread(font, sizeof(myUint16), CHARNUM * CELLH, file);

  if (itemcnt != CHARNUM * CELLH)  {
    throwError(fatal, "ERROR: Failed to read font file\n");
  }
  fclose(file);
  /* In the specification,        0xC3 = £
   * In the font file,            0xC3 = #
   * In the screenshots provided: 0xC3 = #
   * I have chosen to follow the font file and the screenshot (test_m7.gif). */
}

void loadFonts(myUint16 font[FONTNUM][CHARNUM][CELLH])
{
  readFont(font[alphanumeric], ALPHAFONT);
  readFont(font[contiguous], CONTFONT);
  readFont(font[separate], SEPFONT);
}

void setMatrixPixels(cell cellmatrix[H][W], myUint16 font[FONTNUM][CHARNUM][CELLH])
{
  int h, w;

  for (h = 0; h < H; h++) {
    for (w = 0; w < W; w++) {
      setCellPixels(font[cellmatrix[h][w].s.dismode], &cellmatrix[h][w]);
    }
  }
}

void setCellPixels(myUint16 font[CHARNUM][CELLH], cell *c)
{
  /* control codes are (usually) displayed as a space: */
  myUint8 index = max(c->code, FIRSTCHAR ) - FIRSTCHAR;
  /* These rects (x, y ,w ,h) determine which part of the character is
   * printed: */
  static rect fontrect[RECTNUM] = {
    { 0,         0, CELLW, CELLH,    }, /* normal       */
    { 0, CELLH / 2, CELLW, CELLH / 2 }, /* doublebottom */
    { 0,         0, CELLW, CELLH / 2 }  /* doubletop    */ };
  myUint16 pixelarray[CELLH] = {0};

  handleHoldGraphics(font[index], c, pixelarray);
  fillCellPixelArray(pixelarray, c, &fontrect[c->s.height]);
}

void handleHoldGraphics(myUint16 *fonttile, cell *c, myUint16 *pixelarray)
{
  static myUint16 mostrecent[CELLH] = {0};
  static heightMode  prevheight  = single;
  static displayMode prevdismode = alphanumeric;

  /* As per the spec, reset the hold graphics char to a space if there has been
   * a change in the display mode or height mode. */
  if (prevdismode != c->s.dismode || prevheight != c->s.height) {
    memset(mostrecent, 0, sizeof(myUint16) * CELLH);
  }

  /* sets pixelarray to either last graphics char (if hold graphics is on and
   * the current code is a control code) or to the correct font tile (normal
   * behaviour): */
  if (c->code < FIRSTCHAR && c->s.holdgraphics == hold) {
    memcpy(pixelarray, mostrecent, sizeof(myUint16) * CELLH);
  }
  else {
    memcpy(pixelarray, fonttile, sizeof(myUint16) * CELLH);
  }

  /* If graphical code and not control code, then update the mostrecent
   * character - stored as an array in order to capturethe same graphics mode as
   * it was originally: */
  if (c->code > FIRSTCHAR && c->s.dismode != alphanumeric) {
    memcpy(mostrecent, fonttile, sizeof(myUint16) * CELLH);
  }
  prevdismode = c->s.dismode;
  prevheight  = c->s.height;
}

void fillCellPixelArray(myUint16 *character, cell *c, rect *r)
{
  unsigned int y, i, vscale = CELLH / r->h; /* vertical scaling factor
   * ( for double height) */

  for (y = 0; y < r->h; y++){
    for (i = 0; i < vscale; i++) {
      c->ch[(y * vscale) + i] = character[y + r->y];
    }
  }
}

int max(int a, int b)
{
  if (a > b) {
    return a;
  }
  return b;
}

/* The following functions are for debugging only.  They have not been tested.*/

void printBinArray(myUint16 *a, int n)
{
  int i,j;

  for (i = 0; i < n; i++) {
    for (j = CELLW; j >= 0 ; j--) {
      fprintf(stderr,"%d", (a[i] >> j) & 1);
    }
    fprintf(stderr,"\n");
  }
  fprintf(stderr,"\n");
}

void printCellDebugInfo(cell *c)
{
  fprintf(stderr,"Cell code: 0x%x\n", c->code);
  fprintf(stderr,"fgColour: %d\n", c->s.fgcolour);
  fprintf(stderr,"bgColour: %d\n", c->s.bgcolour);
  fprintf(stderr,"disMode: %d\n", c->s.dismode);
  fprintf(stderr,"height: %d\n", c->s.height);
  fprintf(stderr,"holdGraphics: %d\n\n", c->s.holdgraphics);
  printBinArray(c->ch, CELLH);
}
