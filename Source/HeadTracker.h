// HeadTracker.h
// Author: Lance Reichert
// November 24th, 2015



#ifndef JAUNT_HEADTRACKER_H
#define JAUNT_HEADTRACKER_H

#include "JuceHeader.h"
#include "SerialPort.h"

class HeadTracker : public ChangeListener
{
public:

					HeadTracker();
					~HeadTracker();

	void 			resetHome();
	void 			getCurrentHeadOrientation(float* azRad, float* elRad);

	// Inherited from ChangeListener
	//==========================================================================
	virtual void 	changeListenerCallback (ChangeBroadcaster* stream) override;

private:

	SerialPort* 			port;
    SerialPortInputStream* 	stream;
    float                   lastTimeStampMs;
    float                   samplingRateHz;
    float                   tc;

	// JUCE_USE_DEBUGGING_NEW_OPERATOR;
};

#endif