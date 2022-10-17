#include "header.h" 
#include "timer.cpp"
#include "texture.cpp"
#include "dot.cpp"
#include "SDLhandler.cpp"
#include "states.cpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

extern SDL_Window* gWindow ; 
extern SDL_Renderer* gRenderer ; 
extern TTF_Font* gFont ;  
extern LTexture gDotTexture ; 
extern bool Strike ;
extern Dot p[10];

void handle();

int main()
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		events();	
	}
	//Free resources and close SDL
	close();

	return 0;
}