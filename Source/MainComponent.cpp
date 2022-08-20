#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
    

    addAndMakeVisible(&multiSlider);
    addAndMakeVisible(&multiSlider2);
    multiSlider2.setHorizontal(true);
    multiSlider2.setColour(sjf_multislider::backgroundColourId, juce::Colours::black);
    multiSlider.setColour(sjf_multislider::backgroundColourId, juce::Colours::white);
    multiSlider.setColour(sjf_multislider::sliderColourID, juce::Colours::red);
    multiSlider2.setColour(sjf_multislider::sliderColourID, juce::Colours::green);
    
    
    addAndMakeVisible(&multitoggle);
    multitoggle.setNumRowsAndColumns(3, 12);
    multitoggle.setColour(sjf_multitoggle::tickColourId, juce::Colours::red);
    multitoggle.setColour(sjf_multitoggle::backgroundColourId, juce::Colours::darkcyan);
    multitoggle.setColour(sjf_multitoggle::tickDisabledColourId, juce::Colours::transparentBlack);
    
    
    addAndMakeVisible(&multitoggle2);
    multitoggle2.setNumRowsAndColumns(12, 4);
    multitoggle2.setColour(sjf_multitoggle::tickColourId, juce::Colours::purple);
    multitoggle2.setColour(sjf_multitoggle::backgroundColourId, juce::Colours::peru);
    multitoggle2.setColour(sjf_multitoggle::tickDisabledColourId, juce::Colours::transparentBlack);
    
    
    
    addAndMakeVisible(&nSlidersSlider);
    nSlidersSlider.setRange(1, 32, 1);
    nSlidersSlider.setSliderStyle(juce::Slider::LinearVertical);
    
    nSlidersSlider.onValueChange = [this]
    {
        multiSlider.setNumSliders( nSlidersSlider.getValue() );
        multiSlider2.setNumSliders( nSlidersSlider.getValue() );
    };
    
    addAndMakeVisible(&nRowsSlider);
    nRowsSlider.setRange(1, 32, 1);
    nRowsSlider.setSliderStyle(juce::Slider::LinearVertical);
    nRowsSlider.onValueChange = [this] { multitoggle.setNumRows( nRowsSlider.getValue() ); multitoggle2.setNumRows( nRowsSlider.getValue() ); };
    
    addAndMakeVisible(&nColumnsSlider);
    nColumnsSlider.setRange(1, 32, 1);
    nColumnsSlider.setSliderStyle(juce::Slider::LinearVertical);
    nColumnsSlider.onValueChange = [this] { multitoggle.setNumColumns( nColumnsSlider.getValue() ); multitoggle2.setNumColumns( nColumnsSlider.getValue() ); };
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
//    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{

    multiSlider.setBounds(20, 20, 200, 100);
    multiSlider2.setBounds(20, 120, 200, 200);
    nSlidersSlider.setBounds(0, 20, 20, 100);
    
    multitoggle.setBounds(40, 320, 150, 150);
    multitoggle2.setBounds(190, 320, 150, 150);
    
    nRowsSlider.setBounds(0, 320, 20, 150);
    nColumnsSlider.setBounds(20, 320, 20, 150);
    
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
