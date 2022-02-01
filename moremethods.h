#include "moremoremethods.h"

#define SIZE (20)

// Create snake array
int grid [SIZE+1][SIZE+1];
int ia;
int ib;
int ic;
int id;
int ie;
int ig;
// keep track of how big the screen is
int head[2];
int tail[2];
int food[2];
int snake[SIZE*SIZE];
int snakel;
// keep track of how big the screen is
int height;
int width;
SDL_Rect rect;
// set to 1 when window close button is pressed
extern int close_requested;
extern SDL_Renderer *rend;
extern SDL_Window *win;
int debug;
int sizerw;
int sizerh;

void rendergrid(void)
{
	// screen rezising
  SDL_GetWindowSize(win, &width, &height);
  createtile(height/SIZE);
  sizerw=width/SIZE;
  sizerh=height/SIZE;
	if (width<height)
	{
		for (ia = 1; ia < SIZE+1; ++ia)
		{
			for (ib = 1; ib < SIZE+1; ++ib)
			{
				rect.x=((ib-1)*sizerw)+1;
				rect.y=((ia-1)*sizerw-(width-height)/2)+1;
				rect.w=sizerw-2;
				rect.h=sizerw-2;
				SDL_RenderCopy(
					rend,
					chooser(grid[ib][ia]),
					0,
					&rect
				);
			}
		}
	}
	else
	{
		for (ia = 1; ia < SIZE+1; ++ia)
		{
			for (ib = 1; ib < SIZE+1; ++ib)
			{
				rect.x=((ib-1)*sizerh-(height-width)/2)+1;
				rect.y=((ia-1)*sizerh)+1;
				rect.w=sizerh-2;
				rect.h=sizerh-2;
				SDL_RenderCopy(
					rend,
					chooser(grid[ib][ia]),
					0,
					&rect
				);
			}
		}
	}
  SDL_DestroyTexture(blacktex);
  SDL_DestroyTexture(darkgreentex);
  SDL_DestroyTexture(redtex);
}

void createarr(void)
{
  ie=3;
  id=0;
  ig=3;
	for (ia = 1; ia < SIZE+1; ++ia)
  	{
    	for (ib = 1; ib < SIZE+1; ++ib)
		{
    		grid[ia][ib]=0;
		}
  	}
  head[0] = SIZE/2;
  tail[0] = SIZE/2-3;
  food[0] = SIZE/2+2;
  head[1] = SIZE/2;
  tail[1] = SIZE/2;
  food[1] = SIZE/2;
  snake[0] = 3;
  snake[1] = 3;
  snake[2] = 3;
  snakel = 3;
	grid[head[0]][head[1]]=1;
  grid[SIZE/2-1][SIZE/2]=1;
	grid[food[0]][food[1]]=2;
}

void randomfood(int lol)
{
  while (1) {
    food[0] = (rand() % 10)+1;
    food[1] = (rand() % 10)+1;
    if (grid[food[0]][food[1]]==0) {
      grid[food[0]][food[1]]=2;
      snake[snakel]=lol;
      snakel++;
      printf("len:%i\n", snakel);
      break;
    }
  }
}

void inputer(void)
{
  // process events
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
      switch (event.type)
      {
      case SDL_QUIT:
          close_requested = 1;
          break;
      case SDL_KEYDOWN:
          switch (event.key.keysym.scancode)
          {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                ie = 0;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                ie = 1;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                ie = 2;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                ie = 3;
                break;
            default:
                break;
          }
          break;
      }
  }
}

int checkend(void)
{
  if (head[0]==SIZE+1 || head[0]==0 || head[1]==SIZE+1 || head[1]==0) {
    createarr();
    printf("wtf\n");
    return 1;
  }
  else if (grid[head[0]][head[1]]==1) {
    createarr();
    return 1;
  }
  else {
    return 0;
  }
}

void snaketail(int lul)
{
  grid[tail[0]][tail[1]]=0;
  printf("%i:%i\n", tail[0],tail[1]);
  switch (snake[0])
  {
    case 0:
      tail[1]=tail[1]-1;
      for (ia = 0; ia < snakel; ia++) {
        snake[ia]=snake[ia+1];
      }
      snake[snakel-1]=lul;
      break;
    case 1:
      tail[1]=tail[1]+1;
      for (ia = 0; ia < snakel; ia++) {
        snake[ia]=snake[ia+1];
      }
      snake[snakel-1]=lul;
      break;
    case 2:
      tail[0]=tail[0]-1;
      for (ia = 0; ia < snakel; ia++) {
        snake[ia]=snake[ia+1];
      }
      snake[snakel-1]=lul;
      break;
    case 3:
      tail[0]=tail[0]+1;
      for (ia = 0; ia < snakel; ia++) {
        snake[ia]=snake[ia+1];
      }
      snake[snakel-1]=lul;
      break;
    default:
      printf("%i hä\n", ig);
  }
}

void game(void)
{
  // Game Tick
  if (ic==10)
  {
    // Game loop
    switch (ig) {
      case 0:
        if (ie!=1) {
          ig=ie;
        }
        break;
      case 1:
        if (ie!=0) {
          ig=ie;
        }
        break;
      case 2:
        if (ie!=3) {
          ig=ie;
        }
        break;
      case 3:
        if (ie!=2) {
          ig=ie;
        }
        break;
      default:
        printf("%i hä\n", ig);
    }
    switch (ig)
    {
      case 0:
        head[1]=head[1]-1;
        id=checkend();
        if (id!=1) {
          if (grid[head[0]][head[1]]!=2) {
            snaketail(ig);
          }
          else {
            randomfood(ig);
          }
          grid[head[0]][head[1]]=1;
        }
        else {
          break;
        }
        break;
      case 1:
        head[1]=head[1]+1;
        id=checkend();
        if (id!=1) {
          if (grid[head[0]][head[1]]!=2) {
            snaketail(ig);
          }
          else {
            randomfood(ig);
          }
          grid[head[0]][head[1]]=1;
        }
        else {
          break;
        }
        break;
      case 2:
        head[0]=head[0]-1;
        id=checkend();
        if (id!=1) {
          if (grid[head[0]][head[1]]!=2) {
            snaketail(ig);
          }
          else {
            randomfood(ig);
          }
          grid[head[0]][head[1]]=1;
        }
        else {
          break;
        }
        break;
      case 3:
        head[0]=head[0]+1;
        id=checkend();
        if (id!=1) {
          if (grid[head[0]][head[1]]!=2) {
            snaketail(ig);
          }
          else {
            randomfood(ig);
          }
          grid[head[0]][head[1]]=1;
        }
        else {
          break;
        }
        break;
    }
    ic=1;
  }
  else
  {
    ic=ic+1;
  }
}
