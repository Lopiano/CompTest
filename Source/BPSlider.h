/*
  ==============================================================================

    BPSlider.h
    Created: 3 Mar 2020 2:09:57pm
    Author:  John Caplan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BPSlider                                      : public Slider,
                                                      public Timer
{
public :
    
    BPSlider(AudioParameterFloat& paramToUse, Slider::Listener* listener);
    
    ~BPSlider(){};
    
    void timerCallback() override;
    
    void updateSliderPos();
    
private :
    
    AudioParameterFloat& myParam;
};
