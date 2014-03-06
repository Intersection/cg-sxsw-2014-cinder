#pragma once

#include "cinder/Vector.h"
#include <vector>

class Packet {
public:
	Packet();

	void update();
	void draw();
	void setAttractor( ci::Vec3f attractor );
	void setColors( float red, float green, float blue );
	void setVelocity( ci::Vec3f velocity );
	
	std::vector<ci::Vec3f>	position;
	ci::Vec3f				velocity;
	ci::Vec3f				noise;
	float					radius;
	float					decay;
	float					maxDecay;
	ci::Vec3f				attractor;
	float					red;
	float					green;
	float					blue;
};
