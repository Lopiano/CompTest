/*
  ==============================================================================

    GRMeter.h
    Created: 5 Mar 2020 2:10:20pm
    Author:  John Caplan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class GRMeter                                           : public Component,
                                                          public Timer
{
public:
    
    GRMeter(float& gainReduction);
    
    ~GRMeter(){};
    
    void timerCallback() override;
    
    void paint (Graphics&) override;

    void resized() override;
    
private:
    
    float& currentGR;
};
