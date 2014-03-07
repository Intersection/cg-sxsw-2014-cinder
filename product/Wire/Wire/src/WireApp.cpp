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

	Beacon	beacon;
};

void WireApp::togglePacketCapture()
{
	beacon.togglePacketCapture();
}

void WireApp::prepareSettings( Settings *settings )
{
	settings->setFrameRate( kFrameRate );
	settings->setWindowSize( kWindowWidth, kWindowHeight );
}

void WireApp::shutdown()
{
	beacon.stopPacketCapture();
}

void WireApp::setup(){
	gl::enableAlphaBlending();
}

void WireApp::keyDown( KeyEvent event )
{
	if ( event.getCode() == KeyEvent::KEY_f ){
		setFullScreen( !isFullScreen() );
	}
	
	if (event.getCode() == KeyEvent::KEY_p) {
		togglePacketCapture();
	}
}

void WireApp::resize()
{
	beacon.resize();
}

void WireApp::update(){
	beacon.update();
}

void WireApp::draw()
{
	gl::clear( kClearColor );

	gl::drawSolidRect( getWindowBounds() );

	gl::clear( Color( 0.01f, 0.01f, 0.01f ), true );
    gl::enableAlphaBlending();
	
	beacon.draw();
}

CINDER_APP_BASIC( WireApp, RendererGl(0) )
