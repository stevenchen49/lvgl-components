#pragma once
#include "window.h"

// Mock Button
class wxButton : public wxWindow {
public:
    wxButton() = default;
    
    wxButton(wxWindow* parent, wxWindowID id, const wxString& label,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0)
        : wxWindow(parent, id, pos, size, style), label_(label) {
        std::cout << "[Button] Created button with label: '" << label << "'" << std::endl;
    }
    
    const wxString& GetLabel() const { return label_; }
    
    void SetLabel(const wxString& label) {
        label_ = label;
        std::cout << "[Button] Label changed to: '" << label << "'" << std::endl;
    }
    
    void SetDefault() {
        isDefault_ = true;
        std::cout << "[Button] Set as default button" << std::endl;
    }
    
    bool IsDefault() const { return isDefault_; }
    
    // 模拟点击
    void SimulateClick() {
        std::cout << "[Button] Simulating click on: '" << label_ << "'" << std::endl;
        TriggerEvent(wxEVT_BUTTON);
    }
    
private:
    wxString label_;
    bool isDefault_ = false;
};

// Mock Bitmap Button
class wxBitmapButton : public wxButton {
public:
    wxBitmapButton() = default;
    
    wxBitmapButton(wxWindow* parent, wxWindowID id, const wxString& bitmap,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0)
        : wxButton(parent, id, "", pos, size, style), bitmapPath_(bitmap) {
        std::cout << "[BitmapButton] Created with bitmap: " << bitmap << std::endl;
    }
    
private:
    wxString bitmapPath_;
};

// Mock Toggle Button
class wxBitmapToggleButton : public wxButton {
public:
    wxBitmapToggleButton() = default;
    
    wxBitmapToggleButton(wxWindow* parent, wxWindowID id, const wxString& bitmap,
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize,
                         long style = 0)
        : wxButton(parent, id, "", pos, size, style), bitmapPath_(bitmap) {
        std::cout << "[BitmapToggleButton] Created with bitmap: " << bitmap << std::endl;
    }
    
    bool GetValue() const { return toggled_; }
    
    void SetValue(bool value) {
        toggled_ = value;
        std::cout << "[BitmapToggleButton] Toggled to: " << (value ? "ON" : "OFF") << std::endl;
    }
    
private:
    wxString bitmapPath_;
    bool toggled_ = false;
};
