#include "display.h"

void dispRenderCellMatrix(display *d, cell cellmatrix[H][W])
{
  int h, w;
  
  for (h = 0; h < H; h++) {
    for (w = 0; w < W; w++) {
      dispRenderCell(d, &cellmatrix[h][w], w * CELLW, h * CELLH);
    }
  }
}

void dispRenderCell(display *d, cell *c, int ox, int oy)
{
  int x, y;
  
  for (y = 0; y < CELLH; y++){
    for (x = 0; x < CELLW; x++){
      if (c->ch[y] >> (CELLW - 1 - x) & 1) {
        dispSetDrawColour(d, c->s.fgcolour);
      }
      else {
        dispSetDrawColour(d, c->s.bgcolour);
      }
      SDL_RenderDrawPoint(d->rend, ox + x, oy + y);
    }
  }
}

void dispSetDrawColour(display *d, colour c)
{
  static RGBtriple rgb[CLRNUM] = {
    /* black   */ {0     , 0      ,0     },
    /* red     */ {RGBMAX, 0      ,0     },
    /* green   */ {0     , RGBMAX ,0     },
    /* yellow  */ {RGBMAX, RGBMAX ,0     },
    /* blue    */ {0     , 0      ,RGBMAX},
    /* magenta */ {RGBMAX, 0      ,RGBMAX},
    /* cyan    */ {0     , RGBMAX ,RGBMAX},
    /* white   */ {RGBMAX, RGBMAX ,RGBMAX}
  };

  SDL_SetRenderDrawColor(d->rend,rgb[c].r,rgb[c].g,rgb[c].b,SDL_ALPHA_OPAQUE);
}

void dispInit(display *d)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    dispKill("SDL initialisation failed");
  }

  d->ended = 0;

  d->win= SDL_CreateWindow(WINTITLE, SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, WINW, WINH, SDL_WINDOW_SHOWN);
  if(d->win == NULL){
    dispKill("SDL Window init failed");
  }

  d->rend = SDL_CreateRenderer(d->win, -1, 0);
  if(d->rend == NULL){
    dispKill("SDL Renderer init failed");
  }
}

void dispDrawFrame(display *d)
{
  SDL_RenderPresent(d->rend);
  SDL_RenderClear(d->rend);
}

void dispEventHandler(display *d)
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type) {
      case SDL_QUIT:
        d->ended = 1;
         break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            d->ended = 1;
            break;
        }
    }
  }
}

void dispKill(char *s)
{
  fprintf(stderr, "%s:\n %s\n", s, SDL_GetError());
  SDL_Quit();
  exit(EXIT_FAILURE);
}

void dispTakeScreenshot(display *d)
{
  SDL_Surface *screenshot = SDL_CreateRGBSurface(0, WINW, WINH, 16, 0x0f00, 
    0x00f0, 0x000f, 0xf000);
  char filename[SSHOTSTRLEN] = "";
  time_t tod = time(NULL);
  struct tm *time = gmtime(&tod);
  
  if (screenshot == NULL) {
    dispKill("SDL_CreateRGBSurface failed in dispTakeScreenshot. ");
  }

  SDL_RenderReadPixels(d->rend, NULL, SDL_PIXELFORMAT_ARGB4444, 
    screenshot->pixels, screenshot->pitch);

  strftime(filename, SSHOTSTRLEN, "screenshots/sshot_%d-%m-%y_%H-%M-%S.bmp", time);

  SDL_SaveBMP(screenshot, filename);
  SDL_FreeSurface(screenshot);
  fprintf(stdout,"Screenshot saved as %s\n", filename);
}
