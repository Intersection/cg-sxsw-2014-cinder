#include "Packet.h"
#include "Constants.h"

Packet::Packet()
{
	// Initialize
}

Packet::Packet( ci::Vec3f p, float r, float g, float b, ci::Vec3f v, float d, ci::Vec3f a )
{
	position = p;
	red = r;
	green = g;
	blue = b;
	velocity = v;
	decay = d;
	attractor = a;
}

void Packet::update()
{
	// Compute newest position
	if(abs(attractor.x - position.x) < kPacketRadius){
		dead = true;
		return;
	}

	console() << "delta: " << abs(attractor.x - position.x) << std::endl;
	
	position.x += ((attractor.x - position.x) * velocity.x);
}

void Packet::draw()
{
	// draw the particle, including its position. count on a wrapping context.
	gl::color( Color( red, green, blue ) );
	gl::drawSolidCircle( Vec2f(position.x, position.y), kPacketRadius );
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

bool Packet::isDead()
{
	//if(dead) console() << "DEAD PACKET" << std::endl;
	return dead;
}
