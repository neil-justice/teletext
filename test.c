/* Testing Module.  Compile with 'make test' in order to run tests. Uses a 
 * test wrapping function runTest, which is passed a function pointer to the
 * actual test function.  The struct testtracker is passed each result in turn.
 * Tests which fail due to external circumstances (missing data file, etc) 
 * return "error", rather than "pass" or "fail". See docs/testing.txt for more
 * details, an explanation of the more interesting tests, and documentation
 * of the purposes of the files in the testfiles directory.  */
#include "test.h"

int main(void)
{
  testtracker alltests = { 0, 0 ,0 };
  fprintf(stdout,"\nThis program has been compiled in test mode.\n");
  fprintf(stdout,"To compile it normally, run the 'make' command.\n\n");

  /* state module tests */
  runTest(&alltests, "test_openFile_fakeFile", &test_openFile_fakeFile);
  runTest(&alltests, "test_openFile_realFile", &test_openFile_realFile);
  runTest(&alltests, "test_openFile_badFile", &test_openFile_badFile);
  runTest(&alltests, "test_checkArgs_tooManyArgs", &test_checkArgs_tooManyArgs);
  runTest(&alltests, "test_checkArgs_tooFewArgs", &test_checkArgs_tooFewArgs);
  runTest(&alltests, "test_checkArgs_correctArgNum", &test_checkArgs_correctArgNum);

  runTest(&alltests, "test_readCodesFromFile", &test_readCodesFromFile);
  runTest(&alltests, "test_initState_fgColour", &test_initState_fgColour);
  runTest(&alltests, "test_initState_bgColour", &test_initState_bgColour);
  runTest(&alltests, "test_initState_disMode", &test_initState_disMode);
  runTest(&alltests, "test_initState_height", &test_initState_height);
  runTest(&alltests, "test_initState_holdGraphics", &test_initState_holdGraphics);

  runTest(&alltests, "test_setAlphaMode_red", &test_setAlphaMode_red);
  runTest(&alltests, "test_setAlphaMode_green", &test_setAlphaMode_green);
  runTest(&alltests, "test_setAlphaMode_yellow", &test_setAlphaMode_yellow);
  runTest(&alltests, "test_setAlphaMode_blue", &test_setAlphaMode_blue);
  runTest(&alltests, "test_setAlphaMode_magenta", &test_setAlphaMode_magenta);
  runTest(&alltests, "test_setAlphaMode_cyan", &test_setAlphaMode_cyan);
  runTest(&alltests, "test_setAlphaMode_white", &test_setAlphaMode_white);

  runTest(&alltests, "test_setGraphicsMode_red", &test_setGraphicsMode_red);
  runTest(&alltests, "test_setGraphicsMode_green", &test_setGraphicsMode_green);
  runTest(&alltests, "test_setGraphicsMode_yellow", &test_setGraphicsMode_yellow);
  runTest(&alltests, "test_setGraphicsMode_blue", &test_setGraphicsMode_blue);
  runTest(&alltests, "test_setGraphicsMode_magenta", &test_setGraphicsMode_magenta);
  runTest(&alltests, "test_setGraphicsMode_cyan", &test_setGraphicsMode_cyan);
  runTest(&alltests, "test_setGraphicsMode_white", &test_setGraphicsMode_white);

  runTest(&alltests, "test_setSeparatedMode_cont", &test_setSeparatedMode_cont);
  runTest(&alltests, "test_setSeparatedMode_sep", &test_setSeparatedMode_sep);
  runTest(&alltests, "test_setBgColour_black", &test_setBgColour_black);
  runTest(&alltests, "test_setBgColour_red", &test_setBgColour_red);
  runTest(&alltests, "test_setBgColour_green", &test_setBgColour_green);
  runTest(&alltests, "test_setBgColour_yellow", &test_setBgColour_yellow);
  runTest(&alltests, "test_setBgColour_blue", &test_setBgColour_blue);
  runTest(&alltests, "test_setBgColour_magenta", &test_setBgColour_magenta);
  runTest(&alltests, "test_setBgColour_cyan", &test_setBgColour_cyan);
  runTest(&alltests, "test_setBgColour_white", &test_setBgColour_white);
  runTest(&alltests, "test_setHeightMode_sing", &test_setHeightMode_sing);
  runTest(&alltests, "test_setHeightMode_double", &test_setHeightMode_double);
  runTest(&alltests, "test_setHoldMode_hold", &test_setHoldMode_hold);
  runTest(&alltests, "test_setHoldMode_rel", &test_setHoldMode_rel);

  runTest(&alltests, "test_setCellState", &test_setCellState);
  runTest(&alltests, "test_setMatrixState_fgColour", &test_setMatrixState_fgColour);
  runTest(&alltests, "test_setMatrixState_bgColour", &test_setMatrixState_bgColour);
  runTest(&alltests, "test_setMatrixState_disMode",&test_setMatrixState_disMode);
  runTest(&alltests, "test_setMatrixState_height",&test_setMatrixState_height);
  runTest(&alltests, "test_setMatrixState_holdmode",&test_setMatrixState_holdmode);
  runTest(&alltests, "test_setParityBit",&test_setParityBit);

  /* cell module tests */
  runTest(&alltests, "test_readFont",&test_readFont); 
  runTest(&alltests, "test_fillCellPixelArray_singleHeight",&test_fillCellPixelArray_singleHeight); 
  runTest(&alltests, "test_fillCellPixelArray_doubleHeightTop",&test_fillCellPixelArray_doubleHeightTop); 
  runTest(&alltests, "test_fillCellPixelArray_doubleHeightBottom",&test_fillCellPixelArray_doubleHeightBottom);   
  runTest(&alltests, "test_handleHoldGraphics_noHold",&test_handleHoldGraphics_noHold); 
  runTest(&alltests, "test_handleHoldGraphics_hold",&test_handleHoldGraphics_hold); 
  runTest(&alltests, "test_handleHoldGraphics_mostRecent",&test_handleHoldGraphics_mostRecent); 
  runTest(&alltests, "test_handleHoldGraphics_badMostRecent",&test_handleHoldGraphics_badMostRecent); 
  
  runTest(&alltests, "test_setCellPixels_alphanumeric",&test_setCellPixels_alphanumeric); 
  runTest(&alltests, "test_setCellPixels_contiguous",&test_setCellPixels_contiguous); 
  runTest(&alltests, "test_setCellPixels_separate",&test_setCellPixels_separate); 

  /* display module tests*/
  runTest(&alltests, "test_CompareScrnshotWithCurrentDisplay",&test_CompareScrnshotWithCurrentDisplay);

  fprintf(stdout,"\nFinal results:\nPass: %3d\nFail: %3d\nError: %2d\n\n", alltests.passcnt, alltests.failcnt, alltests.errorcnt);
  return alltests.failcnt;
}

