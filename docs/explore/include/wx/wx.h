#pragma once
// Mock wxWidgets 统一头文件

#include <string>
#include <functional>
#include <memory>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

// 基本类型定义
using wxWindowID = int;
using wxString = std::string;

// 常量定义
constexpr wxWindowID wxID_ANY = -1;
constexpr wxWindowID wxID_OK = 5100;
constexpr wxWindowID wxID_CANCEL = 5101;
constexpr wxWindowID wxID_EXIT = 5006;
constexpr wxWindowID wxID_ABOUT = 5014;
constexpr wxWindowID wxID_FIND = 5030;

// 位置和大小
struct wxPoint {
    int x, y;
    wxPoint(int x = 0, int y = 0) : x(x), y(y) {}
};

struct wxSize {
    int width, height;
    wxSize(int w = -1, int h = -1) : width(w), height(h) {}
    void SetWidth(int w) { width = w; }
    void SetHeight(int h) { height = h; }
};

const wxPoint wxDefaultPosition{-1, -1};
const wxSize wxDefaultSize{-1, -1};

// 样式常量
constexpr long wxALIGN_LEFT = 0x0100;
constexpr long wxTE_MULTILINE = 0x0020;
constexpr long wxTE_PROCESS_ENTER = 0x0400;
constexpr long wxBU_EXACTFIT = 0x0001;
constexpr long wxRA_SPECIFY_ROWS = 0x0001;

// 方向常量
enum wxOrientation {
    wxHORIZONTAL = 0x0004,
    wxVERTICAL = 0x0008
};

// 事件类型
class wxEvent {
public:
    virtual ~wxEvent() = default;
};

class wxCommandEvent : public wxEvent {
public:
    bool IsChecked() const { return checked_; }
    void SetChecked(bool checked) { checked_ = checked; }
private:
    bool checked_ = false;
};

// 事件类型常量
constexpr int wxEVT_BUTTON = 10000;
constexpr int wxEVT_TEXT = 10001;
constexpr int wxEVT_TEXT_ENTER = 10002;
constexpr int wxEVT_CHECKBOX = 10003;
constexpr int wxEVT_CHOICE = 10004;
constexpr int wxEVT_COMBOBOX = 10005;
constexpr int wxEVT_LISTBOX = 10006;
constexpr int wxEVT_RADIOBOX = 10007;
constexpr int wxEVT_SLIDER = 10008;
constexpr int wxEVT_SPINCTRL = 10009;
constexpr int wxEVT_TOGGLEBUTTON = 10010;
constexpr int wxEVT_MENU = 10011;

// 字体信息
struct wxFontInfo {
    int pointSize = 12;
    std::string faceName = "Default";
    
    wxFontInfo(int size) : pointSize(size) {}
    wxFontInfo& FaceName(const std::string& name) { faceName = name; return *this; }
};

struct wxFont {
    wxFontInfo info;
    wxFont(const wxFontInfo& fontInfo) : info(fontInfo) {}
};

// Sizer标志
class wxSizerFlags {
public:
    wxSizerFlags(int proportion = 0) : proportion_(proportion) {}
    
    wxSizerFlags& Expand() { expand_ = true; return *this; }
    wxSizerFlags& Border(int direction = 0x000F, int borderInPixels = 5) { 
        border_ = borderInPixels; 
        borderDirection_ = direction;
        return *this; 
    }
    wxSizerFlags& Center() { center_ = true; return *this; }
    wxSizerFlags& Centre() { return Center(); }
    
    int GetProportion() const { return proportion_; }
    bool ShouldExpand() const { return expand_; }
    int GetBorder() const { return border_; }
    bool ShouldCenter() const { return center_; }
    
private:
    int proportion_ = 0;
    bool expand_ = false;
    int border_ = 0;
    int borderDirection_ = 0;
    bool center_ = false;
};

// 日志系统
template<typename... Args>
void wxLogMessage(const std::string& format, Args... args) {
    std::cout << "[wxLog] ";
    printf(format.c_str(), args...);
    std::cout << std::endl;
}

inline void wxLogMessage(const std::string& message) {
    std::cout << "[wxLog] " << message << std::endl;
}

// =============================================================================
// 窗口和控件类定义
// =============================================================================

// Mock Sizer基类
class wxSizer {
public:
    wxSizer() = default;
    virtual ~wxSizer() = default;
    
