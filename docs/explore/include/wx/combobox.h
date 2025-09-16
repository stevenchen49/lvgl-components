#pragma once
#include "textctrl.h"

// Mock ComboBox
class wxComboBox : public wxTextCtrl {
public:
    wxComboBox() = default;
    
    wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value = "",
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               int n = 0, const wxString choices[] = nullptr,
               long style = 0)
        : wxTextCtrl(parent, id, value, pos, size, style) {
        for (int i = 0; i < n; ++i) {
            choices_.push_back(choices[i]);
        }
        std::cout << "[ComboBox] Created with " << n << " choices" << std::endl;
    }
    
    int GetSelection() const { return selection_; }
    
    void SetSelection(int selection) {
        if (selection >= 0 && selection < static_cast<int>(choices_.size())) {
            selection_ = selection;
            SetValue(choices_[selection]);
            std::cout << "[ComboBox] Selection changed to: " << selection << std::endl;
            TriggerEvent(wxEVT_COMBOBOX);
        }
    }
    
    void Append(const wxString& item) {
        choices_.push_back(item);
        std::cout << "[ComboBox] Added item: '" << item << "'" << std::endl;
    }
    
private:
    std::vector<wxString> choices_;
    int selection_ = -1;
};

// Mock Bitmap ComboBox
class wxBitmapComboBox : public wxComboBox {
public:
    wxBitmapComboBox() = default;
    
    wxBitmapComboBox(wxWindow* parent, wxWindowID id, const wxString& value = "",
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     long style = 0)
        : wxComboBox(parent, id, value, pos, size, 0, nullptr, style) {
        std::cout << "[BitmapComboBox] Created" << std::endl;
    }
};
