#include "moremethods.h"

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (800)
// keep track of how big the screen is
int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
SDL_Window *win;
SDL_Renderer *rend;

// set to 1 when window close button is pressed
int close_requested = 0;

int initWindow(void)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
  {
      printf("error initializing SDL: %s\n", SDL_GetError());
      return 1;
  }

  win = SDL_CreateWindow("Snake",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         WINDOW_WIDTH,
                         WINDOW_HEIGHT,
                         SDL_WINDOW_RESIZABLE);
  if (!win)
  {
      printf("error creating window: %s\n", SDL_GetError());
      SDL_Quit();
    return 1;
  }

  // Create a renderer, which sets up the graphics hardware
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  rend = SDL_CreateRenderer(win, -1, render_flags);
  if (!rend)
  {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
  }
	return 0;
}

void initMainLoop(void)
{
  createarr();
  // animation loop
  while (!close_requested)
  {
			// clear the window
			SDL_RenderClear(rend);
      rendergrid();
      inputer();
			game();
      // draw the image to the window
      SDL_RenderPresent(rend);
      // wait 1/60th of a second
      SDL_Delay(1000/100);
  }

  // clean up resources before exiting
	SDL_DestroyTexture(redtex);
	SDL_DestroyTexture(blacktex);
  SDL_DestroyTexture(darkgreentex);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
