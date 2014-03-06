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

class BeaconPCAPApp : public AppBasic {
public:
	void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
	void keyDown( KeyEvent event );
	void resize();
	void update();
	void draw();
	void shutdown();
	void togglePacketCapture();
	
	gl::Texture				mTexture;
	gl::GlslProg			mShader;
	Beacon					mBeacon;

};

void BeaconPCAPApp::togglePacketCapture()
{
	mBeacon.togglePacketCapture();
}

void BeaconPCAPApp::prepareSettings( Settings *settings )
{
	settings->setFrameRate( kFrameRate );
	settings->setWindowSize( kWindowWidth, kWindowHeight );
}

void BeaconPCAPApp::shutdown()
{
	mBeacon.stopPacketCapture();
}

void BeaconPCAPApp::setup()
{
	
	try {
		mShader = gl::GlslProg( loadResource( RES_SHADER_PASSTHRU ), loadResource( RES_SHADER_FRAGMENT ) );
	} catch ( gl::GlslProgCompileExc &exc ) {
		console() << "Cannot compile shader: " << exc.what() << std::endl;
		exit(1);
	}catch ( Exception &exc ){
		console() << "Cannot load shader: " << exc.what() << std::endl;
		exit(1);
	}
	
	try {
		mTexture = gl::Texture( loadImage( loadResource( RES_GRADIENT ) ) );
	}catch ( Exception &exc ){
		console() << "Cannot load texture: " << exc.what() << std::endl;
	}
}

void BeaconPCAPApp::mouseDown( MouseEvent event ){}

void BeaconPCAPApp::keyDown( KeyEvent event )
{
	if ( event.getCode() == KeyEvent::KEY_f ){
		setFullScreen( !isFullScreen() );
	}
	
	if (event.getCode() == KeyEvent::KEY_p) {
		togglePacketCapture();
	}
}

void BeaconPCAPApp::resize()
{

}

void BeaconPCAPApp::update()
{
	mTexture = gl::Texture( );

	// Look at dots?
	
}

void BeaconPCAPApp::draw()
{
	// clear out the window with black
	gl::clear( kClearColor );

//	if( !mTexture ) return;

//	mTexture.enableAndBind();
	gl::drawSolidRect( getWindowBounds() );

	
	gl::clear( Color( 0.66f, 0.66f, 0.66f ), true );
    gl::enableAlphaBlending();
	
	std::map<std::string, Ping> pings = mBeacon.getPings();
	
	float padding = 20.0f;
	float minWidth = 10.0f;
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

//	mShader.bind();
//	mShader.uniform( "tex", 0 );
//	mShader.uniform( "bright", 0.99f );
//	mShader.uniform( "ledCount", 400.0f );
//	mShader.uniform( "aspect", kWindowHeight / kWindowWidth );
//
//	mTexture.unbind();
//	mShader.unbind();
}


CINDER_APP_BASIC( BeaconPCAPApp, RendererGl(4) )
