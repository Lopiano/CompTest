/*
  ==============================================================================

    EnvFollower.h
    Created: 25 Feb 2020 12:24:55pm
    Author:  John Caplan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

class EnvFollower
{
public:
    
    ///ctor
    EnvFollower();
    
    ///dtor
    ~EnvFollower(){};
    
    /// Sets things up for the current params and sample rate
    void prepare(double sampleRate, float threshold, float ratio, float attack, float release);
    
    /// Does the buisness
    void calculate(float input);
    
    /// Gets output
    float getEnvOuput();
    
    ///Add a new sample to the buffer used to find the max and returns the current max
    float addBuffSample(float newSample);
    
private:
    
    float maxVal = 0.0f;

    float filtA = 0;
    float filtB = 0;
    float filtGain = 1.5;
    
    float attackSlope = 0.0f;
    float releaseSlope  = 0.0f;
    
    float attMult = 0.0f;
    float relMult = 0.0f;
    
    float envLevel = 0.0f;
    
    float envMem = 0.0f;
    
    std::vector<float> buff;
    
    int buffPos = 0;
    int maxPos = 0;
    float lastMax = 0.0f;
    
    float thresh;
    
    /// this is just for testing
    float getSideChain(){return envMem;};
};
