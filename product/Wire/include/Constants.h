#pragma once
#include "cinder/Color.h"

static const float kWindowWidth		= 1280.0f;
static const float kWindowHeight	= 1024.0f;

static const float kCenterX			= kWindowWidth/2.0f;
static const float kCenterY			= kWindowHeight/2.0f;

static const float kPingRadius		= 5.0f;
static const float kPacketRadius	= 5.0f;

static const float kFrameRate		= 60.0f;

static const float kRadius			= 300.0f;

static const ci::Color kClearColor	= ci::Color(0.0f, 0.0f, 0.0f);
static const float kCaptureWidth	= 640.0f;
static const float kCaptureHeight	= 480.0f;

static const int kMaxPings			= 20;