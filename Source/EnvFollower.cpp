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
    
}

void EnvFollower::prepare(double sampleRate, float threshold, float ratio,
                          float attack, float release)
{
    float freq = 100.0f;
    float basefc = freq/sampleRate;
    filtB = expf(-2.0f * float_Pi * basefc);
    filtA = 1.0f - filtB;
    
    float tenDbAbove = threshold * Decibels::decibelsToGain(10.0);
    
    attackSlope = tenDbAbove/(attack * sampleRate);
    
    releaseSlope = threshold/(release * sampleRate);
}

void EnvFollower::calculate(float input)
{
    float absChan = fabs(input);
    
    envMem = filtA * absChan * filtGain + filtB * envMem;
    
    if (envMem > envLevel)
    {
        envLevel += attackSlope;
    }
    else if (envLevel > 0)
    {
        envLevel -= releaseSlope;
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
