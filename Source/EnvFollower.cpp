/*
  ==============================================================================

    EnvFollower.cpp
    Created: 25 Feb 2020 12:24:55pm
    Author:  John Caplan

  ==============================================================================
*/

#include "EnvFollower.h"

EnvFollower::EnvFollower()
{
    buff.resize(500);
}

void EnvFollower::prepare(double sampleRate, float threshold, float ratio,
                          float attack, float release)
{
    float freq = 100.0f;
    float basefc = freq/sampleRate;
    filtB = expf(-2.0f * float_Pi * basefc);
    filtA = 1.0f - filtB;
    
    //float tenDbAbove = Decibels::decibelsToGain(threshold) * Decibels::decibelsToGain(10.0);
    
    thresh = Decibels::decibelsToGain(threshold);
    
    attackSlope = 1.0f/(attack * sampleRate);
    
    releaseSlope = 1.0f/(release * sampleRate);
}

void EnvFollower::calculate(float input)
{
    float absChan = fabs(input);
    
    maxVal = addBuffSample(absChan);
    
    envMem = filtA * maxVal + filtB * envMem;
    
    if (envMem > envLevel)
    {
        if (envLevel + attackSlope >= envMem)
        {
            state = rest;
            envLevel = envMem;
        }
        else
        {
            envLevel += attackSlope;
            state = attack;
        }
    }
    else if (envLevel > 0 && envLevel > envMem)
    {
        if (envLevel - releaseSlope < envMem)
        {
            envLevel = envMem;
        }
        else
        {
            state = release;
            envLevel = (envLevel * releaseSlope);
        }
    }
    else if (envMem == envLevel)
    {
        state = rest;
    }
}

float EnvFollower::getSideChain()
{
    return envMem;
}

float EnvFollower::getEnvOuput()
{
    return envLevel;
}

float EnvFollower::addBuffSample(float newSample)
{
    *(buff.begin() + buffPos) = newSample;
    
    float newMax = 0;
    if (newSample >= lastMax)
    {
        newMax = newSample;
        maxPos = buffPos;
    }
    else if (maxPos != buffPos)
    {
        newMax = lastMax;
    }
    else
    {
        auto maxFound = std::max_element(buff.begin(), buff.end());
        maxPos = static_cast<int>(std::distance(buff.begin(), maxFound));
        newMax = *maxFound;
    }
    lastMax = newMax;
    
    buffPos++;
    if (buffPos == 500)
    {
        buffPos = 0;
    }
    return newMax;
}
