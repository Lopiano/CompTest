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
    
private:
    
    int numIn = 0;
    int sampleMax = 500;
    float maxVal = 0.0f;

    float filtA = 0;
    float filtB = 0;
    float filtGain = 1.5;
    
    float attackSlope = 0.0f;
    float releaseSlope  = 0.0f;
    
    float envLevel = 0.0f;
    
    float envMem = 0.0f;
};
