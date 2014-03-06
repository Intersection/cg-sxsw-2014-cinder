#pragma once

#include "cinder/Cinder.h"
#include "cinder/Vector.h"
#include "cinder/app/AppBasic.h"

#include <vector>

using namespace ci;
using namespace ci::app;

class Packet {
public:
	Packet();
	Packet( ci::Vec3f position, float red, float green, float blue, ci::Vec3f velocity, float decay, ci::Vec3f attractor );

	void update();
	void draw();
	void setAttractor( ci::Vec3f attractor );
	void setColors( float red, float green, float blue );
	void setVelocity( ci::Vec3f velocity );
	bool isDead();
	
	ci::Vec3f				position;
	ci::Vec3f				velocity;
	ci::Vec3f				noise;
	float					radius;
	float					decay;
	float					maxDecay;
	ci::Vec3f				attractor;
	float					red;
	float					green;
	float					blue;
	bool					dead;
};
