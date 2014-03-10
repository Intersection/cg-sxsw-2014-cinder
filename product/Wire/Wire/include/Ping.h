#pragma once

#include <time.h>
#include <list>
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "Packet.h"

class Ping {
public:
    Ping();
    Ping( ci::Vec2f position, int index );
    ~Ping();

    void					ping();
	void					update();
	void					draw();
	void					setPosition( ci::Vec2f position );
	void					setAngle( float angle );
	void					setTextureFont( ci::gl::TextureFontRef textureFont );
	void					setAddress( std::string address );
	
	ci::Vec2f				position;
	int						index;
    time_t					timer;
    time_t					stamp;
    time_t					updateStamp;
    double					seconds;
	std::string				address;
	ci::ColorA				color;
	std::list<Packet>		packets;
	ci::gl::TextureFontRef	textureFont;

protected:
	void					updateAngle();

};
