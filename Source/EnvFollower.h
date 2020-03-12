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
    
    EnvFollower();
    
    ~EnvFollower(){};
    
    void prepare(double sampleRate, float threshold, float ratio, float attack, float release);
    
    void calculate(float input);
    
    float getSideChain();
    
    float getEnvOuput();
    
    float addBuffSample(float newSample);
    
    enum State
    {
        rest,
        attack,
        release
    };
    
private:
    
    float maxVal = 0.0f;

    float filtA = 0;
    float filtB = 0;
    float filtGain = 1.5;
    
    float attackSlope = 0.0f;
    float releaseSlope  = 0.0f;
    
    float relstore = 0.0f;
    
    float envLevel = 0.0f;
    
    float envMem = 0.0f;
    
    std::vector<float> buff;
    
    int buffPos = 0;
    int maxPos = 0;
    float lastMax = 0.0f;
    
    State state;
    float envFlip;
    float memFlip;
    float thresh;
};
