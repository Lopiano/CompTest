/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompTefAudioProcessorEditor::CompTefAudioProcessorEditor (CompTefAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    attSlider = std::make_unique<BPSlider>(*p.getPVecs().compParams[0].param, this);
    addAndMakeVisible(*attSlider);
    relSlider = std::make_unique<BPSlider>(*p.getPVecs().compParams[1].param, this);
    addAndMakeVisible(*relSlider);
    ratSlider = std::make_unique<BPSlider>(*p.getPVecs().compParams[2].param, this);
    addAndMakeVisible(*ratSlider);
    thrSlider = std::make_unique<BPSlider>(*p.getPVecs().compParams[3].param, this);
    addAndMakeVisible(*thrSlider);
    
    meter = std::make_unique<GRMeter>(p.getGR());
    addAndMakeVisible(*meter);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

CompTefAudioProcessorEditor::~CompTefAudioProcessorEditor()
{
}

void CompTefAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == attSlider.get())
    {
        *processor.getPVecs().compParams[0].param = slider->getValue();
    }
    if (slider == relSlider.get())
    {
        *processor.getPVecs().compParams[1].param = slider->getValue();
    }
    if (slider == ratSlider.get())
    {
        *processor.getPVecs().compParams[2].param = slider->getValue();
    }
    if (slider == thrSlider.get())
    {
        *processor.getPVecs().compParams[3].param = slider->getValue();
    }
}

//==============================================================================
void CompTefAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hey I'm a compressor", getLocalBounds(), Justification::centred, 1);
}

void CompTefAudioProcessorEditor::resized()
{
    attSlider->setBounds (0, 0, 400, 25);
    attSlider->setSize   (400, 25);
    
    relSlider->setBounds (0, 25, 400, 25);
    relSlider->setSize   (400, 25);
    
    ratSlider->setBounds (0, 50, 400, 25);
    ratSlider->setSize   (400, 25);
    
    thrSlider->setBounds (0, 75, 400, 25);
    thrSlider->setSize   (400, 25);
    
    meter->setBounds(0, 100, 400, 25);
    meter->setSize(400, 25);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