    virtual void Add(class wxWindow* window, const wxSizerFlags& flags = wxSizerFlags());
    virtual void Add(wxSizer* sizer, const wxSizerFlags& flags = wxSizerFlags());
    virtual void SetSizeHints(class wxWindow* window);
    virtual void Layout();
    
protected:
    struct SizerItem {
        class wxWindow* window;
        wxSizer* sizer;
        wxSizerFlags flags;
    };
    std::vector<SizerItem> children_;
};

// Mock Window基类
class wxWindow {
public:
    wxWindow() = default;
    wxWindow(wxWindow* parent, wxWindowID id, 
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0)
        : parent_(parent), id_(id), pos_(pos), size_(size), style_(style) {
        if (parent) {
            parent->AddChild(this);
        }
        std::cout << "[Window] Created window with ID: " << id << std::endl;
    }
    
    virtual ~wxWindow() {
        std::cout << "[Window] Destroying window with ID: " << id_ << std::endl;
    }
    
    // 基本属性
    wxWindowID GetId() const { return id_; }
    wxWindow* GetParent() const { return parent_; }
    const wxPoint& GetPosition() const { return pos_; }
    const wxSize& GetSize() const { return size_; }
    long GetWindowStyle() const { return style_; }
    
    void SetSize(const wxSize& size) { 
        size_ = size;
        std::cout << "[Window] Size changed to: " << size.width << "x" << size.height << std::endl;
    }
    
    void SetPosition(const wxPoint& pos) { 
        pos_ = pos;
        std::cout << "[Window] Position changed to: (" << pos.x << ", " << pos.y << ")" << std::endl;
    }
    
    // 启用/禁用
    void Enable(bool enable = true) { 
        enabled_ = enable;
        std::cout << "[Window] " << (enable ? "Enabled" : "Disabled") << " window" << std::endl;
    }
    
    bool IsEnabled() const { return enabled_; }
    
    // 字体
    void SetFont(const wxFont& font) {
        font_ = std::make_unique<wxFont>(font);
        std::cout << "[Window] Font changed to: " << font.info.faceName 
                  << " size " << font.info.pointSize << std::endl;
    }
    
    // Sizer管理
    void SetSizer(wxSizer* sizer) { 
        sizer_ = sizer;
        std::cout << "[Window] Sizer attached to window" << std::endl;
    }
    
    wxSizer* GetSizer() const { return sizer_; }
    
    void SetSizerAndFit(wxSizer* sizer) {
        SetSizer(sizer);
        sizer->SetSizeHints(this);
        std::cout << "[Window] Sizer attached and fitted" << std::endl;
    }
    
    // 简化的事件绑定
    template<typename Function>
    void Bind(int eventType, Function&& func, wxWindowID id = wxID_ANY) {
        std::cout << "[Window] Binding event type " << eventType 
                  << " for window ID " << (id == wxID_ANY ? id_ : id) << std::endl;
        
        eventHandlers_[eventType] = [func](wxEvent& e) {
            if constexpr (std::is_invocable_v<Function, wxCommandEvent&>) {
                func(static_cast<wxCommandEvent&>(e));
            } else {
                func();
            }
        };
    }
    
    // 触发事件（用于测试）
    void TriggerEvent(int eventType) {
        auto it = eventHandlers_.find(eventType);
        if (it != eventHandlers_.end()) {
            std::cout << "[Window] Triggering event type " << eventType << std::endl;
            wxCommandEvent event;
            it->second(event);
        }
    }
    
    // 查找子窗口
    wxWindow* FindWindow(wxWindowID id) {
        if (id_ == id) return this;
        for (auto* child : children_) {
            if (auto* found = child->FindWindow(id)) {
                return found;
            }
        }
        return nullptr;
    }
    
protected:
    void AddChild(wxWindow* child) {
        children_.push_back(child);
        std::cout << "[Window] Added child window" << std::endl;
    }
    
    wxWindow* parent_ = nullptr;
    wxWindowID id_ = wxID_ANY;
    wxPoint pos_;
    wxSize size_;
    long style_ = 0;
    bool enabled_ = true;
    std::unique_ptr<wxFont> font_;
    wxSizer* sizer_ = nullptr;
    std::vector<wxWindow*> children_;
    std::map<int, std::function<void(wxEvent&)>> eventHandlers_;
};

// 实现Sizer方法
inline void wxSizer::Add(wxWindow* window, const wxSizerFlags& flags) {
    std::cout << "[Sizer] Adding window to sizer with flags" << std::endl;
    children_.push_back({window, nullptr, flags});
}

