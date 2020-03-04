/*
  ==============================================================================

    paramVecs.h
    Created: 3 Mar 2020 2:08:33pm
    Author:  John Caplan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ParamVecs
{
public:
    
    ParamVecs(AudioProcessor& owner);
    
    ~ParamVecs(){};
    
    void addAllParameters();
    
    struct FloatParam
    {
        FloatParam(String nameToUse, String identToUse, float defToUse, float minToUse, float maxToUse)
        : name (nameToUse),
          ident (identToUse),
          def (defToUse),
          min (minToUse),
          max (maxToUse)
        {}
        
        String name;
        String ident;
        float def;
        float min;
        float max;
        
        AudioParameterFloat* param;
    };
    
    void addFloatParamStruct(FloatParam& pStrt);
    
    std::vector<FloatParam> compParams =
    {
        {"Attack",   "att", 0.01f,  0.001f, 0.1f},
        {"Release",  "rel", 0.1f,   0.01f,  1.0f},
        {"Ratio",    "rat", 0.5f,   0.1f,   1.0f},
        {"Treshold", "thr", 0.1f,   0.001f, 1.0f}
    };
    
    std::vector<AudioParameterFloat*> floatParams;
    
private:

    AudioProcessor& processor;
    
};
