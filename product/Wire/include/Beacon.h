#include <pcap/pcap.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include "cinder/Thread.h"
#include "cinder/app/AppBasic.h"
#include "Constants.h"

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

    std::map<std::string, Ping>     getPings();

	bool                            mPacketCaptureRunning;
	bool                            mPacketCaptureShouldStop;
	std::thread                     mPacketCaptureThread;

    std::map<std::string, Ping>     mPings;
	pcap_t*                         mPCapDescriptor;

protected:
	void doPacketCaptureFn();

};