#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

//Govori opercijskom sustavu da koristi najbrzu grafičku karticu
extern "C" 
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern "C"
{
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

//Screen dimension constants
bool FULLSCREEN = 0;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

const int DISPLAY_FPS = 60;
const int DISPLAY_FRAME_TIME = 1000 / DISPLAY_FPS;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current time start time
Uint32 startTime = 0;

bool keys[1024];

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("PiK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC);

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			SDL_SetWindowResizable(gWindow, SDL_TRUE);

			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
        	if( gRenderer == NULL )
        	{
            	printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            	success = false;
        	}

        	else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }


            }
		}
		

	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	srand( time(NULL) );
	
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT ) //User requests quit
				{
					quit = true;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        	SDL_RenderClear( gRenderer );

			//Update screen
        	SDL_RenderPresent( gRenderer );
		
			if(SDL_GetTicks() - startTime < DISPLAY_FRAME_TIME){
				SDL_Delay( DISPLAY_FRAME_TIME - (SDL_GetTicks() - startTime) );
			}

			startTime = SDL_GetTicks();

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}