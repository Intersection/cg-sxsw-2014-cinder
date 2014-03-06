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
    ~Ping();

    double decay();
    void ping();
	void update();
	void draw();

    float xPos;
    float yPos;
    int count;
    
    time_t timer;
    time_t stamp;
    time_t updateStamp;

    double seconds;
    
    float mRed;
    float mGreen;
    float mBlue;
    
	std::list<Packet> mPackets;
	
};
