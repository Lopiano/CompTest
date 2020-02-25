/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

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
    float ratio = 0.25;
    float attack  = 0.00001f;
    float release = 0.00005f;
    float envFollow = 0.0f;
    
    std::array<float, 2> envMem = {0.0f, 0.0f};
    
    
    float filtA = 0;
    float filtB = 0;
    float filtGain = 1.5;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompTefAudioProcessor)
};
