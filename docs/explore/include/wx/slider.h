#pragma once
#include "window.h"

// Mock Slider
class wxSlider : public wxWindow {
public:
    wxSlider() = default;
    
    wxSlider(wxWindow* parent, wxWindowID id, int value, int minValue, int maxValue,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0)
        : wxWindow(parent, id, pos, size, style), 
          value_(value), min_(minValue), max_(maxValue) {
        std::cout << "[Slider] Created with range [" << minValue << ", " << maxValue 
                  << "] value: " << value << std::endl;
    }
    
    int GetValue() const { return value_; }
    
    void SetValue(int value) {
        if (value < min_) value = min_;
        if (value > max_) value = max_;
        
        if (value_ != value) {
            value_ = value;
            std::cout << "[Slider] Value changed to: " << value << std::endl;
            TriggerEvent(wxEVT_SLIDER);
        }
    }
    
    int GetMin() const { return min_; }
    int GetMax() const { return max_; }
    
    void SetRange(int min, int max) {
        min_ = min;
        max_ = max;
        std::cout << "[Slider] Range changed to [" << min << ", " << max << "]" << std::endl;
        if (value_ < min_) SetValue(min_);
        if (value_ > max_) SetValue(max_);
    }
    
private:
    int value_ = 0;
    int min_ = 0;
    int max_ = 100;
};
