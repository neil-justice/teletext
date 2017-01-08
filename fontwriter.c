/* fontwriter:
 * This standalone program is used to create fonts for the contiguous and
 * separated graphics modes.  It loads m7fixed.fnt, as a baseline, so that font
 * data for blast-through text can be retained, then uses the information
 * given in the specification to set which sixels should be lit and which should
 * not.  (i.e. if the LSB is 1, the top left sixel is lit).  The pixel values of
 * the sixels are stored in an array of 6 8-bit numbers, making contiguous and
 * separate fonts equally easy to produce. (other shapes are also possible). */
 
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define FIRSTCHAR 0xA0 /* Start of sixel or char codes in control code spec. */

#define BLASTBEGIN 0xC0 /* Blast-through text begin and end points. */
#define BLASTEND   0xDF

#define CHARNUM   96
#define CELLH     18
#define SIXELH    (CELLH / 3)
#define SIXELCNT  6
#define SIXELCOLS 2
#define SIXELROWS 3

#define PIXELROWCONT 0xFF /* 11111111 */
#define PIXELROWSEP  0x7E /* 01111110 */

#define BASEFONT "files/m7fixed.fnt"
#define CONTFONT "files/m7cont.fnt"
#define SEPFONT  "files/m7sep.fnt"

typedef unsigned short myUint16;
typedef unsigned char myUint8;

typedef enum sixel { off, on } sixel;
typedef enum sixelcol { left, right } sixelcol;
typedef enum sixelrow { top, mid, bottom } sixelrow;

enum sixelpos { 
  topleft     = 0, /* If bit 0 (LSB) is on, then the top left sixel is on. */
  topright    = 1, /* If bit 1 is on, then the top right sixel is on, etc. */
  midleft     = 2, /* These values are used to generate a bitmask in the   */
  midright    = 3, /* editchar() function */
  bottomleft  = 4, 
  bottomright = 6
};

typedef enum errorType { fatal, warning } errorType;

void readFont(myUint16 font[CHARNUM][CELLH], char *filename);
void editChar(myUint16 *character, unsigned int i, myUint8 *pixelarray);
void clearCharacter(myUint16 character[CELLH]);
void writeSixels(myUint16* character, sixel sixels[SIXELROWS][SIXELCOLS], 
  myUint8 *pixelarray);
void writeFont(myUint16 font[CHARNUM][CELLH], char *filename);
void createFont(myUint16 font[CHARNUM][CELLH], myUint8 *pixelarray, 
  char *filename);
  
FILE *openFile(char *filename, char *mode);
void throwError(errorType e, char *s);

int main(void)
{
  myUint16 font[CHARNUM][CELLH];
  myUint8 contiguous[SIXELH] = { 
    PIXELROWCONT, 
    PIXELROWCONT, 
    PIXELROWCONT, 
    PIXELROWCONT, 
    PIXELROWCONT, 
    PIXELROWCONT };
  myUint8 separate[SIXELH] = { 
    0, 
    PIXELROWSEP,
    PIXELROWSEP,
    PIXELROWSEP,
    PIXELROWSEP,
    0 };
  
  /* load the base font so that the blast-through letters are copied from it */
  readFont(font, BASEFONT);
  
  createFont(font, contiguous, CONTFONT);
  createFont(font, separate, SEPFONT);
  
  return 0;
}

void createFont(myUint16 font[CHARNUM][CELLH], myUint8 *pixelarray, 
  char *filename)
{
  unsigned int i;
 
  for (i = 0; i < CHARNUM; i++) {
    editChar(font[i], i + FIRSTCHAR, pixelarray);
  }
  writeFont(font, filename); 
  fprintf(stdout,"Font written to file %s\n", filename);
}
 
void readFont(myUint16 font[CHARNUM][CELLH], char *filename)
{
  FILE *file = openFile(filename, "rb");
  size_t itemcnt = fread(font, sizeof(myUint16), CHARNUM * CELLH, file);
  
  if (itemcnt != CHARNUM * CELLH) {
    throwError(fatal, "ERROR: Failed to read font file\n");
  }
  fclose(file); 
}

void editChar(myUint16 *character, unsigned int i,  myUint8 *pixelarray)
{
  sixel sixels[SIXELROWS][SIXELCOLS] = {{off}};

  if ((i >> topleft) & 1) {
    sixels[top][left] = on;
  }
  if ((i >> topright) & 1) {
    sixels[top][right] = on;
  }
  if ((i >> midleft) & 1) {
    sixels[mid][left] = on;
  }
  if ((i >> midright) & 1) {
    sixels[mid][right] = on;
  }
  if ((i >> bottomleft) & 1) {
    sixels[bottom][left] = on;
  }
  if ((i >> bottomright) & 1) {
    sixels[bottom][right] = on;
  }
  if ( i < BLASTBEGIN || i > BLASTEND) {
    clearCharacter(character);
    writeSixels(character, sixels, pixelarray);
  }
}

void clearCharacter(myUint16 *character)
{
  int h;
  
  for (h = 0; h < CELLH; h++) {
    character[h] = 0;
  }
}

void writeSixels(myUint16* character, sixel sixels[SIXELROWS][SIXELCOLS], 
  myUint8 *pixelarray)
{
  int i;
  sixelcol c;
  sixelrow r;
  
  for (r = 0; r < SIXELROWS; r++) {
    for (c = 0; c < SIXELCOLS; c++) {
      if (sixels[r][c] == on) {
        /* For each value in the array character[CELLH], either 0x00FF or 0xFF00
         * is written (assuming contiguous graphics), depending on if the sixel 
         * is in the right or left column.  the (1 - c) switches switches a 0 to
         * a 1 and vise versa, so the left shift is either by 0 or 8.
         * CHAR_BIT = 8 (defined in limits.h, and assuming sizeof(char) == 1) */
        for (i = 0; i < SIXELH; i++) {
          character[i +(SIXELH * r)] |= (pixelarray[i] << ((1 - c) * CHAR_BIT));
        }
      }
    }
  }
}

void writeFont(myUint16 font[CHARNUM][CELLH], char *filename)
{
  FILE *file = openFile(filename, "wb");
  size_t itemcnt = fwrite(font, sizeof(myUint16), CHARNUM * CELLH, file);
  
  if (itemcnt != CHARNUM * CELLH) {
    throwError(fatal, "ERROR: Failed to write to font file\n");
  }
  fclose(file); 
}

FILE *openFile(char *filename, char *mode)
{
  FILE *file = fopen(filename, mode);
  
  if (file == NULL) {
    throwError(fatal, 
      "ERROR: unable to open file:\nCheck filename and path.\n");
  }
  
  return file;
}

void throwError(errorType e, char *s)
{
  fprintf(stderr, "%s", s);
  if (e == fatal) {
    exit(EXIT_FAILURE);
  }
}