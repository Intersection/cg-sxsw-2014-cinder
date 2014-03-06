#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"

#include "cinder/params/Params.h"

#include "Resources.h"
#include "Constants.h"
#include "Beacon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WireApp : public AppBasic {
public:
	void prepareSettings( Settings *settings );
	void setup();
	void keyDown( KeyEvent event );
	void resize();
	void update();
	void draw();
	void shutdown();
	void togglePacketCapture();
	
	Beacon					mBeacon;
};

void WireApp::togglePacketCapture()
{
	mBeacon.togglePacketCapture();
}

void WireApp::prepareSettings( Settings *settings )
{
	settings->setFrameRate( kFrameRate );
	settings->setWindowSize( kWindowWidth, kWindowHeight );
}

void WireApp::shutdown()
{
	mBeacon.stopPacketCapture();
}

void WireApp::setup(){}

void WireApp::keyDown( KeyEvent event )
{
	if ( event.getCode() == KeyEvent::KEY_f ){
		setFullScreen( !isFullScreen() );
	}
	
	if (event.getCode() == KeyEvent::KEY_p) {
		togglePacketCapture();
	}
}

void WireApp::resize(){}

void WireApp::update(){}

void WireApp::draw()
{
	gl::clear( kClearColor );

	gl::drawSolidRect( getWindowBounds() );

	gl::clear( Color( 0.01f, 0.01f, 0.01f ), true );
    gl::enableAlphaBlending();
	
	std::map<std::string, Ping> pings = mBeacon.getPings();
	
	float padding = 20.0f;
	float width = 0.0f;
	int index = 0;
	int count = pings.size();
	float height = (kWindowHeight - (padding * 2.0f)) / count;
	float x, y;

	for(std::map<std::string, Ping>::iterator points_it = pings.begin(); points_it != pings.end(); points_it++)
    {
		++index;

        x = padding * 2.0f;
        y = (padding * 2.0f) + (index * height);

		gl::color( Color( points_it->second.mRed, points_it->second.mGreen, 1.0f ) );

		width = padding * points_it->second.count;
		gl::drawSolidRect( Rectf(x, y, width, height), true);
    }
}

CINDER_APP_BASIC( WireApp, RendererGl(4) )
