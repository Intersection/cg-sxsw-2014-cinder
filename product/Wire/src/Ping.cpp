//
//  Ping.cpp
//  Wire
//
//  Created by Toby Boudreaux on 3/5/14.
//  Copyright (c) 2014 Control Group. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Ping.h"
#include "Constants.h"

Ping::Ping(){
    
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

Ping::~Ping(){}

void Ping::ping()
{
    if(count < 10){
        count++;
    }
    
    time(&updateStamp);
}

double Ping::decay()
{
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer, updateStamp);
    return std::max(1.0, seconds);

}

