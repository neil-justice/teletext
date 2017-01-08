#include "display.h"

/* String length for printing 'pass','fail' or 'error'.  includes EOS */
#define RESSTRLEN 6 
/* Max length for format string used to print test name and result */
#define FMTSTRLEN 16
/* correct value for argc - used for testing the checkArgs() function. */
#define CORRECTARGC 2 
/* known file for testing file reading */
#define TESTFILE "testfiles/test.m7"
/* used to offset the pass/fail output neatly */
#define COLSIZE 58
/* Length of string used to call imagediff.sh, which counts the number of
 * different pixels between the latest screenshot and a known good screenshot. */
#define SCRIPTSTRLEN 128
#define SCRIPTSTR "./imagediff.sh -p >"

typedef enum result { fail, pass, error } result;

typedef struct testtracker {
  int failcnt, passcnt, errorcnt;
} testtracker;

/* Pointer to test function, used to call test functions from runTest */
typedef result(*test)(void); 

void runTest(testtracker *tracker, char *testidentifier, test t);
int setColOffset(size_t testIDlen);
void clearLogFile(char *filename);

/* state module tests */
result test_openFile_fakeFile(void);
result test_openFile_realFile(void);
result test_openFile_badFile(void);
result test_checkArgs_tooManyArgs(void);
result test_checkArgs_tooFewArgs(void);
result test_checkArgs_correctArgNum(void);
result test_readCodesFromFile(void);

result test_initState_fgColour(void);
result test_initState_bgColour(void);
result test_initState_disMode(void);
result test_initState_separatedGraphics(void);
result test_initState_height(void);
result test_initState_holdGraphics(void);

result test_setAlphaMode_red(void);
result test_setAlphaMode_green(void);
result test_setAlphaMode_yellow(void);
result test_setAlphaMode_blue(void);
result test_setAlphaMode_magenta(void);
result test_setAlphaMode_cyan(void);
result test_setAlphaMode_white(void);
result test_setGraphicsMode_red(void);
result test_setGraphicsMode_green(void);
result test_setGraphicsMode_yellow(void);
result test_setGraphicsMode_blue(void);
result test_setGraphicsMode_magenta(void);
result test_setGraphicsMode_cyan(void);
result test_setGraphicsMode_white(void);
result test_setSeparatedMode_cont(void);
result test_setSeparatedMode_sep(void);
result test_setBgColour_black(void);
result test_setBgColour_red(void);
result test_setBgColour_green(void);
result test_setBgColour_yellow(void);
result test_setBgColour_blue(void);
result test_setBgColour_magenta(void);
result test_setBgColour_cyan(void);
result test_setBgColour_white(void);
result test_setHeightMode_sing(void);
result test_setHeightMode_double(void);
result test_setHoldMode_hold(void);
result test_setHoldMode_rel(void);

result test_setCellState(void);
result test_setMatrixState_fgColour(void);
result test_setMatrixState_disMode(void);
result test_setMatrixState_bgColour(void);
result test_setMatrixState_height(void);
result test_setMatrixState_holdmode(void);
result test_setParityBit(void);

/* cell module tests */
result test_readFont(void);
result test_fillCellPixelArray_singleHeight(void);
result test_fillCellPixelArray_doubleHeightTop(void);
result test_fillCellPixelArray_doubleHeightBottom(void);
result test_handleHoldGraphics_noHold(void);
result test_handleHoldGraphics_hold(void);
result test_handleHoldGraphics_mostRecent(void);
result test_handleHoldGraphics_badMostRecent(void);
result test_setCellPixels_alphanumeric(void);
result test_setCellPixels_contiguous(void);
result test_setCellPixels_separate(void);

/* display module tests */
result test_CompareScrnshotWithCurrentDisplay(void);