void runTest(testtracker *tracker, char *testidentifier, test t)
{
  char resultstr[RESSTRLEN] = "";
  char formatstr[FMTSTRLEN] = "";
  int l = setColOffset(strlen(testidentifier));
  result r = t();

  clearLogFile(ERRORLOGFILE);

  if (r == pass) {
    tracker->passcnt++;
    strcpy(resultstr,"pass");
  }
  else if (r == fail) {
    tracker->failcnt++;
    strcpy(resultstr,"fail");
  }
  else {
    strcpy(resultstr,"error");
    tracker->errorcnt++;
  }

  sprintf(formatstr,"%%s : %%%ds\n", l);
  fprintf(stdout, formatstr, testidentifier, resultstr);
}

int setColOffset(size_t testIDlen)
{
  int l;

  if ( (l = COLSIZE - testIDlen) > 0) {
    return l;
  }
  else {
    return 1;
  }
}

void clearLogFile(char *filename)
{
  fclose(fopen(filename, "w"));
}


/*** TESTS START ***/


result test_openFile_realFile(void)
{
  FILE *file = openFile(TESTFILE, "rb");
  return (result)(file != NULL);
}

result test_openFile_fakeFile(void)
{
  FILE *file = openFile("/this/dir/is/nonexistent/fakefile.m7", "rb");
  return (result)( checkErrorThrown(EXITATTEMPT) && file == NULL );
}

