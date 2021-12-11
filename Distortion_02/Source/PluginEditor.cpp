/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"


    //==============================================================================

Distortion_02AudioProcessorEditor::Distortion_02AudioProcessorEditor (Distortion_02AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
   
    setSize (920, 520);
    
    InputGainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    InputGainSlider.setRange(-48.f, 12.f, 0.1f);
    InputGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    InputGainSlider.setPopupDisplayEnabled(true, false, this);
    InputGainSlider.setTextValueSuffix(" dB");
    InputGainSlider.setValue(0.f);
    InputGainSlider.addListener(this);
    addAndMakeVisible(&InputGainSlider);
    
    InputLabel.setText("Input Gain", juce::dontSendNotification);
    InputLabel.attachToComponent(&InputGainSlider, true);
    InputLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    InputLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(InputLabel);
    
    //====================================================================================================
    
    OutputGainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    OutputGainSlider.setRange(-48.f, 12.f, 0.1f);
    OutputGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    OutputGainSlider.setPopupDisplayEnabled(true, false, this);
    OutputGainSlider.setTextValueSuffix(" dB");
    OutputGainSlider.setValue(0.f);
    OutputGainSlider.addListener(this);
    addAndMakeVisible(&OutputGainSlider);
    
    OutputLabel.setText("Output Gain", juce::dontSendNotification);
    OutputLabel.attachToComponent(&OutputGainSlider, true);
    OutputLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    OutputLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(OutputLabel);
    
    //====================================================================================================
    
    ThresholdSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    ThresholdSlider.setRange(0.2f, 0.75f, 0.01f);
    ThresholdSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    ThresholdSlider.setPopupDisplayEnabled(true, false, this);
    ThresholdSlider.setTextValueSuffix(" Linear Cutoff");
    ThresholdSlider.setValue(0.6f);
    ThresholdSlider.addListener(this);
    addAndMakeVisible(&ThresholdSlider);
    
    ThresholdLabel.setText("Hard Clip Threshold", juce::dontSendNotification);
    ThresholdLabel.attachToComponent(&ThresholdSlider, true);
    ThresholdLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    ThresholdLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(ThresholdLabel);
    
    //====================================================================================================
    
    DistortionAmountSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    DistortionAmountSlider.setRange(0.2f, 1.2f, 0.01f);
    DistortionAmountSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    DistortionAmountSlider.setPopupDisplayEnabled(true, false, this);
    //DistortionAmountSlider.setTextValueSuffix(" Distortion Amount");
    DistortionAmountSlider.setValue(0.5f);
    DistortionAmountSlider.addListener(this);
    addAndMakeVisible(&DistortionAmountSlider);
    
    DistortionAmountLabel.setText("Distortion Amount", juce::dontSendNotification);
    DistortionAmountLabel.attachToComponent(&DistortionAmountSlider, true);
    DistortionAmountLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    DistortionAmountLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(DistortionAmountLabel);
    
    //=====================================================================================================

    BitCrushSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    BitCrushSlider.setRange(4.f,10.f,1.f);
    BitCrushSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    BitCrushSlider.setPopupDisplayEnabled(true, false, this);
    BitCrushSlider. setTextValueSuffix(" Bits");
    BitCrushSlider. setValue(5.f);
    BitCrushSlider.addListener(this);
    addAndMakeVisible(&BitCrushSlider);
    
    BitcrushLabel.setText("Bit Crush", juce::dontSendNotification);
    BitcrushLabel.attachToComponent(&BitCrushSlider, true);
    BitcrushLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    BitcrushLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(BitcrushLabel);
    
    
    //=====================================================================================================
    
    wetDrySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    wetDrySlider.setRange(0.f, 1.f, 0.01f);
    wetDrySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    wetDrySlider.setPopupDisplayEnabled(true, false, this);
    wetDrySlider.setTextValueSuffix(" dB");
    wetDrySlider.setValue(1.f);
    wetDrySlider.addListener(this);
    addAndMakeVisible(&wetDrySlider);
    

    WetDryLabel.setText("Wet/Dry Mix", juce::dontSendNotification);
    WetDryLabel.attachToComponent(&wetDrySlider, true);
    WetDryLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    WetDryLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(WetDryLabel);
    
    //====================================================================================================
    
    // Create on/off labels for buttons
    
    ArcTanLabel.setText("Off", juce::dontSendNotification);
    ArcTanLabel.attachToComponent(&ArcTanButton, false);
    ArcTanLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    ArcTanLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(ArcTanLabel);
    
    //====================================================================================================
    
    softMixLabel.setText("Off", juce::dontSendNotification);
    softMixLabel.attachToComponent(&SoftMixButton, false);
    softMixLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    softMixLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(softMixLabel);
    
    //====================================================================================================
    
    cubicLabel.setText("Off", juce::dontSendNotification);
    cubicLabel.attachToComponent(&CubicButton, false);
    cubicLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    cubicLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(cubicLabel);
    
    //====================================================================================================
    
    bitButtonLabel.setText("Off", juce::dontSendNotification);
    bitButtonLabel.attachToComponent(&BitCrushButton, false);
    bitButtonLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    bitButtonLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(bitButtonLabel);
    
    //====================================================================================================
    
    hardButtonLabel.setText("Off", juce::dontSendNotification);
    hardButtonLabel.attachToComponent(&hardButton, false);
    hardButtonLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    hardButtonLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(hardButtonLabel);
    
    
    //=====================================================================================================
    ArcTanButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    ArcTanButton.onClick = [this]()
            {
               // buttonPress.setArcTanButtonState(audioProcessor.ArcTanButton);
                if (audioProcessor.ArcTanButton == 0)
                {
                    audioProcessor.ArcTanButton = 1;
                    audioProcessor.CubicButton = 0;
                    audioProcessor.SoftMixButton = 0;
                    softMixLabel.setText("Off", juce::dontSendNotification);
                    cubicLabel.setText("Off", juce::dontSendNotification);
                    ArcTanLabel.setText("On", juce::dontSendNotification);
                }
            
                else if (audioProcessor.ArcTanButton == 1)
                {
                    audioProcessor.ArcTanButton = 0;
                    ArcTanLabel.setText("Off", juce::dontSendNotification);
                }
                
            };
    addAndMakeVisible(ArcTanButton);
    
    
     //=====================================================================================================
     
     SoftMixButton.setToggleState(true, juce::NotificationType::dontSendNotification);
     SoftMixButton.onClick = [this]()
             {
                 if (audioProcessor.SoftMixButton == 0)
                 {
                     audioProcessor.SoftMixButton = 1;              //changing state of button if pressed
                     audioProcessor.CubicButton = 0;
                     audioProcessor.ArcTanButton = 0;
                     softMixLabel.setText("On", juce::dontSendNotification);
                     cubicLabel.setText("Off", juce::dontSendNotification);
                     ArcTanLabel.setText("Off", juce::dontSendNotification);
                 }
                     
                 else if (audioProcessor.SoftMixButton == 1)
                 {
                     audioProcessor.SoftMixButton = 0;
                     softMixLabel.setText("Off", juce::dontSendNotification);
                 }
                 
             };
     addAndMakeVisible(SoftMixButton);
    
    
    //====================================================================================================
    CubicButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    CubicButton.onClick = [this]()
            {
                if (audioProcessor.CubicButton == 0)
                {
                    audioProcessor.CubicButton = 1;            
                    audioProcessor.ArcTanButton = 0;
                    audioProcessor.SoftMixButton = 0;
                    softMixLabel.setText("Off", juce::dontSendNotification);
                    cubicLabel.setText("On", juce::dontSendNotification);
                    ArcTanLabel.setText("Off", juce::dontSendNotification);
                }
                
                else if (audioProcessor.CubicButton == 1)
                {
                    audioProcessor.CubicButton = 0;
                    cubicLabel.setText("Off", juce::dontSendNotification);
                }
                
            };
    addAndMakeVisible(CubicButton);
    
    
    
    //=====================================================================================================
    
    BitCrushButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    BitCrushButton.onClick = [this]()
            {
                if (audioProcessor.BitCrushButton == 0)
                {
                    audioProcessor.BitCrushButton = 1;              //changing state of button if pressed
                    bitButtonLabel.setText("On", juce::dontSendNotification);
                }
                    
                else if (audioProcessor.BitCrushButton == 1)
                {
                    audioProcessor.BitCrushButton = 0;
                    bitButtonLabel.setText("Off", juce::dontSendNotification);
                }
                
            };
    addAndMakeVisible(BitCrushButton);
   
    //=================================================================================================
    
    hardButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    hardButton.onClick = [this]()
            {
                if (audioProcessor.hardButton == 0)
                    {
                        audioProcessor.hardButton = 1;
                        hardButtonLabel.setText("On", juce::dontSendNotification);
                    }
            
                else if (audioProcessor.hardButton == 1)
                    {
                        audioProcessor.hardButton = 0;
                        hardButtonLabel.setText("Off", juce::dontSendNotification);
                    }
            };
    addAndMakeVisible(hardButton);
    
}



