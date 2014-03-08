#include "Packet.h"
#include "Constants.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Packet::Packet(){}

Packet::Packet( ci::Vec2f s, ci::Color c, ci::Vec2f a )
{
	color = c;
	attractor = a;
	
	perlin = ci::Perlin();
	perlin.setSeed( (int32_t)clock() );
	speed = 5.0f;
	damp = 0.9f;

	startingPosition = s;
	position = s;
	priorPosition = position;
	velocity = ci::Vec2f::zero();
	
	lifespan = 5.0f;
	dead = false;
	
	time(&stamp);
}

double Packet::getDecay()
{
    time(&timer);
    
    seconds = difftime(timer, stamp);
    return std::max(1.0, seconds);
}

void Packet::update()
{

	animationCounter += 10.0f;

	if(getDecay() >= lifespan){
		dead = true;
		return;
	}
	
	priorPosition = position;
	
	// Update position toward attractor
	position += ((attractor - position) * Vec2f(0.025f, 0.1025f));

	//0.9001f
	Vec3f deriv = perlin.dfBm( Vec3f( position.x, position.y, animationCounter ) * 0.0001f );
	z = deriv.z;
	Vec2f deriv2( deriv.x, deriv.y );
	deriv2.normalize();
	velocity += deriv2 * speed;

	position += velocity;
	velocity *= damp;
	color.a = 1.0f - (getDecay() / lifespan);
}

void Packet::draw()
{
	gl::enableAlphaBlending();
	
	// draw all the particles as lines from mPosition to mLastPosition
	glBegin( GL_LINES );
		gl::color( color );
		//glVertex2f( startingPosition );
		glVertex2f( priorPosition );
		glVertex2f( position );
	glEnd();
	
//	gl::drawSolidCircle( position, kPacketRadius/2 );
//	gl::drawSolidCircle( priorPosition, kPacketRadius/2 );

	//gl::drawSolidCircle( position, kPacketRadius/4.0f );
	
	gl::disableAlphaBlending();

}

void Packet::setAttractor( ci::Vec2f a )
{
	attractor = a;
}

void Packet::setColor( ci::ColorA c )
{
	color = ColorA( c.r, c.g, c.b, 0.5f );
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

void Packet::setStartingPosition( ci::Vec2f p )
{
	startingPosition = p;
}