result test_openFile_badFile(void)
{
  FILE *file = openFile("badfile.m7", "rb");
  return (result)( checkErrorThrown(EXITATTEMPT) && file == NULL );
}

result test_checkArgs_tooManyArgs(void)
{
  checkArgs(CORRECTARGC + 1);
  return (result)checkErrorThrown(EXITATTEMPT);
}

result test_checkArgs_tooFewArgs(void)
{
  checkArgs(CORRECTARGC - 1);
  return (result)checkErrorThrown(EXITATTEMPT);
}

result test_checkArgs_correctArgNum(void)
{
  checkArgs(CORRECTARGC);
  return (result)checkErrorThrown("");
}

result test_readCodesFromFile(void)
{
  int h, w;
  cell testmatrix[H][W];
  myUint8 a[H][W]  = {
  #include "testfiles/testfiledata.h"
  };

  readCodesFromFile(TESTFILE,testmatrix);

  for (h = 0; h < H; h++) {
    for (w = 0; w < W; w++) {
      if (testmatrix[h][w].code != a[h][w]) {
        return fail;
      }
    }
  }

  return pass;
}

/* initState tests*/
result test_initState_fgColour(void)
{
  state s;
  initState(&s);
  return (result)(s.fgcolour == white);
}

result test_initState_bgColour(void)
{
  state s;
  initState(&s);
  return (result)(s.bgcolour == black);
}

result test_initState_disMode(void)
{
  state s;
  initState(&s);
  return (result)(s.dismode == alphanumeric);
}

result test_initState_height(void)
{
  state s;
  initState(&s);
  return (result)(s.height == single);
}

result test_initState_holdGraphics(void)
{
  state s;
  initState(&s);
  return (result)(s.holdgraphics == release);
}

/* setAlphaMode tests */
result test_setAlphaMode_red(void)
{
  state s;
  setMode(redalpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == red);
}
result test_setAlphaMode_green(void)
{
  state s;
  setMode(greenalpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == green);
}
result test_setAlphaMode_yellow(void)
{
  state s;
  setMode(yellowalpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == yellow);
}
result test_setAlphaMode_blue(void)
{
  state s;
  setMode(bluealpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == blue);
}
result test_setAlphaMode_magenta(void)
{
  state s;
  setMode(magentaalpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == magenta);
}
result test_setAlphaMode_cyan(void)
{
  state s;
  setMode(cyanalpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == cyan);
}
result test_setAlphaMode_white(void)
{
  state s;
  setMode(whitealpha, &s);
  return (result)(s.dismode == alphanumeric && s.fgcolour == white);
}

/* setGraphicsMode tests */
result test_setGraphicsMode_red(void)
{
  state s;
  setMode(redgraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == red);
}
result test_setGraphicsMode_green(void)
{
  state s;
  setMode(greengraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == green);
}
result test_setGraphicsMode_yellow(void)
{
  state s;
  setMode(yellowgraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == yellow);
}
result test_setGraphicsMode_blue(void)
{
  state s;
  setMode(bluegraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == blue);
}
result test_setGraphicsMode_magenta(void)
{
  state s;
  setMode(magentagraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == magenta);
}
result test_setGraphicsMode_cyan(void)
{
  state s;
  setMode(cyangraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == cyan);
}
result test_setGraphicsMode_white(void)
{
  state s;
  setMode(whitegraphics, &s);
  return (result)(s.dismode == contiguous && s.fgcolour == white);
}

/* setSeparatedMode tests */
result test_setSeparatedMode_cont(void)
{
  state s;
  setMode(contgraphics, &s);
  return (result)(s.dismode == contiguous);
}

result test_setSeparatedMode_sep(void)
{
  state s;
  setMode(sepgraphics, &s);
  return (result)(s.dismode == separate);
}

