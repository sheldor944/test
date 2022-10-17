#include "header.h"

struct Circle 
{
	int x , y ; 
	int r ;
};

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


bool checkCollision(Circle& a, Circle& b);
double distanceSquared( int x1, int y1, int x2, int y2 );


class Dot
{
	public:
		static const int DOT_WIDTH = 20 ; 
		static const int DOT_HEIGHT = 20 ;

		static const int DOT_VEL = 2 ; 


		void initialize(int id, int x , int y );
		void handleEvent( SDL_Event& e);
		void move( int id );
		void handleCollision( Dot& a , Dot& b );

		bool potCheck();

		void render();

		Circle& getCollider();

	// private:
		double mPosX , mPosY ; 

		double mVelX , mVelY ;

		double absVX , absVY ; 

		Circle mCollider ; 

		double speed = 0 ; 

		void shiftColliders(); 
};

extern LTexture gDotTexture ; 
bool strike =false ;
Dot p[10];


void Dot::initialize(int id , int x , int y)
{
	mPosX = x;
	mPosY = y ;

	mCollider.r = DOT_HEIGHT /2 ; 
	mCollider.x =x ;
	mCollider.y = y ;


	mVelX = 0 ; 
	mVelY = 0 ; 
	
	shiftColliders();

}

void Dot::handleCollision(Dot& a , Dot& b )
{
	Circle circle1 = a.getCollider();
	Circle circle2 = b.getCollider();

	double n_x = circle1.x - circle2.x;
    double n_y = circle1.y - circle2.y;

    double c = (n_x * (b.mVelX - a.mVelX) + n_y * (b.mVelY - a.mVelY)) / (distanceSquared(n_x, n_y, 0, 0));

	a.mVelX += c * n_x;
    b.mVelX -= c * n_x;

    a.mVelY += c * n_y;
    b.mVelY -= c * n_y;

	 shiftColliders();

}

void Dot::handleEvent(SDL_Event& e )
{
	if(strike == false)
	{
		if(e.type == SDL_KEYDOWN && e.key.repeat == 0 )
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_UP: mVelY -= DOT_VEL ; break ; 
				case SDLK_DOWN: mVelY += DOT_VEL ; break ; 
				case SDLK_LEFT : mVelX -= DOT_VEL ; break; 
				case SDLK_RIGHT: mVelX += DOT_VEL ; break ; 
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_UP: mVelY += DOT_VEL; break;
				case SDLK_DOWN: mVelY -= DOT_VEL; break;
				case SDLK_LEFT: mVelX += DOT_VEL; break;
				case SDLK_RIGHT: mVelX -= DOT_VEL; break;
			}
		}

		if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		{
			strike = true ; 
			speed++;
		}
	}
	if(strike )
	{
		
		if(e.type== SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		{	
			speed++;
			//  cout<<x<<" "<<y<<endl;
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym ==SDLK_SPACE )
		{
			int x , y ; 
			SDL_GetMouseState(&x, &y);
			speed*=5;
			mVelX = speed * ( x-mPosX)/sqrt(distanceSquared(x,y,mPosX,mPosY));
			absVX = abs(mVelX);
			mVelY = speed * ( y-mPosY)/sqrt(distanceSquared(x,y,mPosX,mPosY));
			absVY = abs(mVelY);
			speed = 0 ;
		}
        
	}
}


void Dot::move(int id )
{

	if( id!= 0 )
	{
		mPosX+=mVelX;
		mPosY+=mVelY;

		if(mPosX <= DOT_HEIGHT && mPosY<= DOT_WIDTH)
		{
			mPosX = -10 ;
			mPosY = -10 ;
		}
		else if ( mPosX >= SCREEN_WIDTH-DOT_WIDTH && mPosY >= SCREEN_HEIGHT - DOT_HEIGHT)
		{
			mPosX = SCREEN_WIDTH + 10 ; 
			mPosY = SCREEN_HEIGHT + 10 ;
		}
		else if (mPosX >= SCREEN_WIDTH - DOT_WIDTH && mPosY <= DOT_HEIGHT)
		{
			mPosX = SCREEN_WIDTH + 10 ; 
			mPosY = -10;
		}
		else if (mPosX<= DOT_WIDTH && mPosY >= SCREEN_HEIGHT - DOT_HEIGHT)
		{
			mPosX = -10 ; 
			mPosY = SCREEN_HEIGHT + 10 ;
		}
		else{
			mPosX-=mVelX;
			mPosY-=mVelY;
		}
	}

	for(int i = 0 ; i< 5 ; i++)
	{
		if(id==i)
		{
			continue;
		}
		mPosX+=mVelX ; 
		shiftColliders();
		
		if((mPosX  - mCollider.r < 0 ) || (mPosX + mCollider.r > SCREEN_WIDTH)  )
		{
			mPosX -= mVelX;
			if(strike)mVelX= (-mVelX);
			shiftColliders();
		}
		if(checkCollision(p[id].getCollider() , p[i].getCollider()))
		{
			
			if(!strike){
				mPosX -= mVelX;
				shiftColliders();
			}
		}
		mPosY += mVelY ; 
		shiftColliders();
		if( ( mPosY  - mCollider.r< 0 ) || ( mPosY + mCollider.r > SCREEN_HEIGHT) )
		{
			mPosY -=mVelY ; 
			if(strike)mVelY = -mVelY ;
			shiftColliders();
		}
		if(checkCollision(p[id].getCollider() , p[i].getCollider()))
		{
			if(!strike){
				mPosY -= mVelY;
				shiftColliders();
			}
		}
		if(strike == true )
		{
			// cout<<"hello\n";
			if(checkCollision(p[id].getCollider()  , p[i].getCollider() ))
			{
				mPosX-=mVelX;
				mPosY-=mVelY;
				// cout<<"hellfo \n";
				handleCollision(p[id],p[i]);
			}

			mVelX-= .02 * mVelX;
			mVelY-= .02 * mVelY;

			if(abs(mVelX) < .05 )
			{
				mVelX = 0 ; 
			}
			if( abs(mVelY) < .05)
			{
				mVelY = 0 ;
			}
		}
	}
	// speed--;
}

void Dot::shiftColliders()
{
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

Circle& Dot::getCollider()
{
	return mCollider;
}

void Dot::render()
{
	gDotTexture.render(mPosX - mCollider.r, mPosY-mCollider.r );
}


double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

bool checkCollision(Circle& a, Circle& b)
{
	int totalRadiusSquared = a.r + b.r ; 

	totalRadiusSquared *=totalRadiusSquared ;

	// cout<<"check to hocceh \n";

	if(distanceSquared (a.x , a.y , b.x , b.y ) < (totalRadiusSquared))
	{
		return true ; 
	} 
	return false ;

}