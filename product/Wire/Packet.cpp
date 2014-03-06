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
	speed = 5.0f;
	damp = 0.9f;
}

void Packet::update()
{
	animationCounter += 10.0f; // move ahead in time, which becomes the z-axis of our 3D noise

	// Compute newest position
	if(abs(attractor.x - position.x) < kPacketRadius){
		dead = true;
		return;
	}
	
	priorPosition = position;
	
	Vec3f deriv = perlin.dfBm( Vec3f( position.x, position.y, animationCounter ) * 0.001f );
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
		// color according to velocity
		gl::color( Color( red, green, blue ) );
//		glColor3f( 0.5f + velocity.x / ( speed * 2 ), 0.5f + velocity.y / ( speed * 2 ), 0.5f + z * 0.5f );
		glVertex2f( priorPosition );
		glVertex2f( position );
	glEnd();
	
	
	// draw the particle, including its position. count on a wrapping context.
//	gl::drawSolidCircle( Vec2f(position.x, position.y), kPacketRadius );
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
