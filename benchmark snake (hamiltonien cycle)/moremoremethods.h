SDL_Texture *blacktex;
SDL_Texture *darkgreentex;
SDL_Texture *redtex;
SDL_Surface *black;
SDL_Surface *darkgreen;
SDL_Surface *red;
SDL_Renderer *rend;
#define SIZE (20)
extern int head[2];
extern int gametime;
extern int ie;

void createtile(int sizer)
{
	red = SDL_CreateRGBSurface(0, sizer, sizer, 32, 0, 0, 0, 0);
	SDL_FillRect(red, 0, SDL_MapRGB(red->format, 255, 0, 0));
	black = SDL_CreateRGBSurface(0, sizer, sizer, 32, 0, 0, 0, 0);
	SDL_FillRect(black, 0, SDL_MapRGB(black->format, 20, 20, 20));
	darkgreen = SDL_CreateRGBSurface(0, sizer, sizer, 32, 0, 0, 0, 0);
	SDL_FillRect(darkgreen, 0, SDL_MapRGB(darkgreen->format, 0, 125, 0));
	blacktex = SDL_CreateTextureFromSurface(rend, black);
	darkgreentex = SDL_CreateTextureFromSurface(rend, darkgreen);
	redtex = SDL_CreateTextureFromSurface(rend, red);
	SDL_FreeSurface(black);
	SDL_FreeSurface(darkgreen);
	SDL_FreeSurface(red);
}

SDL_Texture *chooser(int choserr)
{
	if (choserr==0)
	{
		return blacktex;
	}
	else if (choserr==1)
	{
		return darkgreentex;
	}
	else
	{
		return redtex;
	}
}

void ai(void)
{
	if (gametime < 11)
	{
		ie = 3;
	}
	else
	{
		if (head[1] == 20)
		{
			ie = 2;
			if (head[0] == 1) {
				ie = 0;
			}
		}
		else
		{
			if (head[0]%2==1)
			{
				ie = 0;
				if (head[1]==1)
				{
					ie = 3;
				}
			}
			else
			{
				ie = 1;
				if (head[1]==19)
				{
					ie = 3;
					if (head[0]==20) {
						ie = 1;
					}
				}
			}
		}
	}
	gametime++;
}