Distortion_02AudioProcessorEditor::~Distortion_02AudioProcessorEditor()
{
}

//=========================================================================================================

void Distortion_02AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::red);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Distortion Combo", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Distortion_02AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    InputGainSlider.setBounds(80, 80, 20, 420);
    ArcTanButton.setBounds(180, 150, 100, 50);
    CubicButton.setBounds(180, 350, 100, 50);
    SoftMixButton.setBounds(180, 250, 100, 50);
    DistortionAmountSlider.setBounds(340, 80, 20, 420);
    BitCrushButton.setBounds(460, 150, 100, 50);
    BitCrushSlider.setBounds(600, 80, 20, 180);
    hardButton.setBounds(460, 390, 100, 50);
    ThresholdSlider.setBounds(600, 320, 20, 180);
    wetDrySlider.setBounds(800, 80, 20, 180);
    OutputGainSlider.setBounds(800, 320, 20, 180);
  
}

void Distortion_02AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &InputGainSlider)
        audioProcessor.InputGain_dB = InputGainSlider.getValue();
   
    if(slider == &DistortionAmountSlider)
        audioProcessor.DistortionAmount = DistortionAmountSlider.getValue();
    
    if(slider == &BitCrushSlider)
        audioProcessor.BitCrush = BitCrushSlider.getValue();
    
    if(slider == &ThresholdSlider)
        audioProcessor.Threshold = ThresholdSlider.getValue();
    
    if(slider == &wetDrySlider)
        audioProcessor.wetDryMix = wetDrySlider.getValue();
    
    if(slider == &OutputGainSlider)
        audioProcessor.OutputGain_dB = OutputGainSlider.getValue();
}

