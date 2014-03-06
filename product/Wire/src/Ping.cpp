#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Ping.h"
#include "Constants.h"
#include "Packet.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

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
    
    mRed = dist(gen);
    mGreen = dist(gen);
    mBlue = dist(gen);
	
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
	ci::Vec2f attractor = ci::Vec2f( kCenterX, kCenterY );
	mPackets.push_back(Packet(
							  position,
							  mRed, mGreen, mBlue,
							  ci::Vec2f (100.0f, 200.0f ),
							  (float)count,
							  attractor
						)
	);
}

double Ping::decay()
{
    time(&timer);
    
    seconds = difftime(timer, updateStamp);
    return std::max(1.0, seconds);
}

void Ping::update()
{
	// Run through list of packets & update them
	for( std::list<Packet>::iterator packets_it = mPackets.begin(); packets_it != mPackets.end(); ++packets_it ){
		if(packets_it->isDead()){
			mPackets.erase(packets_it);
		}else{
			packets_it->update();
		}
	}
	
	if(abs(targetPosition.x - position.x) < 5.0f){
		position = targetPosition;
	}else{
		position += (targetPosition - position) * 0.125f;
	}
	
	
}

void Ping::draw()
{
	// Draw the origin point

	gl::color( Color( mRed, mGreen, mBlue ) );

	gl::drawSolidCircle( position, 10.0f );

	// Run through list of packets & draw them
	for( std::list<Packet>::iterator packets_it = mPackets.begin(); packets_it != mPackets.end(); ++packets_it ){
		packets_it->draw();
	}
}

void Ping::setPosition( ci::Vec2f p )
{
	targetPosition = p;
}
