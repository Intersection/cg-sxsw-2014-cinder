#pragma once

#include <vector>
#include "cinder/Cinder.h"
#include "cinder/Vector.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Perlin.h"

class Packet {
public:
	Packet();
	Packet( ci::Vec2f startingLocation, ci::Color color, ci::Vec2f attractor );

	void		update();
	void		draw();
	void		setAttractor( ci::Vec2f attractor );
	void		setColor( ci::ColorA color );
	void		setVelocity( ci::Vec2f velocity );
	bool		isDead();
	double		getDecay();
	void		setStartingPosition( ci::Vec2f position );
	
	ci::Vec2f	position;
	ci::Vec2f	priorPosition;
	ci::Vec2f	startingPosition;

	float		z;
	ci::Vec2f	velocity;
	float		radius;
	ci::Vec2f	attractor;
	ci::ColorA	color;
	bool		dead;
	
	ci::Perlin	perlin;
	float		animationCounter;
	float		speed;
	float		damp;
	
	time_t		timer;
    time_t		stamp;
    double		seconds;
	double		lifespan; // in seconds

};
