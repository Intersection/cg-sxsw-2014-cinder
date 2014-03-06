//
//  MACDot.cpp
//  BeaconPCAP
//
//  Created by Toby Boudreaux on 3/5/14.
//  Copyright (c) 2014 Control Group. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Fbo.h"
#include "cinder/ImageIo.h"
#include <cstdlib>
#include "cinder/params/Params.h"

#include "Resources.h"
#include "Constants.h"
#include <ctime>
#include "MACDot.h"
#include <random>
#include <algorithm>

using namespace ci;
using namespace ci::app;
using namespace std;

MACDot::MACDot(){
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    /* This is where you define the number generator for unsigned long long: */
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    
    xPos = dist(gen);
    //yPos = dist(gen);
    yPos = 0.5f;

    mRed = dist(gen);
    mGreen = dist(gen);
    mBlue = dist(gen);

    count = 1;
    
    time(&stamp);
    
}

MACDot::~MACDot(){}

void MACDot::ping()
{
    if(count < 10){
        count++;
    }
    
    time(&updateStamp);
}

double MACDot::decay()
{
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer, updateStamp);
    return std::max(1.0, seconds);

}

