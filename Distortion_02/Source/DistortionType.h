/*
  ==============================================================================

    DistortionType.h
    Created: 25 Nov 2021 12:56:49pm
    Author:  James Maddigan

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <math.h>
class Distortion
{
public:

Distortion (){}

~Distortion (){}
    
    
    //======================================================================================================
    
void setArcTanRatio (int newArcRatio)
    {
        arcTan_Ratio = newArcRatio;
    }
    
float getArcTanRatio ()
    {
        return arcTan_Ratio;
    }
    
float getCubicRatio ()
    {
        cubic_Ratio = 1 - arcTan_Ratio;
        return cubic_Ratio;
    }

void
    setArcTanButton (int newArcTanButton)
    {
        ArcTanButton = newArcTanButton;
    }

int
    getArcTanButton ()
    {
        return ArcTanButton;
    }
    
void getsoftMixButton (int newSoftMixButton)
    {
        softMixButton = newSoftMixButton;
    }
int getSoftButton ()
    {
        return softMixButton;
    }
    
    
    //=====================================================================================================
    
    
void setHardButton (int newHardButtonState)
    {
        hardButton = newHardButtonState;
    }
    
int getHardButton ()
    {
        return hardButton;
    }

void setCubicButton (int newCubicButton)
    {
        CubicButton = newCubicButton;
    }
    
int getCubicButton ()
    {
        return CubicButton;
    }
    
    //======================================================================================================
    
void setBitCrushButton (int NewBitCrushButtonState)
    {
        bitCrushButton = NewBitCrushButtonState;
    }

int getBitCrushButton ()
    {
        return bitCrushButton;
    }
    
    //======================================================================================================
    
void setBitCrush (float NewBitCrushValue)
    {
        bitCrushValue = NewBitCrushValue;
    }
    
float getBitCrush ()
    {
        return bitCrushValue;
    }
    
    //======================================================================================================
    
void setThreshold (float new_threshold)
    {
        threshold = new_threshold;
    }
    
float getThreshold ()
    {
        return threshold;
    }
    
    //======================================================================================================
    
void setAlpha (float new_Alpha)
    {
        Distortion_amount = new_Alpha;
    }
    
float getAlpha ()
    {
        return Distortion_amount;
    }
       
    //=====================================================================================================
    
    
void setWetDry (float newWetDryValue)
    {
        wetMix = newWetDryValue;
    }
    
float getWet ()
    {
        return wetMix;
    }
float getDry ()
    {
        dryMix = 1 - wetMix;
        return dryMix;
    }
       
    //=====================================================================================================
    

    
float process (float Input)
    {
        if (CubicButton == 1)
            {
            return (dryMix * Input) + (wetMix * hardClip(bitCrush(softClipCubic(Input))));
            }
        else if (ArcTanButton == 1)
            {
            return (dryMix * Input) + (wetMix * hardClip(bitCrush(softClipArcTan(Input))));
            }
        else if (softMixButton == 1)
            {
            return (dryMix * Input) + (wetMix * hardClip(bitCrush(ParallelSoftClip(Input))));;
            }
        else
            return hardClip(bitCrush(Input));
    }
    
    
private:
    
   // Distortion_Type distortion_Type;                               // Create variable of type Distortion enum
    int ArcTanButton;
    int CubicButton;
    int softMixButton;
    int hardButton;
    float arcTan_Ratio;
    float cubic_Ratio;    // combined ratio makes 1 (gives ratio between two types of                                             distortion
    float wetMix;
    float dryMix;
    
    float bitCrushValue;
    int bitCrushButton;
    float threshold;                         // private variables as only called as argument within the                                              process block which remains inside the class
    float Distortion_amount;
    float process_Type;
    
    //======================================================================================================
    
float softClipArcTan (float input)
    {
        auto Arc_tan_Dist_Amount = (Distortion_amount * 20);
        float output = atan(input * Arc_tan_Dist_Amount) / atan(Arc_tan_Dist_Amount);
        return output;
        
    }

    //======================================================================================================
    
float softClipCubic (float input)
    {
        auto alpha = Distortion_amount + 1;
            
        float output = alpha * (input - (alpha * (1/3) *pow(input, 3)));
        return output;
        
    }
    
float ParallelSoftClip (float input)
    {
       
            float output = (0.5 * softClipCubic(input)) + ( 0.5 * softClipArcTan(input));
            return output;
        
    }
    
    //======================================================================================================
    
float bitCrush (float Input)
    {
       if (bitCrushButton == 1)
        {
            
            float ampValues = pow(2,((bitCrushValue) - 1));
            float Output =  ceil(ampValues * Input) * (1/ampValues);
            
            return Output;
            
        }
        else
            return Input;
    }
    
    //======================================================================================================
    
    
float hardClip (float input)
    {
        if (hardButton == 1)
            {
            
                if ( input >= threshold)
                    return threshold;
        
                else if (input <= -threshold)
                    return - threshold;
        
                else
                    return input;
            }
        else
            return input;
    }
    
    //======================================================================================================

};
