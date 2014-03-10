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
	gl::TextureFontRef textureFont;

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
	setFullScreen(true);
	gl::enableAlphaBlending();
	textureFont = gl::TextureFont::create(Font("Menlo", 12), gl::TextureFont::Format().enableMipmapping());

	beacon.setTextureFont( textureFont );
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
    gl::enableAlphaBlending();
	
	beacon.draw();
}

CINDER_APP_BASIC( WireApp, RendererGl(8) )
