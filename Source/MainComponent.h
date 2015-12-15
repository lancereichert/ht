/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SerialPort.h"
#include "HeadTracker.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   :  public Component,
                                public ChangeListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
    
    virtual void changeListenerCallback (ChangeBroadcaster* stream) override {
        //std::cout << "Line received: " << ((SerialPortInputStream*)stream)->readNextLine() << std::endl;
    }

private:
    //==============================================================================
    SerialPort* port;
    SerialPortInputStream* pInputStream;
    HeadTracker* headTracker;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
