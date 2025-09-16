#pragma once
#include "wx.h"
#include <functional>
#include <map>

// 前向声明
class wxSizer;

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
    
    void SetSizerAndFit(wxSizer* sizer);
    
    // 简化的事件绑定 - 使用int类型的事件ID
    template<typename Function>
    void Bind(int eventType, Function&& func, wxWindowID id = wxID_ANY) {
        std::cout << "[Window] Binding event type " << eventType 
                  << " for window ID " << (id == wxID_ANY ? id_ : id) << std::endl;
        
        // 存储事件处理器（简化版）
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