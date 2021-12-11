/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class Distortion;
// Forward decleration

    //==============================================================================
/**
*/
class Distortion_02AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Distortion_02AudioProcessor();
    ~Distortion_02AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    
    float InputGain_dB = 1.f;
    float DistortionAmount = 1.f;
    float ArcTanRatio = 1.f;
    int CubicButton = 0;
    int ArcTanButton = 0;
    int SoftMixButton = 0;
    float Threshold = 1.f;
    float BitCrush = 5.f;
    int BitCrushButton = 0;
    int hardButton = 0;
    float wetDryMix = 1.f;
    float OutputGain_dB = 1.f;
    
    float previousGain_Input = 0;
    float previous_distortion_Amount = 0;
    float previousGain_Output = 0;

    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion_02AudioProcessor)
    
    Distortion* distortion;
};
