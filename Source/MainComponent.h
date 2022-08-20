#pragma once

#include <JuceHeader.h>
#include "sjf_widgets.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    sjf_multislider multiSlider, multiSlider2;
    sjf_multitoggle multitoggle, multitoggle2;
    
    juce::Slider nSlidersSlider, nRowsSlider, nColumnsSlider;
private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
