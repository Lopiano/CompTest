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
    
    float tenDbAbove = Decibels::decibelsToGain(threshold) * Decibels::decibelsToGain(10.0);
    
    attackSlope = tenDbAbove/(attack * sampleRate);
    
    releaseSlope = Decibels::decibelsToGain(threshold)/(release * sampleRate);
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
            envLevel = envMem;
        }
        else
        {
            envLevel += attackSlope;
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
            envLevel -= releaseSlope;
        }
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
    buffPos++;
    if (buffPos == 500)
    {
        //*(buff.begin() + buffPos) = -1.0f;
        buffPos = 0;
    }
    return *std::max_element(buff.begin(), buff.end());
}
