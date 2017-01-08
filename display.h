#include "cell.h"
#include <SDL.h>
#include <time.h>

#define WINTITLE "Teletext Viewer"
#define WINW (W * CELLW)
#define WINH (H * CELLH)

#define RGBMAX 255 
#define CLRNUM 8 /* number of colours inc. black */

#define SSHOTSTRLEN 128 /* filename strlen for dispTakeScreenshot */

typedef struct display {
   SDL_bool ended;
   SDL_Window *win;
   SDL_Renderer *rend;
} display;

typedef struct RGBtriple {
  myUint8 r, g, b;
} RGBtriple;

void dispRenderCellMatrix(display *d, cell cellmatrix[H][W]);
void dispRenderCell(display *d, cell *c, int ox, int oy);
void dispSetDrawColour(display *d, colour c);
void dispKill(char *s);
void dispInit(display *d);
void dispDrawFrame(display *d);
void dispEventHandler(display *d);
void dispTakeScreenshot(display *d);
