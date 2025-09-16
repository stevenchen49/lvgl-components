#pragma once
#include "window.h"

// Mock ListBox
class wxListBox : public wxWindow {
public:
    wxListBox() = default;
    
    wxListBox(wxWindow* parent, wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              int n = 0, const wxString choices[] = nullptr,
              long style = 0)
        : wxWindow(parent, id, pos, size, style) {
        for (int i = 0; i < n; ++i) {
            items_.push_back(choices[i]);
        }
        std::cout << "[ListBox] Created with " << n << " items" << std::endl;
    }
    
    int GetSelection() const { return selection_; }
    
    void SetSelection(int selection) {
        if (selection >= 0 && selection < static_cast<int>(items_.size())) {
            selection_ = selection;
            std::cout << "[ListBox] Selection changed to: " << selection << std::endl;
            TriggerEvent(wxEVT_LISTBOX);
        }
    }
    
    void Append(const wxString& item) {
        items_.push_back(item);
        std::cout << "[ListBox] Added item: '" << item << "'" << std::endl;
    }
    
private:
    std::vector<wxString> items_;
    int selection_ = -1;
};
