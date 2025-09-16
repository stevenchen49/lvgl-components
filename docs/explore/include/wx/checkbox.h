#pragma once
#include "window.h"

// Mock CheckBox
class wxCheckBox : public wxWindow {
public:
    wxCheckBox() = default;
    
    wxCheckBox(wxWindow* parent, wxWindowID id, const wxString& label,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0)
        : wxWindow(parent, id, pos, size, style), label_(label) {
        std::cout << "[CheckBox] Created with label: '" << label << "'" << std::endl;
    }
    
    bool GetValue() const { return checked_; }
    
    void SetValue(bool value) {
        if (checked_ != value) {
            checked_ = value;
            std::cout << "[CheckBox] " << (value ? "Checked" : "Unchecked") 
                      << " '" << label_ << "'" << std::endl;
            TriggerEvent(wxEVT_CHECKBOX);
        }
    }
    
    const wxString& GetLabel() const { return label_; }
    
    void SetLabel(const wxString& label) {
        label_ = label;
        std::cout << "[CheckBox] Label changed to: '" << label << "'" << std::endl;
    }
    
    // 模拟点击
    void SimulateClick() {
        SetValue(!checked_);
    }
    
private:
    wxString label_;
    bool checked_ = false;
};

// Mock Choice Control
class wxChoice : public wxWindow {
public:
    wxChoice() = default;
    
    wxChoice(wxWindow* parent, wxWindowID id,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             int n = 0, const wxString choices[] = nullptr,
             long style = 0)
        : wxWindow(parent, id, pos, size, style) {
        for (int i = 0; i < n; ++i) {
            choices_.push_back(choices[i]);
        }
        std::cout << "[Choice] Created with " << n << " choices" << std::endl;
    }
    
    int GetSelection() const { return selection_; }
    
    void SetSelection(int selection) {
        if (selection >= 0 && selection < static_cast<int>(choices_.size())) {
            selection_ = selection;
            std::cout << "[Choice] Selection changed to: " << selection 
                      << " ('" << choices_[selection] << "')" << std::endl;
            TriggerEvent(wxEVT_CHOICE);
        }
    }
    
    wxString GetStringSelection() const {
        if (selection_ >= 0 && selection_ < static_cast<int>(choices_.size())) {
            return choices_[selection_];
        }
        return "";
    }
    
    void Append(const wxString& item) {
        choices_.push_back(item);
        std::cout << "[Choice] Added choice: '" << item << "'" << std::endl;
    }
    
private:
    std::vector<wxString> choices_;
    int selection_ = -1;
};
