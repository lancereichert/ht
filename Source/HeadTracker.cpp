// HeadTracker.cpp
// Author: Lance Reichert
// November 24th, 2015

#include <iostream>
#include <iomanip>
#include "HeadTracker.h"


HeadTracker::HeadTracker()
: lastTimeStampMs(0)
, samplingRateHz(0)
, tc(0.7)
{
	// Try and open default path
	String defaultPath("/dev/tty.usbmodem1411");
	SerialPortConfig portConfig(115200,
								8, 
								SerialPortConfig::SERIALPORT_PARITY_NONE,
								SerialPortConfig::STOPBITS_1,
								SerialPortConfig::FLOWCONTROL_NONE);

	port = new SerialPort(defaultPath, portConfig);

	if(port->exists()) {
		stream = new SerialPortInputStream(port);
		stream->setNotify(SerialPortInputStream::NOTIFY_ON_CHAR, '\n');
		stream->addChangeListener(this);
	}
	else {
		// Warn user no head tracker is there
	}
}

HeadTracker::~HeadTracker() 
{
	delete stream;
	delete port;
}

void HeadTracker::changeListenerCallback (ChangeBroadcaster* stream)
{
	// Parse the string : timesampt(ms?, us?), gx, gy, gz, ax, ay, az
    StringArray delimited;
    delimited.addTokens(((SerialPortInputStream*)stream)->readNextLine(),
                        ",",
                        String::empty);
    
    float timeMs = delimited[0].getFloatValue();
    float pitch = delimited[1].getFloatValue();
    float roll = delimited[2].getFloatValue();
    float yaw = delimited[3].getFloatValue();
    
    samplingRateHz =  (1 - tc) * (1000.0f / (timeMs - lastTimeStampMs)) +   tc * samplingRateHz;
    lastTimeStampMs = timeMs;
    
    std::ios::fmtflags old_settings = std::cout.flags();
    std::cout.precision(2);
    
    std::cout << std::fixed;
    std::cout
    << "Yaw: "    << std::setw(6) << yaw
    << " Pitch: " << std::setw(6) << pitch
    << " Roll: "  << std::setw(6) << roll
    << " FsHz: "  << std::setw(6) << samplingRateHz << std::endl;
    
    std::cout.flags(old_settings);
}