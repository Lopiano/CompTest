/*
  ==============================================================================

    GRMeter.cpp
    Created: 5 Mar 2020 2:10:20pm
    Author:  John Caplan

  ==============================================================================
*/

#include "GRMeter.h"

GRMeter::GRMeter(float& gainReduction)
: currentGR(gainReduction)
{
    startTimer(30);
}

void GRMeter::timerCallback()
{
    repaint();
}

void GRMeter::paint (Graphics& g)
{
    Rectangle<float> downAmt = getLocalBounds().toFloat().removeFromRight((1.0f - currentGR) * getWidth());
    g.setColour(juce::Colours::red.withSaturation(currentGR));
    g.fillRect(downAmt);
    //g.fillAll();
}

void GRMeter::resized()
{
    
}
