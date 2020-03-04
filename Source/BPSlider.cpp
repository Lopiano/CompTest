/*
  ==============================================================================

    BPSlider.cpp
    Created: 3 Mar 2020 2:09:57pm
    Author:  John Caplan

  ==============================================================================
*/

#include "BPSlider.h"

BPSlider::BPSlider (AudioParameterFloat& paramToUse, Slider::Listener* listener)
: myParam(paramToUse)
{
    addListener(listener);
    setRange(paramToUse.range.start, paramToUse.range.end);
    startTimer(30);
    updateSliderPos();
}

void BPSlider::updateSliderPos()
{
    Slider::setValue(myParam.get());
}

void BPSlider::timerCallback()
{
    updateSliderPos();
}
