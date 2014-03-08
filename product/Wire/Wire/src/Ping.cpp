#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Ping.h"
#include "Constants.h"
#include "Packet.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include <cmath>        // std::abs

using namespace ci;
using namespace ci::app;

Ping::Ping()
{
}

Ping::Ping( ci::Vec2f p )
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    
	color = ci::ColorA( dist(gen), dist(gen), dist(gen), 0.7f );
	
    count = 1;

    time(&stamp);
	position = p;
}


Ping::~Ping(){}

void Ping::ping()
{
	count++;
    time(&updateStamp);
	// Add a new packet particle
	ci::Vec2f attractor = ci::Vec2f( getWindowWidth() / 2.0f, getWindowHeight() / 2.0f );

	if( packets.size() > 20 ){
		//packets.pop_back(); // Kill the oldest.
	}


	packets.push_back(Packet( position,
							  color,
							  attractor
						)
	);
}

void Ping::update()
{
	std::list<Packet>::iterator packets_it = packets.begin();
	while(packets_it != packets.end())
	{
		bool dead = packets_it->isDead();
		
		if(dead) {
			packets.erase(packets_it++);
		}else{
			packets_it->update();
			packets_it->setStartingPosition( position + ci::Vec2f( 160.0f, 10.0f ) );
			++packets_it;
		}
	}

	if(abs(targetPosition.x - position.x) < 2.0f && abs(targetPosition.y - position.y) < 2.0f){
		position = targetPosition;
	}else{
		position += (targetPosition - position) * 0.125f;
	}
	
	
}

void Ping::draw()
{
	// Draw the origin point
	gl::enableAlphaBlending();
	gl::color( color );

	float ulx, uly, lrx, lry;

	ulx = position.x;
	uly = position.y;
	lrx = ulx + 40.0f;
	lry = uly + 20.0f;
	
	Rectf iconRect( ulx, uly, lrx, lry );
	gl::drawSolidRect( iconRect );
	Rectf textRect( lrx + 10.0f, uly + 15.0f, lrx + 130.0f, lry  );
	textureFont->drawStringWrapped( address, textRect );

	
	
	// Run through list of packets & draw them
	for( std::list<Packet>::iterator packets_it = packets.begin(); packets_it != packets.end(); ++packets_it ){
		packets_it->draw();
	}
	gl::disableAlphaBlending();

}

void Ping::setPosition( ci::Vec2f p )
{
	targetPosition = p;
}

void Ping::setTextureFont( gl::TextureFontRef t )
{
	textureFont = t;
}

void Ping::setAddress( std::string a )
{
	address = a;
}


