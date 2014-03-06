#include "Packet.h"
#include "Constants.h"


Packet::Packet()
{
	// Initialize
}

Packet::Packet( ci::Vec2f p, float r, float g, float b, ci::Vec2f v, float d, ci::Vec2f a )
{
	position = p;
	priorPosition = p;
	red = r;
	green = g;
	blue = b;
	velocity = v;
	decay = d;
	attractor = a;
	
	perlin = Perlin();
	speed = 2.0f;
	damp = 0.89f;
}

void Packet::update()
{
	animationCounter += 5.0f;

	if(abs(attractor.x - position.x) < kPacketRadius){
		dead = true;
		return;
	}
	
	priorPosition = position;
	
	// Update position toward attractor
	position += ((attractor - position) * Vec2f(0.125f, 0.25f));

	Vec3f deriv = perlin.dfBm( Vec3f( attractor.x, attractor.y, animationCounter ) * 0.901f );
	z = deriv.z;
	Vec2f deriv2( deriv.x, deriv.y );
	deriv2.normalize();
	velocity += deriv2 * speed;
	//position += positionDelta;
	position += velocity;
	velocity *= damp;
}

void Packet::draw()
{
	
	// draw all the particles as lines from mPosition to mLastPosition
	glBegin( GL_LINES );
		gl::color( Color( red, green, blue ) );
		glVertex2f( priorPosition );
		glVertex2f( position );
		gl::drawSolidCircle( position, kPacketRadius );
	glEnd();
	gl::drawSolidCircle( position, kPacketRadius );

}

void Packet::setAttractor( ci::Vec2f a )
{
	attractor = a;
}

void Packet::setColors( float r, float g, float b )
{
	red = r;
	green = g;
	blue = b;
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
