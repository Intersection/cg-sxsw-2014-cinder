#include "Packet.h"


Packet::Packet()
{
	// Initialize
}

void Packet::update()
{
	// Compute newest position
}

void Packet::draw()
{
	// draw the particle, including its position. count on a wrapping context.
}

void Packet::setAttractor( ci::Vec3f a )
{
	attractor = a;
}

void Packet::setColors( float r, float g, float b )
{
	red = r;
	green = g;
	blue = b;
}

void Packet::setVelocity( ci::Vec3f v )
{
	velocity = v;
}