/* setBgColour tests */
result test_setBgColour_black(void)
{
  state s;
  setMode(redalpha, &s);
  setMode(blckbackground, &s);
  return (result)(s.bgcolour == black);
}

result test_setBgColour_red(void)
{
  state s;
  setMode(redalpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == red);
}

result test_setBgColour_green(void)
{
  state s;
  setMode(greenalpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == green);
}

result test_setBgColour_yellow(void)
{
  state s;
  setMode(yellowalpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == yellow);
}

result test_setBgColour_blue(void)
{
  state s;
  setMode(bluealpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == blue);
}

result test_setBgColour_magenta(void)
{
  state s;
  setMode(magentaalpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == magenta);
}

result test_setBgColour_cyan(void)
{
  state s;
  setMode(cyanalpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == cyan);
}

result test_setBgColour_white(void)
{
  state s;
  setMode(whitealpha, &s);
  setMode(newbackground, &s);
  return (result)(s.bgcolour == white);
}

/* setHeightMode tests */
result test_setHeightMode_sing(void)
{
  state s;
  setMode(singleheight, &s);
  return (result)(s.height == single);
}

result test_setHeightMode_double(void)
{
  state s;
  setMode(doubleheight, &s);
  return (result)(s.height == doubletop);
}

/* setHoldMode tests */
result test_setHoldMode_hold(void)
{
  state s;
  setMode(holdgraphics, &s);
  return (result)(s.holdgraphics == hold);
}

result test_setHoldMode_rel(void)
{
  state s;
  setMode(relgraphics, &s);
  return (result)(s.holdgraphics == release);
}

result test_setCellState(void)
{
  state s;
  cell c;
  initState(&s);
  setCellState(&c, &s);
  return (result)( c.s.fgcolour == white
    && c.s.bgcolour == black
    && c.s.dismode == alphanumeric
    && c.s.height == single
    && c.s.holdgraphics == release );
}

result test_setMatrixState_fgColour(void)
{
  state currstate;
  cell testmatrix[H][W];

  readCodesFromFile(TESTFILE, testmatrix);
  setMatrixState(testmatrix, &currstate);

  return (result)(testmatrix[5][15].s.fgcolour == red
    && testmatrix[6][15].s.fgcolour == green
    && testmatrix[7][15].s.fgcolour == yellow
    && testmatrix[8][15].s.fgcolour == magenta
    && testmatrix[9][5].s.fgcolour == white );
}

result test_setMatrixState_bgColour(void)
{
  state currstate;
  cell testmatrix[H][W];

  readCodesFromFile(TESTFILE, testmatrix);
  setMatrixState(testmatrix, &currstate);

  return (result)(testmatrix[13][15].s.bgcolour == cyan
    && testmatrix[15][15].s.bgcolour == blue
    && testmatrix[15][25].s.bgcolour == yellow);
}

result test_setMatrixState_disMode(void)
{
  state currstate;
  cell testmatrix[H][W];

  readCodesFromFile(TESTFILE, testmatrix);
  setMatrixState(testmatrix, &currstate);

  return (result)(testmatrix[H-1][15].s.dismode == contiguous
    && testmatrix[H-2][15].s.dismode == contiguous
    && testmatrix[0][15].s.dismode == alphanumeric
    && testmatrix[H-5][15].s.dismode == separate
    && testmatrix[H-5][5].s.dismode == contiguous
    && testmatrix[5][5].s.dismode == alphanumeric );
}

result test_setMatrixState_height(void)
{
  state currstate;
  cell testmatrix[H][W];

  readCodesFromFile(TESTFILE, testmatrix);
  setMatrixState(testmatrix, &currstate);

  return (result)( testmatrix[2][15].s.height == doubletop
    && testmatrix[3][15].s.height == doublebottom
    && testmatrix[15][31].s.height == single
    && testmatrix[16][31].s.height == doubletop
    && testmatrix[15][36].s.height == doubletop
    && testmatrix[16][36].s.height == doublebottom );
}

