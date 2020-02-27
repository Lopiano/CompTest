/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>
#include "EnvFollower.h"

//==============================================================================
/**
*/
class CompTefAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    CompTefAudioProcessor();
    ~CompTefAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    
    float threshhold = 0.1f;
    float ratio = 0.1;
    float gainReduction = 0.0f;
    
    float attack  = 0.001f;
    float release = 0.01f;
    
    std::array<EnvFollower, 2> followers;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompTefAudioProcessor)
};
