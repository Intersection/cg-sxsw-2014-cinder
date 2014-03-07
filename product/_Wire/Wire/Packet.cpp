#include "Packet.h"
#include "Constants.h"
#include <random>
#include <algorithm>


Packet::Packet()
{
	// Initialize
}

Packet::Packet( ci::Vec2f p, ci::Color c, ci::Vec2f v, float d, ci::Vec2f a )
{
	position = p;
	priorPosition = p;
	color = c;

	velocity = v;
	decay = d;
	attractor = a;
	
	perlin = Perlin();
	perlin.setSeed( clock() );
	speed = 5.0f;
	damp = 0.9f;
}

void Packet::update()
{
	std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

	animationCounter += 10.0f;

	if(abs((attractor.x) - position.x) < kPacketRadius && abs((attractor.y) - position.y) < kPacketRadius){
		dead = true;
		console() << "DEAD" << std::endl;
		return;
	}
	
	priorPosition = position;
	
	// Update position toward attractor
	position += ((attractor - position) * Vec2f(0.125f, 0.125f));

	Vec3f deriv = perlin.dfBm( Vec3f( position.x, position.y, animationCounter ) * 0.0001f );
	z = deriv.z;
	Vec2f deriv2( deriv.x, deriv.y );
	deriv2.normalize();
	velocity += deriv2 * speed;

	position += velocity;
	velocity *= damp;
}

void Packet::draw()
{
	
	// draw all the particles as lines from mPosition to mLastPosition
	glBegin( GL_LINES );
		gl::color( color );
		glVertex2f( priorPosition );
		glVertex2f( position );
		gl::drawSolidCircle( position, kPacketRadius );
	glEnd();
	gl::drawSolidCircle( position, kPacketRadius/4.0f );

}

void Packet::setAttractor( ci::Vec2f a )
{
	attractor = a;
}

void Packet::setColor( ci::Color c )
{
	color = c;
}

void Packet::setVelocity( ci::Vec2f v )
{
	velocity = v;
}

bool Packet::isDead()
{
	//if(dead) console() << "DEAD PACKET" << std::endl;
	return dead;
}
