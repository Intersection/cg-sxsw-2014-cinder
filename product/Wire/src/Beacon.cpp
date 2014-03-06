#include "Beacon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Beacon::Beacon()
{
    mPacketCaptureRunning = false;
	mPacketCaptureShouldStop = false;
}

void Beacon::togglePacketCapture()
{
	if(mPacketCaptureRunning){
		stopPacketCapture();
	}else{
		startPacketCapture();
	}
}

void Beacon::startPacketCapture()
{
	if(mPacketCaptureRunning) return;
	try {
		mPacketCaptureShouldStop = false;
		char errorBuffer[PCAP_ERRBUF_SIZE];
        
		mPCapDescriptor = pcap_open_live("en0", BUFSIZ, 1, 10, errorBuffer);
		
		if(mPCapDescriptor == NULL)
		{
			console() << "Error with pcap_open_live()\n" << std::endl;
			return;
		}
		
		mPacketCaptureThread = thread( bind( &Beacon::doPacketCaptureFn, this ) );
		mPacketCaptureRunning = true;
	}catch(...){
		console() << "Error opening device." << std::endl;
		mPacketCaptureRunning = false;
	}
}

void Beacon::stopPacketCapture()
{
	if(!mPacketCaptureRunning) return;
	mPacketCaptureShouldStop = true;
	mPacketCaptureThread.join();
	mPacketCaptureRunning = false;
}

void Beacon::doPacketCaptureFn()
{
	ci::ThreadSetup threadSetup; // instantiate this if you're talking to Cinder from a secondary thread
    
	const u_char *packet;
	struct ether_header *etherHeader;
	int i;
	struct pcap_pkthdr packetHeader;
	u_char *sourceAddressPtr;
	
	while( !mPacketCaptureShouldStop ) {
		packet = pcap_next(mPCapDescriptor, &packetHeader);
		
		if(packet == NULL)
		{
			// Didn't grab packet
			continue;
		}
		
		// Get header
		etherHeader = (struct ether_header *) packet;
		
		// Get packet type (IP, ARP, other)
		if(ntohs (etherHeader->ether_type) == ETHERTYPE_IP){
			// IP packet - in case you want to filter on these
		}else if(ntohs (etherHeader->ether_type) == ETHERTYPE_ARP){
			// ARP packet - in case you want to filter on these
		}else {
			// Other packet - in case you want to filter on these
			continue;
		}
		
		// Get the source address
		sourceAddressPtr = etherHeader->ether_shost;
		i = ETHER_ADDR_LEN;
		string addy;
		do {
			char tmp[10];
			snprintf(tmp, sizeof(tmp), "%s%x", (i == ETHER_ADDR_LEN) ? "" : ":", *sourceAddressPtr++);
			addy += tmp;
		} while(--i > 0);

        if(mPings.count(addy) == 0){
			mPings[addy] = Ping( ci::Vec2f(100.0f, 200.0f) );
			rebalancePings();
        }

        mPings[addy].ping();
	}
}

void Beacon::rebalancePings()
{
	float r = kRadius;
	float ox = kCenterX;
	float oy = kCenterY;

	float angle;
	float xPos;
	float yPos;
	int i = 0;

	for(std::map<std::string, Ping>::iterator pings_it = mPings.begin(); pings_it != mPings.end(); pings_it++)
	{
		++i;
		
		angle = i * (360.0f / mPings.size());
		xPos = r*cos(angle) + ox;
		yPos = r*sin(angle) + oy;
		pings_it->second.setPosition( ci::Vec2f( xPos, yPos ));
	}
}

Beacon::~Beacon(){}

std::map<std::string, Ping> Beacon::getPings()
{
    return mPings;
}

void Beacon::update()
{
	for(std::map<std::string, Ping>::iterator pings_it = mPings.begin(); pings_it != mPings.end(); pings_it++)
	{
		pings_it->second.update();
	}
}

void Beacon::draw()
{
	gl::color( Color( 1.0f, 0.0f, 1.0f ) );
	gl::drawSolidCircle( ci::Vec2f(kCenterX, kCenterY), kPacketRadius * 4.0f );

	for(std::map<std::string, Ping>::iterator pings_it = mPings.begin(); pings_it != mPings.end(); pings_it++)
	{
		pings_it->second.draw();
	}
}


