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
    
	color = ci::Color( dist(gen), dist(gen), dist(gen) );
	
    count = 1;
    
    time(&stamp);
	position = p;
}


Ping::~Ping(){}

void Ping::ping()
{
	angle = 0.0f;
	count++;
    time(&updateStamp);
	// Add a new packet particle
	ci::Vec2f attractor = ci::Vec2f( getWindowWidth() / 2.0f, getWindowHeight() / 2.0f );
	packets.push_back(Packet(
							  position,
							  color,
							  ci::Vec2f::zero(),
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
	for( std::list<Packet>::iterator packets_it = packets.begin(); packets_it != packets.end(); ++packets_it ){
		if( packets.size() > 20 ){
			// pop some off
			packets.pop_back();
		}

		if(packets_it->isDead()){
			packets.erase(packets_it);
		}else{
			packets_it->update();
		}
	}
	
	if(abs(targetAngle - angle) < 15.0f){
		angle = targetAngle;
	}else{
		angle += (targetAngle - angle) * 0.000125f;
		updateAngle();
	}
}

void Ping::draw()
{
	// Draw the origin point

	gl::color( color );

	gl::drawSolidCircle( position, 10.0f);// - decay() );

	// Run through list of packets & draw them
	for( std::list<Packet>::iterator packets_it = packets.begin(); packets_it != packets.end(); ++packets_it ){
		packets_it->draw();
	}
}

void Ping::setAngle( float a )
{
	targetAngle = a;
}

void Ping::updateAngle()
{
	angle = targetAngle;
	
	float r = kRadius;
	float ox = getWindowWidth()	/ 2.0f;
	float oy = getWindowHeight() / 2.0f;
	
	float xPos;
	float yPos;
	xPos = r*cos(angle) + ox;
	yPos = r*sin(angle) + oy;
	position = Vec2f( xPos, yPos );
	
}

void Ping::setPosition( ci::Vec2f p )
{
	targetPosition = p;
}
