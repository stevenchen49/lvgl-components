#pragma once
#include "window.h"

// Mock Hyperlink Control
class wxHyperlinkCtrl : public wxWindow {
public:
    wxHyperlinkCtrl() = default;
    
    wxHyperlinkCtrl(wxWindow* parent, wxWindowID id, const wxString& label, const wxString& url,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0)
        : wxWindow(parent, id, pos, size, style), label_(label), url_(url) {
        std::cout << "[HyperlinkCtrl] Created link '" << label << "' -> '" << url << "'" << std::endl;
    }
    
    const wxString& GetLabel() const { return label_; }
    const wxString& GetURL() const { return url_; }
    
    void SetLabel(const wxString& label) {
        label_ = label;
        std::cout << "[HyperlinkCtrl] Label changed to: '" << label << "'" << std::endl;
    }
    
    void SetURL(const wxString& url) {
        url_ = url;
        std::cout << "[HyperlinkCtrl] URL changed to: '" << url << "'" << std::endl;
    }
    
private:
    wxString label_;
    wxString url_;
};
