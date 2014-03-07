#pragma once

#include "cinder/Cinder.h"
#include "cinder/Vector.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Perlin.h"

#include <vector>

using namespace ci;
using namespace ci::app;

class Packet {
public:
	Packet();
	Packet( ci::Vec2f startingLocation, ci::Color color, ci::Vec2f attractor );

	void update();
	void draw();
	void setAttractor( ci::Vec2f attractor );
	void setColor( ci::ColorA color );
	void setVelocity( ci::Vec2f velocity );
	bool isDead();
	double getDecay();
	
	ci::Vec2f				position;
	float					z;
	ci::Vec2f				priorPosition;
	ci::Vec2f				velocity;
	float					radius;
	float					decay;
	float					maxDecay;
	ci::Vec2f				attractor;
	ci::ColorA				color;
	bool					dead;
	
	Perlin					perlin;
	float					animationCounter;
	float					speed;
	float					damp;
	
	time_t					timer;
    time_t					stamp;
    double					seconds;
	double					lifespan; // in seconds

};
