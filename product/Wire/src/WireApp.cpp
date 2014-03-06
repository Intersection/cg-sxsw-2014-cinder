#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
	
	Beacon	mBeacon;
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

void WireApp::update(){
	mBeacon.update();
}

void WireApp::draw()
{
	gl::clear( kClearColor );

	gl::drawSolidRect( getWindowBounds() );

	gl::clear( Color( 0.01f, 0.01f, 0.01f ), true );
    gl::enableAlphaBlending();
	
	mBeacon.draw();
}

CINDER_APP_BASIC( WireApp, RendererGl(4) )
