//
//  sjf_multislider.h
//  multiSlider
//
//  Created by Simon Fay on 20/08/2022.
//

#ifndef sjf_multislider_h
#define sjf_multislider_h

class sjf_multislider : public juce::Component
{
public:
    //==============================================================================
    sjf_multislider()
    {
        setInterceptsMouseClicks(true, false);
        createSliderArray(4); // just default to 4 sliders because why not
        setSize (600, 400);
    }
    //==============================================================================
    ~sjf_multislider()
    {
        deleteAllChildren();
    }
    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        g.setColour( findColour(backgroundColourId) );
        g.fillAll();
        g.setFont (juce::Font (16.0f));
        g.setColour ( findColour(outlineColourId) );
        g.drawRect(0, 0, getWidth(), getHeight());
        
        auto nSliders = sliders.size();
        for (int s = 0; s < nSliders; s++)
        {
            sliders[s]->setColour( juce::Slider::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f) ) ;
            sliders[s]->setColour( juce::Slider::trackColourId, findColour( sliderColourID ) );
        }
    }
    //==============================================================================
    void resized() override
    {
        auto nSliders = sliders.size();
        for (int s = 0; s < nSliders; s++)
        {
            if (!isHorizontalFlag)
            {
                auto sWidth = (float)this->getWidth() / (float)nSliders;
                sliders[s]->setSliderStyle(juce::Slider::LinearBarVertical);
                sliders[s]->setBounds(sWidth*s, 0.0f, sWidth, getHeight());
            }
            else
            {
                auto sHeight = (float)getHeight()/(float)nSliders;
                sliders[s]->setSliderStyle(juce::Slider::LinearBar);
                sliders[s]->setBounds(0.0f, sHeight*s, getWidth(), sHeight);
            }
        }
    }
    //==============================================================================
    void setNumSliders( int numSliders )
    {
        auto nSliders = sliders.size();
        if (numSliders < 1){ numSliders = 1; }
        if (numSliders == nSliders){ return; }
        
        std::vector<float> temp;
        for(int s = 0; s < nSliders; s++){ temp.push_back(sliders[s]->getValue()); }
        
        createSliderArray(numSliders);
        
        for(int s = 0; s < numSliders; s++)
        {
            if(s < temp.size()) { sliders[s]->setValue(temp[s]); }
        }
        resized();
    }
    //==============================================================================
    int getNumSliders()
    {
        return sliders.size();
    }
    //==============================================================================
    float fetch(int sliderIndex)
    {
        return ( sliders[sliderIndex]->getValue() );
    }
    //==============================================================================
    void setRange(float min, float max)
    {
        for (int s = 0; s < sliders.size(); s ++) { sliders[s]->setRange(min, max); }
    }
    //==============================================================================
    std::vector<float> outputList()
    {
        auto nSliders = sliders.size();
        std::vector<float> temp;
        for(int s = 0; s < nSliders; s++){ temp.push_back(sliders[s]->getValue()); }
        return temp;
    }
    //==============================================================================
    void setHorizontal(bool horizontal)
    {
        if(isHorizontalFlag != horizontal)
        {
            isHorizontalFlag = horizontal;
            resized();
        }
        
    }
    enum ColourIds
    {
        backgroundColourId          = 0x1001200,
        outlineColourId        = 0x1000c00,
        sliderColourID               = 0x1001310,
    };
private:
    void calulateMousePosToSliderCal(const juce::MouseEvent& e)
    {
        
        auto nSliders = sliders.size();
        auto pos = e.position;
        if (!isHorizontalFlag)
        {
            auto x = pos.getX();
            auto y = pos.getY();
            auto val = ((float)getHeight()-y)/(float)getHeight();
            auto sWidth = getWidth()/nSliders;
            for (int s = 0; s < nSliders; s++)
            {
                if( e.mods.isShiftDown() )
                {
                    for (int s = 0; s < sliders.size(); s++)
                    {
                        sliders[s]->setValue( val );
                    }
                }
                else if( e.mods.isAltDown() )
                {
                    for (int s = 0; s < sliders.size(); s++)
                    {
                        sliders[s]->setValue( sliders[s]->getMinimum() );
                    }
                }
                else if( x >= s*sWidth && x < (s+1)*sWidth)
                {
                    sliders[s]->setValue(val);
                }
            }
        }
        else
        {
            auto x = pos.getX();
            auto y = pos.getY();
            auto val = x / (float)getWidth();
            auto sHeight = getHeight()/nSliders;
            for (int s = 0; s < nSliders; s++)
            {
                if( e.mods.isShiftDown() )
                {
                    for (int s = 0; s < sliders.size(); s++)
                    {
                        sliders[s]->setValue( val );
                    }
                }
                else if( e.mods.isAltDown() )
                {
                    for (int s = 0; s < sliders.size(); s++)
                    {
                        sliders[s]->setValue( sliders[s]->getMinimum() );
                    }
                }
                else if( y >= s*sHeight && y < (s+1)*sHeight)
                {
                    sliders[s]->setValue(val);
                }
            }
        }
    }
    void mouseDown (const juce::MouseEvent& e) override
    {
        calulateMousePosToSliderCal(e);
    }
    //==============================================================================
    void mouseDrag(const juce::MouseEvent& e) override
    {
        calulateMousePosToSliderCal(e);
    }
    //==============================================================================
    void createSliderArray(int nSliders)
    {
        deleteAllChildren();
        sliders.clear();
        for (int s = 0; s < nSliders; s ++)
        {
            juce::Slider *slider = new juce::Slider;
            slider->setTextBoxStyle(juce::Slider::NoTextBox, 0,0,0);
            slider->setRange(0.0, 1.0, 0.0);
            slider->setInterceptsMouseClicks(false, false);
            addAndMakeVisible(slider);
            sliders.add(slider);
        }
    }
    //==============================================================================
    
    
private:
    juce::Array<juce::Slider*> sliders;
    bool isHorizontalFlag = false;
};
#endif /* sjf_multislider_h */
