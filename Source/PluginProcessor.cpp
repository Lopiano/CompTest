/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompTefAudioProcessor::CompTefAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        pVecs(*this)
#endif
{
    pVecs.addAllParameters();
}

CompTefAudioProcessor::~CompTefAudioProcessor()
{
}

//==============================================================================
const String CompTefAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompTefAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompTefAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompTefAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompTefAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompTefAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompTefAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompTefAudioProcessor::setCurrentProgram (int index)
{
}

const String CompTefAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompTefAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CompTefAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (int i = 0; i < followers.size(); ++i)
    {
        followers[i].prepare(getSampleRate(),
                             pVecs.compParams[3].param->get(),
                             pVecs.compParams[2].param->get(),
                             pVecs.compParams[0].param->get(),
                             pVecs.compParams[1].param->get());
    }
}

void CompTefAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompTefAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CompTefAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (int i = 0; i < followers.size(); ++i)
    {
        followers[i].prepare(getSampleRate(),
                             pVecs.compParams[3].param->get(),
                             pVecs.compParams[2].param->get(),
                             pVecs.compParams[0].param->get(),
                             pVecs.compParams[1].param->get());
    }
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    float threshhold = pVecs.compParams[3].param->get();
    float ratio = pVecs.compParams[2].param->get();
    
    float makeUp = Decibels::decibelsToGain(pVecs.compParams[4].param->get());
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            followers[channel].calculate(*channelData);
            float envLevel = Decibels::gainToDecibels(followers[channel].getEnvOuput());
            
            float overAmt  = envLevel > threshhold? envLevel - threshhold: 0.0f;
            
            gainReduction[channel] = Decibels::decibelsToGain(-1.0f * ratio * overAmt);
            
            *channelData *= gainReduction[channel] * makeUp;
            //*channelData = followers[channel].getEnvOuput();
            channelData++;
        }
    }
}

//==============================================================================
bool CompTefAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CompTefAudioProcessor::createEditor()
{
    return new CompTefAudioProcessorEditor (*this);
}

//==============================================================================
void CompTefAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompTefAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompTefAudioProcessor();
}
