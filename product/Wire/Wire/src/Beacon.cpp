#include "Beacon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Beacon::~Beacon(){}

Beacon::Beacon()
{
    packetCaptureRunning = false;
	packetCaptureShouldStop = false;
}

void Beacon::togglePacketCapture()
{
	if(packetCaptureRunning){
		stopPacketCapture();
	}else{
		startPacketCapture();
	}
}

void Beacon::startPacketCapture()
{
	if(packetCaptureRunning) return;
	try {
		packetCaptureShouldStop = false;
		char errorBuffer[PCAP_ERRBUF_SIZE];
        
		pCapDescriptor = pcap_open_live("en0", BUFSIZ, 1, 10, errorBuffer);
		
		if(pCapDescriptor == NULL)
		{
			// TODO: Throw real exception here.
			console() << "Error with pcap_open_live()\n" << std::endl;
			return;
		}
		
		packetCaptureThread = thread( bind( &Beacon::doPacketCaptureFn, this ) );
		packetCaptureRunning = true;
	}catch(...){
		// TODO: Throw real exception here.
		console() << "Error opening device." << std::endl;
		packetCaptureRunning = false;
	}
}

void Beacon::stopPacketCapture()
{
	if(!packetCaptureRunning) return;
	packetCaptureShouldStop = true;
	packetCaptureThread.join();
	packetCaptureRunning = false;
}

void Beacon::doPacketCaptureFn()
{
	ci::ThreadSetup threadSetup;
    
	const u_char *packet;
	struct ether_header *etherHeader;
	int i;
	struct pcap_pkthdr packetHeader;
	u_char *sourceAddressPtr;
	
	while( !packetCaptureShouldStop ) {
		packet = pcap_next(pCapDescriptor, &packetHeader);
		
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

        if(pings.count(addy) == 0){
			pings[addy] = Ping( ci::Vec2f::zero() );
			rebalancePings();
        }

        pings[addy].ping();
	}
}

std::map<std::string, Ping> Beacon::getPings()
{
    return pings;
}

void Beacon::update()
{
	for(std::map<std::string, Ping>::iterator pings_it = pings.begin(); pings_it != pings.end(); pings_it++)
	{
		pings_it->second.update();
	}
}

#pragma mark - VISUAL STUFF - MOVE TO UI CLASS

void Beacon::draw()
{
//	gl::color( Color( 1.0f, 0.0f, 1.0f ) );
//	gl::drawSolidCircle( ci::Vec2f(getWindowWidth()/2.0f, getWindowHeight()/2.0f), kPacketRadius * 4.0f );

	for(std::map<std::string, Ping>::iterator pings_it = pings.begin(); pings_it != pings.end(); pings_it++)
	{
		pings_it->second.draw();
	}
}

void Beacon::rebalancePings()
{
	float angle;
	int i = 0;

	for(std::map<std::string, Ping>::iterator pings_it = pings.begin(); pings_it != pings.end(); pings_it++)
	{
		++i;
		angle = i * (360.0f / pings.size());
		pings_it->second.setAngle( angle );
	}
}

void Beacon::resize()
{
	pings.clear();
	rebalancePings();
}