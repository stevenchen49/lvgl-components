#pragma once
#include "window.h"

// Mock RadioBox
class wxRadioBox : public wxWindow {
public:
    wxRadioBox() = default;
    
    wxRadioBox(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               int n = 0, const wxString choices[] = nullptr,
               int majorDim = 1, long style = 0)
        : wxWindow(parent, id, pos, size, style), title_(title), majorDim_(majorDim) {
        for (int i = 0; i < n; ++i) {
            choices_.push_back(choices[i]);
        }
        std::cout << "[RadioBox] Created '" << title << "' with " << n << " choices" << std::endl;
    }
    
    int GetSelection() const { return selection_; }
    
    void SetSelection(int selection) {
        if (selection >= 0 && selection < static_cast<int>(choices_.size())) {
            selection_ = selection;
            std::cout << "[RadioBox] Selection changed to: " << selection 
                      << " ('" << choices_[selection] << "')" << std::endl;
            TriggerEvent(wxEVT_RADIOBOX);
        }
    }
    
    const wxString& GetLabel() const { return title_; }
    
private:
    wxString title_;
    std::vector<wxString> choices_;
    int selection_ = 0;
    int majorDim_ = 1;
};
