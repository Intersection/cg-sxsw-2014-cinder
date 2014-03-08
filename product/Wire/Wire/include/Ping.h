//
//  Ping.h
//  Wire
//
//  Created by Toby Boudreaux on 3/5/14.
//  Copyright (c) 2014 Control Group. All rights reserved.
//
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include "Packet.h"
#include <list>

class Ping {
public:
    Ping();
    Ping( ci::Vec2f position );
    ~Ping();

    void ping();
	void update();
	void draw();
	void setPosition( ci::Vec2f position );
	void setAngle( float angle );

	ci::Vec2f position;
	ci::Vec2f targetPosition;

    int count;

    time_t timer;
    time_t stamp;
    time_t updateStamp;

    double seconds;

	ci::ColorA color;

	std::list<Packet> packets;

protected:
	void updateAngle();

};