result test_setMatrixState_holdmode(void)
{
  state currstate;
  cell testmatrix[H][W];

  readCodesFromFile(TESTFILE, testmatrix);
  setMatrixState(testmatrix, &currstate);

  return (result)( testmatrix[2][15].s.holdgraphics == release
    && testmatrix[3][15].s.holdgraphics == release
    && testmatrix[15][31].s.holdgraphics == release
    && testmatrix[16][31].s.holdgraphics == release
    && testmatrix[15][36].s.holdgraphics == release
    && testmatrix[20][36].s.holdgraphics == hold 
    && testmatrix[20][35].s.holdgraphics == hold
    && testmatrix[20][34].s.holdgraphics == hold
    && testmatrix[20][33].s.holdgraphics == hold
    && testmatrix[18][36].s.holdgraphics == hold 
    && testmatrix[18][35].s.holdgraphics == hold
    && testmatrix[18][34].s.holdgraphics == hold
    && testmatrix[18][33].s.holdgraphics == hold );
}

result test_setParityBit(void)
{
  myUint8 i = 100;
  
  return (result)(setParityBit(i) == 228);
}

/* cell module tests */
result test_readFont(void)
{
  myUint16 font[CHARNUM][CELLH];
  myUint16 testdata[CHARNUM][CELLH] = {
  #include "testfiles/fontdata.h"
  };
  int i, j;

  readFont(font, ALPHAFONT);

  for (i = 0; i < CHARNUM; i++) {
    for (j = 0; j < CELLH; j++) {
      if (font[i][j] != testdata[i][j]) {
        return fail;
      }
    }
  }
  return pass;
}

result test_fillCellPixelArray_singleHeight(void)
{
  cell c;
  rect r = {0, 0, CELLW, CELLH };
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
  
  fillCellPixelArray(fonttile, &c, &r);
  
  return (memcmp(c.ch,fonttile,sizeof(myUint16) * CELLH) == 0);
}

result test_fillCellPixelArray_doubleHeightBottom(void)
{
  cell c;
  rect r = { 0, CELLH / 2, CELLW, CELLH / 2 };
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
  myUint16 resultcomp[CELLH] = {
    0xFF11,
    0xFF11,
    0x00FF,
    0x00FF,
    0xFF00,
    0xFF00,
    0x5566,
    0x5566,
    0x4444,
    0x4444,
    0xEEEE,
    0xEEEE,
    0xABAB,
    0xABAB,
    0xCAFE,
    0xCAFE,
    0xFACE,
    0xFACE };
  
  fillCellPixelArray(fonttile, &c, &r);
  
  return (memcmp(c.ch,resultcomp,sizeof(myUint16) * CELLH) == 0);
}

result test_fillCellPixelArray_doubleHeightTop(void)
{
  cell c;
  rect r = { 0, 0, CELLW, CELLH / 2 };
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
  myUint16 resultcomp[CELLH] = {
    0xFFFF,
    0xFFFF,
    0xF485,
    0xF485,
    0x3456,
    0x3456,
    0x1234,
    0x1234,
    0x0000,
    0x0000,
    0x1111,
    0x1111,
    0x2222,
    0x2222,
    0x3333,
    0x3333,
    0x4444,
    0x4444 };
  
  fillCellPixelArray(fonttile, &c, &r);
  
  return (memcmp(c.ch,resultcomp,sizeof(myUint16) * CELLH) == 0);
}

result test_handleHoldGraphics_noHold(void)
{
  cell c;
  myUint16 pixelarray[CELLH];
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
    
  initState(&c.s);
  handleHoldGraphics(fonttile, &c, pixelarray);
  
  return (memcmp(fonttile,pixelarray,sizeof(myUint16) * CELLH) == 0);
}

result test_handleHoldGraphics_hold(void)
{
  cell c;
  myUint16 pixelarray[CELLH];
  myUint16 resultcomp[CELLH] = { 0 };
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
    
  initState(&c.s);
  c.s.holdgraphics = hold;
  handleHoldGraphics(fonttile, &c, pixelarray);
  
  return (memcmp(resultcomp,pixelarray,sizeof(myUint16) * CELLH) == 0);
}

