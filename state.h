#include "error.h"

/* throwError and its replacement during test mode are defined in error.c.
 * Whereas calls to throwError can end up calling exit(), mock_throwError logs
 * any attempted exit calls to a file instead, so as not to interrupt testing.*/
#ifdef TESTING
#define throwError(e, s) mock_throwError(e, s)
#endif

#define H 25
#define W 40
#define CELLCNT (H * W)

#define MSBVAL 128 /* value of the most significant bit in a byte */

typedef enum colour {
  black, red, green, yellow, blue, magenta, cyan, white
} colour;

/* I distinguish between modes and codes - codes are the 8 bit hex codes
 * extracted from the .m7 file, whereas modes are switched on and off based on
 * these codes, and stored in a state structure. */
typedef enum displayMode { alphanumeric, contiguous, separate } displayMode;
typedef enum holdMode    { release, hold } holdMode;
typedef enum heightMode  { single, doublebottom, doubletop } heightMode;

typedef struct state {
  colour      fgcolour;
  colour      bgcolour;
  displayMode dismode;
  heightMode  height;
  holdMode    holdgraphics;
} state;

typedef struct cell {
  state s;
  myUint8 code;
  myUint16 ch[CELLH]; /* bit / pixel '2D' array */
} cell;

typedef enum controlCode {
  redalpha        = 0x81,
  greenalpha      = 0x82,
  yellowalpha     = 0x83,
  bluealpha       = 0x84,
  magentaalpha    = 0x85,
  cyanalpha       = 0x86,
  whitealpha      = 0x87,

  redgraphics     = 0x91,
  greengraphics   = 0x92,
  yellowgraphics  = 0x93,
  bluegraphics    = 0x94,
  magentagraphics = 0x95,
  cyangraphics    = 0x96,
  whitegraphics   = 0x97,

  contgraphics    = 0x99,
  sepgraphics     = 0x9a,
  blckbackground  = 0x9c,
  newbackground   = 0x9d,
  singleheight    = 0x8c,
  doubleheight    = 0x8d,
  holdgraphics    = 0x9e,
  relgraphics     = 0x9f

} controlCode;

/* Validate data and read from binary file into matrix. */
void checkArgs(int argc);
void checkTypedefSizes(void);
FILE *openFile(char *filename, char *mode);
myUint8 setParityBit(myUint8 i);
void readCodesFromFile(char *filename, cell cellmatrix[H][W]);

/* Sets the state to the initial state: white text, single height,
 * contiguous graphics, black background, release graphics. */
void initState(state *s);

/* Updates the current state based on the code of the current
 * cell, then writes currstate to the cell state. */
void setMatrixState(cell cellmatrix[H][W], state *s);
void setCellState(cell *c, state *currstate);
void setMode(myUint8 code, state *s);
