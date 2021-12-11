/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"



//==============================================================================
/**
*/
class Distortion_02AudioProcessorEditor  :  public juce::AudioProcessorEditor,
private juce::Slider::Listener

{
public:
    Distortion_02AudioProcessorEditor (Distortion_02AudioProcessor&);
    ~Distortion_02AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Distortion_02AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion_02AudioProcessorEditor)
    
    juce::Slider InputGainSlider;
    juce::TextButton ArcTanButton {"ArcTan Clipping"};
    juce::Slider DistortionAmountSlider;
    juce::TextButton SoftMixButton {"50:50"};
    juce::TextButton CubicButton {"Cubic Distortion"};
    juce::Slider BitCrushSlider;
    juce::TextButton BitCrushButton {"Bit Crush"};
    juce::TextButton hardButton {"Hard Clipping"};
    juce::Slider ThresholdSlider;
    juce::Slider OutputGainSlider;
    juce::Slider wetDrySlider;
    
    juce::Label InputLabel;
    juce::Label OutputLabel;
    juce::Label DistortionAmountLabel;
    juce::Label ThresholdLabel;
    juce::Label SoftRatioLabel;
    juce::Label BitcrushLabel;
    juce::Label WetDryLabel;
    
    // On/off Labels
    
    juce::Label ArcTanLabel;
    juce::Label cubicLabel;
    juce::Label softMixLabel;
    juce::Label bitButtonLabel;
    juce::Label hardButtonLabel;
    
    void sliderValueChanged(juce::Slider* slider) override;
    
  
};
