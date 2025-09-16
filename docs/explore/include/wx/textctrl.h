#pragma once
#include "window.h"

// Mock Text Control
class wxTextCtrl : public wxWindow {
public:
    wxTextCtrl() = default;
    
    wxTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = "",
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0)
        : wxWindow(parent, id, pos, size, style), value_(value) {
        std::cout << "[TextCtrl] Created with initial value: '" << value << "'" << std::endl;
        if (style & wxTE_MULTILINE) {
            std::cout << "[TextCtrl] Multiline mode enabled" << std::endl;
        }
    }
    
    const wxString& GetValue() const { return value_; }
    
    void SetValue(const wxString& value) {
        value_ = value;
        std::cout << "[TextCtrl] Value changed to: '" << value << "'" << std::endl;
        TriggerEvent(wxEVT_TEXT);
    }
    
    void DiscardEdits() {
        std::cout << "[TextCtrl] Discarding edits" << std::endl;
    }
    
    void SetFocus() {
        std::cout << "[TextCtrl] Gaining focus" << std::endl;
    }
    
    // 模拟用户输入
    void SimulateInput(const wxString& text) {
        SetValue(text);
        if (GetWindowStyle() & wxTE_PROCESS_ENTER) {
            std::cout << "[TextCtrl] Simulating Enter key press" << std::endl;
            TriggerEvent(wxEVT_TEXT_ENTER);
        }
    }
    
private:
    wxString value_;
};

// Mock Spin Control
class wxSpinCtrl : public wxWindow {
public:
    wxSpinCtrl() = default;
    
    wxSpinCtrl(wxWindow* parent, wxWindowID id, const wxString& value = "",
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               int min = 0, int max = 100, int initial = 0)
        : wxWindow(parent, id, pos, size, style), 
          value_(initial), min_(min), max_(max) {
        std::cout << "[SpinCtrl] Created with range [" << min << ", " << max 
                  << "] initial value: " << initial << std::endl;
    }
    
    int GetValue() const { return value_; }
    
    void SetValue(int value) {
        if (value < min_) value = min_;
        if (value > max_) value = max_;
        
        if (value_ != value) {
            value_ = value;
            std::cout << "[SpinCtrl] Value changed to: " << value << std::endl;
            TriggerEvent(wxEVT_SPINCTRL);
        }
    }
    
    void SetRange(int min, int max) {
        min_ = min;
        max_ = max;
        std::cout << "[SpinCtrl] Range changed to [" << min << ", " << max << "]" << std::endl;
        if (value_ < min_) SetValue(min_);
        if (value_ > max_) SetValue(max_);
    }
    
    // 模拟旋转
    void SimulateSpin(int delta) {
        SetValue(value_ + delta);
    }
    
private:
    int value_ = 0;
    int min_ = 0;
    int max_ = 100;
};
