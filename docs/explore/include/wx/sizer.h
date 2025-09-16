#pragma once
#include "wx.h"
#include <vector>
#include <memory>

// 前向声明
class wxWindow;

// Mock Sizer基类
class wxSizer {
public:
    wxSizer() = default;
    virtual ~wxSizer() = default;
    
    virtual void Add(wxWindow* window, const wxSizerFlags& flags = wxSizerFlags()) {
        std::cout << "[Sizer] Adding window to sizer with flags" << std::endl;
        children_.push_back({window, nullptr, flags});
    }
    
    virtual void Add(wxSizer* sizer, const wxSizerFlags& flags = wxSizerFlags()) {
        std::cout << "[Sizer] Adding sub-sizer with flags" << std::endl;
        children_.push_back({nullptr, sizer, flags});
    }
    
    virtual void SetSizeHints(wxWindow* window) {
        std::cout << "[Sizer] Setting size hints for window" << std::endl;
        (void)window; // 避免未使用参数警告
    }
    
    virtual void Layout() {
        std::cout << "[Sizer] Performing layout calculation" << std::endl;
    }
    
protected:
    struct SizerItem {
        wxWindow* window;
        wxSizer* sizer;
        wxSizerFlags flags;
    };
    std::vector<SizerItem> children_;
};

// Box Sizer
class wxBoxSizer : public wxSizer {
public:
    explicit wxBoxSizer(wxOrientation orient) : orientation_(orient) {
        std::cout << "[BoxSizer] Created " 
                  << (orient == wxHORIZONTAL ? "horizontal" : "vertical") 
                  << " box sizer" << std::endl;
    }
    
private:
    wxOrientation orientation_;
};

// Static Box
class wxStaticBox : public wxWindow {
public:
    wxStaticBox(wxWindow* parent, wxWindowID id, const wxString& label);
    
    const wxString& GetLabel() const { return label_; }
    void SetLabel(const wxString& label) { 
        label_ = label;
        std::cout << "[StaticBox] Label changed to: " << label << std::endl;
    }
    
private:
    wxString label_;
};

// Static Box Sizer
class wxStaticBoxSizer : public wxBoxSizer {
public:
    wxStaticBoxSizer(wxStaticBox* box, wxOrientation orient) 
        : wxBoxSizer(orient), staticBox_(box) {
        std::cout << "[StaticBoxSizer] Created with label: " << box->GetLabel() << std::endl;
    }
    
private:
    wxStaticBox* staticBox_;
};

// 实现SetSizerAndFit
inline void wxWindow::SetSizerAndFit(wxSizer* sizer) {
    SetSizer(sizer);
    sizer->SetSizeHints(this);
    std::cout << "[Window] Sizer attached and fitted" << std::endl;
}