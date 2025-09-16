#pragma once
#include "window.h"

// Mock Static Text
class wxStaticText : public wxWindow {
public:
    wxStaticText() = default;
    
    wxStaticText(wxWindow* parent, wxWindowID id, const wxString& label,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0)
        : wxWindow(parent, id, pos, size, style), label_(label) {
        std::cout << "[StaticText] Created with text: '" << label << "'" << std::endl;
    }
    
    const wxString& GetLabel() const { return label_; }
    
    void SetLabel(const wxString& label) {
        label_ = label;
        std::cout << "[StaticText] Text changed to: '" << label << "'" << std::endl;
    }
    
    void Wrap(int width) {
        wrapWidth_ = width;
        std::cout << "[StaticText] Text wrapped at width: " << width << std::endl;
    }
    
private:
    wxString label_;
    int wrapWidth_ = -1;
};

// Mock Static Bitmap
class wxStaticBitmap : public wxWindow {
public:
    wxStaticBitmap() = default;
    
    wxStaticBitmap(wxWindow* parent, wxWindowID id, const wxString& bitmap,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0)
        : wxWindow(parent, id, pos, size, style), bitmapPath_(bitmap) {
        std::cout << "[StaticBitmap] Created with bitmap: " << bitmap << std::endl;
    }
    
private:
    wxString bitmapPath_;
};

// Mock Static Line
class wxStaticLine : public wxWindow {
public:
    wxStaticLine() = default;
    
    wxStaticLine(wxWindow* parent, wxWindowID id,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0)
        : wxWindow(parent, id, pos, size, style) {
        std::cout << "[StaticLine] Created separator line" << std::endl;
    }
};
