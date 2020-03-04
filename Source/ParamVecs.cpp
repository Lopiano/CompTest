/*
  ==============================================================================

    paramVecs.cpp
    Created: 3 Mar 2020 2:08:33pm
    Author:  John Caplan

  ==============================================================================
*/

#include "ParamVecs.h"

ParamVecs::ParamVecs(AudioProcessor& owner)
: processor(owner)
{
    
}

void ParamVecs::addFloatParamStruct(FloatParam& pStrt)
{
    processor.addParameter (pStrt.param =
                            new AudioParameterFloat (pStrt.ident,
                                                     pStrt.name,
                                                     NormalisableRange<float> (pStrt.min, pStrt.max),
                                                     pStrt.def));
    
    floatParams.push_back(pStrt.param);
}

void ParamVecs::addAllParameters()
{
    for (int i = 0; i < compParams.size(); ++i)
    {
        addFloatParamStruct(compParams[i]);
    }
}
