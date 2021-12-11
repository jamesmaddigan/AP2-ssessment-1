/*
  ==============================================================================

    DistortionType.h
    Created: 25 Nov 2021 12:56:49pm
    Author:  James Maddigan

  ==============================================================================
*/

#pragma once

#include <math.h>
class Distortion
{
public:

Distortion (){}

~Distortion (){}
    
enum Distortion_Type {Soft_Cubic, Hard, Soft_ArcTan};
    
    
void setDistortionType (Distortion_Type newType)
{
        distortion_Type = newType;                          // takes parameter as enum mand sets private
                                                            // enum variable to be equal to the passed enum
}

Distortion_Type getDistrotionType()
{
    return distortion_Type;                       // Return updated distortion type
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
    
    float getAlpha ( )
        {
            return Distortion_amount;
        }
       
    //=====================================================================================================
    
    
float process (float input)
    {
        if (distortion_Type == Soft_Cubic)
            {
            
                return softClipCubic (input);
            }
        
        else if (distortion_Type == Hard)
            {
        
                return hardClip (input);
            }
        
        else if (distortion_Type == Soft_ArcTan)
            {
                
                return softClipArcTan (input);
                
            }
        else
        {
            return input;
        }
    }
    
    
    
    
    
    
    
    
    
private:
    
    Distortion_Type distortion_Type;                               // Create variable of type Distortion enum
    
    float threshold;                         //private variables as only called as argument within the process                                            block which remains inside the class
    float Distortion_amount;
    
    float softClipCubic (float input)
    {
        float output = input - (Distortion_amount * (1/3) * pow(input, 3));
        return output;
    }
    
    float hardClip (float input)
    {
        if ( input >= threshold)
            return threshold;
        
        else if (input <= -threshold)
            return - threshold;
        
        else
            return input;
    }
    
    float softClipArcTan (float input)
    {
        auto Arc_tan_Dist_Amount = (Distortion_amount * 10);
        float output = (2/M_PI)* atan(input * Arc_tan_Dist_Amount);
        return output;

    }

    
   // float gain_dB {1.f};
   // float previous_gain {0.f};
};
