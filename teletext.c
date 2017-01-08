/* Main module.  This module is replaced in testing or extension mode (accessed
 * using the makefile commands "make test" and "make ext" respectively). */
#include "display.h"

int main(int argc, char **argv)
{
  state currstate;
  cell cellmatrix[H][W];
  display d;
  myUint16 font[FONTNUM][CHARNUM][CELLH];
  
  checkTypedefSizes();
  checkArgs(argc);
  readCodesFromFile(argv[1], cellmatrix);
  loadFonts(font);
  setMatrixState(cellmatrix, &currstate);
  setMatrixPixels(cellmatrix, font);
  
  dispInit(&d);
  dispRenderCellMatrix(&d, cellmatrix);
  if (strcmp(argv[1],"testfiles/test.m7") == 0) {
    dispTakeScreenshot(&d);
  } /* This screenshot is produced for testing purposes. */
  dispDrawFrame(&d);

  do {
    dispEventHandler(&d);
  }
  while (d.ended == 0);
  return 0;
}
