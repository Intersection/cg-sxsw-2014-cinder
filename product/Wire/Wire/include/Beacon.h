#include <pcap/pcap.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include "cinder/Thread.h"
#include "cinder/app/AppBasic.h"
#include "Constants.h"
#include "cinder/gl/TextureFont.h"

#include "Ping.h"

class Beacon {
public:
    Beacon();
    ~Beacon();
    
    void togglePacketCapture();
	void startPacketCapture();
	void stopPacketCapture();
	void update();
	void draw();
	void resize();
	void setTextureFont( gl::TextureFontRef textureFont );


    std::map<std::string, Ping>     getPings();

	bool                            packetCaptureRunning;
	bool                            packetCaptureShouldStop;
	std::thread                     packetCaptureThread;

    std::map<std::string, Ping>     pings;
	pcap_t*                         pCapDescriptor;
	float							spacing;
	gl::TextureFontRef				textureFont;


protected:
	void doPacketCaptureFn();
	void rebalancePings();


};