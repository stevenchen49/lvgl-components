#pragma once
#include "wx.h"

// Mock Application
class wxApp {
public:
    wxApp() {
        std::cout << "[App] wxApp created" << std::endl;
    }
    
    virtual ~wxApp() {
        std::cout << "[App] wxApp destroyed" << std::endl;
    }
    
    virtual bool OnInit() {
        std::cout << "[App] OnInit() called" << std::endl;
        return true;
    }
    
    virtual int OnExit() {
        std::cout << "[App] OnExit() called" << std::endl;
        return 0;
    }
    
    void SetTopWindow(wxWindow* window) {
        topWindow_ = window;
        std::cout << "[App] Top window set" << std::endl;
    }
    
    wxWindow* GetTopWindow() const { return topWindow_; }
    
    // 模拟主循环
    int MainLoop() {
        std::cout << "[App] Entering main loop" << std::endl;
        // 在真实应用中，这里会是事件循环
        // 我们只是模拟一下
        std::cout << "[App] Main loop running..." << std::endl;
        std::cout << "[App] Exiting main loop" << std::endl;
        return OnExit();
    }
    
private:
    wxWindow* topWindow_ = nullptr;
};

// Mock Frame
class wxFrame : public wxWindow {
public:
    wxFrame() = default;
    
    wxFrame(wxWindow* parent, wxWindowID id, const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0)
        : wxWindow(parent, id, pos, size, style), title_(title) {
        std::cout << "[Frame] Created frame with title: '" << title << "'" << std::endl;
    }
    
    const wxString& GetTitle() const { return title_; }
    
    void SetTitle(const wxString& title) {
        title_ = title;
        std::cout << "[Frame] Title changed to: '" << title << "'" << std::endl;
    }
    
    void Show(bool show = true) {
        visible_ = show;
        std::cout << "[Frame] " << (show ? "Showing" : "Hiding") << " frame" << std::endl;
    }
    
    bool IsShown() const { return visible_; }
    
    void Close(bool force = false) {
        std::cout << "[Frame] Closing frame" << (force ? " (forced)" : "") << std::endl;
        visible_ = false;
    }
    
    // 状态栏
    void CreateStatusBar(int number = 1) {
        statusBarFields_ = number;
        std::cout << "[Frame] Created status bar with " << number << " fields" << std::endl;
    }
    
    void SetStatusText(const wxString& text, int field = 0) {
        std::cout << "[Frame] Status bar field " << field << ": '" << text << "'" << std::endl;
    }
    
    // 菜单栏
    void SetMenuBar(void* menuBar) {
        std::cout << "[Frame] Menu bar attached" << std::endl;
    }
    
private:
    wxString title_;
    bool visible_ = false;
    int statusBarFields_ = 0;
};

// Mock Dialog
class wxDialog : public wxFrame {
public:
    wxDialog() = default;
    
    wxDialog(wxWindow* parent, wxWindowID id, const wxString& title,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0)
        : wxFrame(parent, id, title, pos, size, style) {
        std::cout << "[Dialog] Created dialog with title: '" << title << "'" << std::endl;
    }
    
    int ShowModal() {
        std::cout << "[Dialog] Showing modal dialog" << std::endl;
        Show(true);
        // 模拟模态对话框
        std::cout << "[Dialog] Modal dialog closed with result: OK" << std::endl;
        return wxID_OK;
    }
    
    void EndModal(int retCode) {
        std::cout << "[Dialog] Ending modal dialog with code: " << retCode << std::endl;
        Show(false);
    }
};

// 标准对话框按钮
inline wxSizer* CreateStdDialogButtonSizer(long flags) {
    std::cout << "[StdButtons] Creating standard dialog buttons with flags: " << flags << std::endl;
    return new wxBoxSizer(wxHORIZONTAL);
}

// 应用程序宏
#define wxIMPLEMENT_APP(appclass) \
    int main() { \
        std::cout << "[Main] Starting wxUI Mock Explorer" << std::endl; \
        appclass app; \
        if (app.OnInit()) { \
            return app.MainLoop(); \
        } \
        return -1; \
    }