result test_handleHoldGraphics_mostRecent(void)
{
  cell c, d;
  myUint16 pixelarray[CELLH];
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
  myUint16 wrongtile[CELLH] = {
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001 };
  
  initState(&c.s);
  c.s.holdgraphics = hold;
  c.s.dismode = contiguous;
  c.code = FIRSTCHAR + 1;
  
  initState(&d.s);
  d.s.holdgraphics = hold;
  d.s.dismode = contiguous;
  d.code = FIRSTCHAR - 1;
  
  handleHoldGraphics(fonttile, &c, pixelarray);
  handleHoldGraphics(wrongtile, &d, pixelarray);
  
  return (memcmp(fonttile,pixelarray,sizeof(myUint16) * CELLH) == 0);
}

result test_handleHoldGraphics_badMostRecent(void)
{
  cell c, d;
  myUint16 pixelarray[CELLH];
  myUint16 resultcomp[CELLH] = { 0 };
  myUint16 fonttile[CELLH] = {
    0xFFFF,
    0xF485,
    0x3456,
    0x1234,
    0x0000,
    0x1111,
    0x2222,
    0x3333,
    0x4444,
    0xFF11,
    0x00FF,
    0xFF00,
    0x5566,
    0x4444,
    0xEEEE,
    0xABAB,
    0xCAFE,
    0xFACE };
  myUint16 wrongtile[CELLH] = {
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001,
    0x0001 };
  
  initState(&c.s);
  c.s.holdgraphics = hold;
  c.s.dismode = contiguous;
  c.code = FIRSTCHAR + 1;
  
  initState(&d.s);
  d.s.holdgraphics = hold;
  d.s.dismode = alphanumeric;
  d.code = FIRSTCHAR - 1;
  
  handleHoldGraphics(fonttile, &c, pixelarray);
  handleHoldGraphics(wrongtile, &d, pixelarray);
  
  return (memcmp(resultcomp,pixelarray, sizeof(myUint16) * CELLH) == 0);
}

result test_setCellPixels_alphanumeric(void)
{
  cell c;
  myUint16 font[CHARNUM][CELLH];

  initState(&c.s);
  c.code = 0xC2;  /* A */
  readFont(font, ALPHAFONT);
  
  setCellPixels(font, &c);
  
  return (memcmp(c.ch,font[34], sizeof(myUint16) * CELLH) == 0);
}

result test_setCellPixels_separate(void)
{
  cell c;
  myUint16 font[CHARNUM][CELLH];

  initState(&c.s);
  c.code = 0xC2;  /* A */
  readFont(font, SEPFONT);
  
  setCellPixels(font, &c);
  
  return (memcmp(c.ch,font[34], sizeof(myUint16) * CELLH) == 0);
}

result test_setCellPixels_contiguous(void)
{
  cell c;
  myUint16 font[CHARNUM][CELLH];

  initState(&c.s);
  c.code = 0xC2;  /* A */
  readFont(font, CONTFONT);
  
  setCellPixels(font, &c);
  
  return (memcmp(c.ch,font[34], sizeof(myUint16) * CELLH) == 0);
}

/* display module tests */
result test_CompareScrnshotWithCurrentDisplay(void)
{
  /* Calls imagediff.sh -p, which counts the number of different pixels between
   * the latest screenshot and a known good screenshot. */
  int pixeldiffcnt;
  FILE *errorlog;
  char s[SCRIPTSTRLEN] = SCRIPTSTR;
  strcat(s,ERRORLOGFILE);

  if (system(s) != 0) {
    return error; /* script failed to execute */
  }

  errorlog = fopen(ERRORLOGFILE, "r");
  if (errorlog == NULL) {
    return error;
  }
  if (fscanf(errorlog, "%d", &pixeldiffcnt) != 1) {
    return error; /* Most likely to happen if screenshots dir is empty */
  }
  fclose(errorlog);

  return (result)(pixeldiffcnt == 0);
}
