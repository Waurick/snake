SDL_Texture *blacktex;
SDL_Texture *darkgreentex;
SDL_Texture *redtex;
SDL_Surface *black;
SDL_Surface *darkgreen;
SDL_Surface *red;
SDL_Renderer *rend;

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
