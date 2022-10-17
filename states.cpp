#include "header.h" ;

int GameState = 0 ;

extern SDL_Window* gWindow ; 
extern SDL_Renderer* gRenderer ; 
extern TTF_Font* gFont ;  
extern LTexture gDotTexture ; 
extern bool Strike ;
extern Dot p[10];


void events ()
{
    //Load media
		if( !loadMedia("dot.bmp") )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

			//Current time start time
			Uint32 startTime = 0;

			//In memory text stream
			std::stringstream timeText;

			LTimer fpsTImer ;
			
			p[0].initialize(0,20,20);
			p[1].initialize(1,SCREEN_WIDTH/2 , SCREEN_HEIGHT/2);
			p[2].initialize(2,SCREEN_WIDTH/2 + Dot::DOT_WIDTH , SCREEN_HEIGHT/2 );
			p[3].initialize(3,SCREEN_WIDTH/2 + Dot::DOT_WIDTH , SCREEN_HEIGHT/2 + Dot::DOT_HEIGHT );
			p[4].initialize(4,SCREEN_WIDTH/2 + 50 , SCREEN_HEIGHT/2 + 50 );
			
			

			//While application is running
			while( !quit )
			{
				if(GameState == 0 )
				{
					LTexture screen ;
					SDL_RenderClear( gRenderer );
					screen.loadFromFile("mainMenu.jpeg");

					// loadMedia("mainMenu.jpeg");
					screen.render(0,0);
					// SDL_RenderClear(gRenderer);
					SDL_RenderPresent( gRenderer );
					while( SDL_PollEvent (&e) != 0)
					{
						if(e.type == SDL_QUIT)
						{
							quit = true ;
						}
						else{
							int mouseX,mouseY ;
							SDL_GetMouseState(&mouseX , &mouseY ) ;
							if(mouseX>=  909 and mouseX <= 1180 and mouseY >= 416 and mouseY <= 512 and e.type == SDL_MOUSEBUTTONDOWN)
							{
								GameState = 2 ;
								cout<<"change hoise kintu \n";
								// break;
							}
							else if (mouseX>=  909 and mouseX <= 1180 and mouseY >= 578 and mouseY <= 675 and e.type == SDL_MOUSEBUTTONDOWN)
							{
								GameState = 1 ;
							}
							if(e.type == SDL_MOUSEMOTION)
							{
								cout<<mouseX<<" "<<mouseY<<endl;
							}
						}
					}
				
				}
				if(GameState == 1)
				{
					cout<<"about a aise \n";
					LTexture screen ; 
					SDL_RenderClear( gRenderer );
					screen.loadFromFile("about.jpg");
					screen.render( 0 , 0 );
					SDL_RenderPresent( gRenderer );

					while( SDL_PollEvent (&e) != 0)
					{
						if(e.type == SDL_QUIT)
						{
							quit = true ;
						}
					}
				}
				if(GameState == 2)
				{
                    LTexture screen ; 
                    SDL_RenderClear(gRenderer);
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    screen.loadFromFile("background.jpg");
                    screen.render(0,0);
                   

					//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					p[0].handleEvent(e);
				}
				p[0].move( 0);
				p[1].move(1);
				p[2].move(2);
				p[3].move(3);
				p[4].move(4);
				
				//Clear screen
				
				// SDL_RenderClear( gRenderer );

				// //Render wall
				// // SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );		
				// // SDL_RenderDrawRect( gRenderer, &wall );
				
				// //Render dots
				p[0].render();
				p[1].render();
				p[2].render();
				p[3].render();
				p[4].render();
				//Update screen
				SDL_RenderPresent( gRenderer );
				}
			}
		}
}