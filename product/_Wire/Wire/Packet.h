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
	Packet( ci::Vec2f position, ci::Color color, ci::Vec2f velocity, float decay, ci::Vec2f attractor );

	void update();
	void draw();
	void setAttractor( ci::Vec2f attractor );
	void setColor( ci::Color color );
	void setVelocity( ci::Vec2f velocity );
	bool isDead();
	
	ci::Vec2f				position;
	float					z;
	ci::Vec2f				priorPosition;
	ci::Vec2f				velocity;
	float					radius;
	float					decay;
	float					maxDecay;
	ci::Vec2f				attractor;
	ci::Color				color;
	bool					dead;
	
	Perlin					perlin;
	float					animationCounter;
	float					speed;
	float					damp;
	
};
