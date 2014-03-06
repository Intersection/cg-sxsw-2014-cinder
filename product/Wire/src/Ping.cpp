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
    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    
    xPos = dist(gen) * kWindowWidth;
    yPos = dist(gen) * kWindowHeight;

    mRed = dist(gen);
    mGreen = dist(gen);
    mBlue = dist(gen);

    count = 1;
    
    time(&stamp);
}

Ping::~Ping(){}

void Ping::ping()
{
	count++;
    time(&updateStamp);
	// Add a new packet particle
	ci::Vec2f attractor = ci::Vec2f( kWindowWidth - 20.0f, yPos );
	mPackets.push_back(Packet(
							  Vec2f( 0.0f, yPos),
							  mRed, mGreen, mBlue,
							  ci::Vec2f(0.0125f, 0.0125f),
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
}

void Ping::draw()
{
	// Draw the origin point

	gl::color( Color( mRed, mGreen, mBlue ) );
	float x = 20.0f;
	float y = yPos;
	gl::drawSolidCircle( Vec2f(x, y), 10.0f );

	// Run through list of packets & draw them
	for( std::list<Packet>::iterator packets_it = mPackets.begin(); packets_it != mPackets.end(); ++packets_it ){
		packets_it->draw();
	}
}

