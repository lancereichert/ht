/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
    
    StringPairArray portList = SerialPort::getSerialPortPaths();
    if(portList.size())
    {
        StringArray keys = portList.getAllKeys();
        std::cout << keys.size() << " port(s) found." << std::endl;
        
        for (int i = 0; i < keys.size(); i++) {
            std::cout << "key: " << keys[i] << "\tvalue: " << portList.getValue(keys[i], "") << std::endl;
        }
        
        //open the arduino port
        port = new SerialPort(portList.getValue(keys[2], ""),
                                          SerialPortConfig(115200,
                                                           8,
                                                           SerialPortConfig::SERIALPORT_PARITY_NONE,
                                                           SerialPortConfig::STOPBITS_1,
                                                           SerialPortConfig::FLOWCONTROL_NONE));
        
        if(port->exists()) {
            
            std::cout << "Port exists" << std::endl;
            
            pInputStream = new SerialPortInputStream(port);
            
            //Ask to be notified when a new line is available:
            pInputStream->addChangeListener(this); //we must be a changelistener to receive notifications
            pInputStream->setNotify(SerialPortInputStream::NOTIFY_ON_CHAR, '\n');
        } else {
            std::cout << "Port doesn't exist" << std::endl;
        }
    } else {
        std::cout << "No serial ports found of any type" << std::endl;
    }
}

MainContentComponent::~MainContentComponent()
{
    if (pInputStream)
        delete pInputStream;
    
    if (port)
        delete port;
    
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
