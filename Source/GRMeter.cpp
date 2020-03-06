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
    float grInDb = Decibels::gainToDecibels(currentGR);
    float reductionAmt = -1.0f * grInDb / 42.0f;
    
    Rectangle<float> downAmt = getLocalBounds().toFloat().removeFromRight(reductionAmt * getWidth());
    g.setColour(juce::Colours::red.withSaturation(currentGR));
    g.fillRect(downAmt);
    //g.fillAll();
}

void GRMeter::resized()
{
    
}
