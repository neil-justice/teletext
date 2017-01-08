#include "state.h"

/* throwError and its replacement during test mode are defined in error.c.
 * Whereas calls to throwError can end up calling exit(), mock_throwError logs
 * any attempted exit calls to a file instead, so as not to interrupt testing.*/
#ifdef TESTING
#define throwError(e, s) mock_throwError(e, s)
#endif

#define FIRSTCHAR 0xA0
#define CHARNUM 96 /* number of characters in font file */
#define FONTNUM 3 /* number of different fonts */
#define RECTNUM 3 /* singleheight, top half of double, bottom half. */
#define ALPHAFONT "files/m7fixed.fnt"
#define CONTFONT  "files/m7cont.fnt"
#define SEPFONT   "files/m7sep.fnt" /* the graphical fonts were created using
 * fontwriter.c */
 
/* Used to determine which portion of a font character to draw - eg just the
 * bottom half, or just the top half: */
typedef struct rect {
  myUint8 x, y, w, h;
} rect;

void loadFonts(myUint16 font[FONTNUM][CHARNUM][CELLH]);
void readFont(myUint16 font[CHARNUM][CELLH], char *filename);
void setCellPixels(myUint16 font[CHARNUM][CELLH], cell *c);
void handleHoldGraphics(myUint16 *fonttile, cell *c, myUint16 *pixelarray);
void fillCellPixelArray(myUint16 *character, cell *c, rect *r);
void setMatrixPixels(cell cellmatrix[H][W], myUint16 font[FONTNUM][CHARNUM][CELLH]);

int  max(int a, int b);
void printCellDebugInfo(cell *c);
void copyArray(myUint16 *dst, myUint16 *src, int n);
void printBinArray(myUint16 *a, int n);