inline void wxSizer::Add(wxSizer* sizer, const wxSizerFlags& flags) {
    std::cout << "[Sizer] Adding sub-sizer with flags" << std::endl;
    children_.push_back({nullptr, sizer, flags});
}

inline void wxSizer::SetSizeHints(wxWindow* window) {
    std::cout << "[Sizer] Setting size hints for window" << std::endl;
    (void)window; // 避免未使用参数警告
}

inline void wxSizer::Layout() {
    std::cout << "[Sizer] Performing layout calculation" << std::endl;
}

// Box Sizer
class wxBoxSizer : public wxSizer {
public:
    explicit wxBoxSizer(wxOrientation orient) {
        std::cout << "[BoxSizer] Created " 
                  << (orient == wxHORIZONTAL ? "horizontal" : "vertical") 
                  << " box sizer" << std::endl;
    }
};

// 应用程序类
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
    
    int MainLoop() {
        std::cout << "[App] Entering main loop" << std::endl;
        std::cout << "[App] Main loop running..." << std::endl;
        std::cout << "[App] Exiting main loop" << std::endl;
        return OnExit();
    }
    
private:
    wxWindow* topWindow_ = nullptr;
};

// Frame类
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
    
    void CreateStatusBar(int number = 1) {
        statusBarFields_ = number;
        std::cout << "[Frame] Created status bar with " << number << " fields" << std::endl;
    }
    
    void SetStatusText(const wxString& text, int field = 0) {
        std::cout << "[Frame] Status bar field " << field << ": '" << text << "'" << std::endl;
    }
    
    void SetMenuBar(void* menuBar) {
        std::cout << "[Frame] Menu bar attached" << std::endl;
        (void)menuBar; // 避免未使用参数警告
    }
    
private:
    wxString title_;
    bool visible_ = false;
    int statusBarFields_ = 0;
};

// Dialog类
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
        std::cout << "[Dialog] Modal dialog closed with result: OK" << std::endl;
        return wxID_OK;
    }
    
    void EndModal(int retCode) {
        std::cout << "[Dialog] Ending modal dialog with code: " << retCode << std::endl;
        Show(false);
    }
};

// =============================================================================
// 控件类定义
// =============================================================================

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
        (void)value; // 避免未使用参数警告
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

// Mock Slider
class wxSlider : public wxWindow {
public:
    wxSlider() = default;
    
    wxSlider(wxWindow* parent, wxWindowID id, int value, int minValue, int maxValue,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0)
        : wxWindow(parent, id, pos, size, style), 
          value_(value), min_(minValue), max_(maxValue) {
        std::cout << "[Slider] Created with range [" << minValue << ", " << maxValue 
                  << "] value: " << value << std::endl;
    }
    
    int GetValue() const { return value_; }
    
    void SetValue(int value) {
        if (value < min_) value = min_;
        if (value > max_) value = max_;
        
        if (value_ != value) {
            value_ = value;
            std::cout << "[Slider] Value changed to: " << value << std::endl;
            TriggerEvent(wxEVT_SLIDER);
        }
    }
    
    int GetMin() const { return min_; }
    int GetMax() const { return max_; }
    
    void SetRange(int min, int max) {
        min_ = min;
        max_ = max;
        std::cout << "[Slider] Range changed to [" << min << ", " << max << "]" << std::endl;
        if (value_ < min_) SetValue(min_);
        if (value_ > max_) SetValue(max_);
    }
    
private:
    int value_ = 0;
    int min_ = 0;
    int max_ = 100;
};

// Mock Gauge (Progress Bar)
class wxGauge : public wxWindow {
public:
    wxGauge() = default;
    
    wxGauge(wxWindow* parent, wxWindowID id, int range,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0)
        : wxWindow(parent, id, pos, size, style), range_(range) {
        std::cout << "[Gauge] Created with range: " << range << std::endl;
    }
    
    int GetValue() const { return value_; }
    
    void SetValue(int value) {
        if (value < 0) value = 0;
        if (value > range_) value = range_;
        
        if (value_ != value) {
            value_ = value;
            std::cout << "[Gauge] Progress: " << value << "/" << range_ 
                      << " (" << (100 * value / range_) << "%)" << std::endl;
        }
    }
    
    int GetRange() const { return range_; }
    
    void SetRange(int range) {
        range_ = range;
        std::cout << "[Gauge] Range changed to: " << range << std::endl;
        if (value_ > range_) SetValue(range_);
    }
    
private:
    int value_ = 0;
    int range_ = 100;
};

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