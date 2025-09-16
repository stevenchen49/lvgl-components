#pragma once
#include "window.h"

// Mock Gauge (Progress Bar)
class wxGauge : public wxWindow {
public:
    wxGauge() = default;
    
    wxGauge(wxWindow* parent, wxWindowID id, int range,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0)
        : wxWindow(parent, id, pos, size, style), range_(range) {
        std::cout << "[Gauge] Created with range: " << range << std::endl;
    }
    
    int GetValue() const { return value_; }
    
    void SetValue(int value) {
        if (value < 0) value = 0;
        if (value > range_) value = range_;
        
        if (value_ != value) {
            value_ = value;
            std::cout << "[Gauge] Progress: " << value << "/" << range_ 
                      << " (" << (100 * value / range_) << "%)" << std::endl;
        }
    }
    
    int GetRange() const { return range_; }
    
    void SetRange(int range) {
        range_ = range;
        std::cout << "[Gauge] Range changed to: " << range << std::endl;
        if (value_ > range_) SetValue(range_);
    }
    
private:
    int value_ = 0;
    int range_ = 100;
};
