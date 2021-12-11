/*
  ==============================================================================

    AudioUtilities.h
    Created: 25 Nov 2021 12:56:30pm
    Author:  James Maddigan

  ==============================================================================
*/

#pragma once



auto stepResponse (float input, float previous_input, float alpha = 0.75)
    {
        return (1 - alpha) * input + alpha * previous_input;
    }


    

