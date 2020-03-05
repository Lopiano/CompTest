/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BPSlider.h"
#include "GRMeter.h"

//==============================================================================
/**
*/
class CompTefAudioProcessorEditor  : public AudioProcessorEditor,
                                     public Slider::Listener
{
public:
    CompTefAudioProcessorEditor (CompTefAudioProcessor&);
    ~CompTefAudioProcessorEditor();
    
    void sliderValueChanged (Slider* slider) override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    std::unique_ptr<BPSlider> attSlider;
    std::unique_ptr<BPSlider> relSlider;
    std::unique_ptr<BPSlider> ratSlider;
    std::unique_ptr<BPSlider> thrSlider;
    
    std::unique_ptr<GRMeter> meter;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompTefAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompTefAudioProcessorEditor)
};
