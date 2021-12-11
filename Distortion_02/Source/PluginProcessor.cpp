/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "AudioUtilities.h"
#include "DistortionType.h"

//==============================================================================
Distortion_02AudioProcessor::Distortion_02AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    distortion = new Distortion;
}

Distortion_02AudioProcessor::~Distortion_02AudioProcessor()
{
    delete distortion;
}

//==============================================================================
const juce::String Distortion_02AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Distortion_02AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Distortion_02AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Distortion_02AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Distortion_02AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Distortion_02AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Distortion_02AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Distortion_02AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Distortion_02AudioProcessor::getProgramName (int index)
{
    return {};
}

void Distortion_02AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Distortion_02AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Distortion_02AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Distortion_02AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Distortion_02AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    auto gainLinear_Input = pow(10, InputGain_dB/20);
    auto gainLinear_Output = pow(10, OutputGain_dB/20);
    
    auto current_Gain_In = stepResponse(gainLinear_Input, previousGain_Input);
    auto current_Gain_Out = stepResponse(gainLinear_Output, previousGain_Output);
    
    // At start  of each buffer, step function to smooth trainsition to new gain value

    distortion->setAlpha(DistortionAmount);
    distortion->getAlpha();
    distortion->setThreshold(Threshold);
    distortion->getThreshold();
    distortion->setArcTanButton(ArcTanButton);
    distortion->getArcTanButton();
    distortion->setHardButton(hardButton);
    distortion->getHardButton();
    distortion->setBitCrushButton(BitCrushButton);
    distortion->getBitCrushButton();
    distortion->setBitCrush(BitCrush);
    distortion->getBitCrush();
    distortion->setCubicButton(CubicButton);
    distortion->getCubicButton();
    distortion->getsoftMixButton(SoftMixButton);
    distortion->setWetDry(wetDryMix);
    distortion ->getWet();
    distortion->getDry();
    
for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer (channel);
                
            for (int sample = 0; sample < buffer.getNumSamples(); sample++)
                {
                    channelData[sample] = current_Gain_In * channelData[sample];
                            // Apply Input gain to sample
                    channelData[sample] = distortion->process(channelData[sample]);
                           // -> used instead of . as Object of the class is a pointer
                            // Apply distortion to sample
                    channelData[sample] = current_Gain_Out * channelData[sample];
                           //Apply output gain to sample
                }
        }
    
    previousGain_Input = current_Gain_In;            // Once at least one if statement run, update previous                                                   values
    previousGain_Output = current_Gain_Out;
    
}
    


//==============================================================================
bool Distortion_02AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Distortion_02AudioProcessor::createEditor()
{
    return new Distortion_02AudioProcessorEditor (*this);
}

//==============================================================================
void Distortion_02AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Distortion_02AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Distortion_02AudioProcessor();
}
