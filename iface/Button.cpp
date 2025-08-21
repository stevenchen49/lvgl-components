#include "Button.h"
#include "../impls/lv8/ButtonLv8.cpp"

namespace Gui {

Button::Button() 
    : Component(), mToggleMode(false), mChecked(false)
{
}

Button::Button(const ButtonConfig& config) 
    : Component(), mButtonConfig(config), mToggleMode(config.toggleMode), mChecked(config.checked)
{
    if (!config.buttonText.empty()) {
        mButtonText = config.buttonText;
    }
    
    // 从 ButtonConfig 初始化 Component 的配置
    ComponentConfig compConfig;
    compConfig.visible = config.visible;
    compConfig.enabled = config.enabled;
    compConfig.clickable = config.clickable;
    compConfig.focusable = config.focusable;
    compConfig.style.bgColor = config.state.normalBgColor;
    compConfig.style.textColor = config.state.normalTextColor;
    compConfig.style.radius = config.buttonStyle.cornerRadius;
    compConfig.style.borderWidth = config.buttonStyle.borderWidth;
    compConfig.style.borderColor = config.buttonStyle.borderColor;
    compConfig.text.content = config.buttonText;
    compConfig.text.enabled = !config.buttonText.empty();
    
    mConfig = compConfig;
}

Button::Button(const std::string& text) 
    : Component(), mButtonText(text), mToggleMode(false), mChecked(false)
{
}

Button::Button(const std::string& text, const ButtonConfig& config) 
    : Component(), mButtonConfig(config), mButtonText(text), mToggleMode(config.toggleMode), mChecked(config.checked)
{
    // 从 ButtonConfig 初始化 Component 的配置
    ComponentConfig compConfig;
    compConfig.visible = config.visible;
    compConfig.enabled = config.enabled;
    compConfig.clickable = config.clickable;
    compConfig.focusable = config.focusable;
    compConfig.style.bgColor = config.state.normalBgColor;
    compConfig.style.textColor = config.state.normalTextColor;
    compConfig.style.radius = config.buttonStyle.cornerRadius;
    compConfig.style.borderWidth = config.buttonStyle.borderWidth;
    compConfig.style.borderColor = config.buttonStyle.borderColor;
    compConfig.text.content = text;
    compConfig.text.enabled = !text.empty();
    
    mConfig = compConfig;
}

Button::~Button()
{
}

lv_obj_t* Button::createObject(lv_obj_t* parent)
{
    // 使用静态方法创建按钮对象
    mLvObj = _lvCreateButton(parent);
    if (mLvObj) {
        applyConfig();
        applyButtonConfig();
    }
    return mLvObj;
}

void Button::applyButtonConfig()
{
    if (!mLvObj) return;
    
    // 使用静态方法应用配置
    _lvSetConfig(mLvObj, mButtonConfig);
}

Button& Button::setConfig(const ButtonConfig& config)
{
    mButtonConfig = config;
    mToggleMode = config.toggleMode;
    mChecked = config.checked;
    
    if (!config.buttonText.empty()) {
        mButtonText = config.buttonText;
    }
    
    if (mLvObj) {
        applyButtonConfig();
    }
    
    return *this;
}

Button& Button::setButtonText(const std::string& text)
{
    mButtonText = text;
    if (mLvObj) {
        _lvSetButtonText(mLvObj, text);
    }
    return *this;
}

Button& Button::setButtonState(lv_state_t state)
{
    if (mLvObj) {
        _lvSetButtonState(mLvObj, state);
    }
    return *this;
}

Button& Button::setToggleMode(bool enable)
{
    mToggleMode = enable;
    if (mLvObj) {
        _lvSetToggleMode(mLvObj, enable);
    }
    return *this;
}

Button& Button::setChecked(bool checked)
{
    mChecked = checked;
    if (mLvObj) {
        _lvSetChecked(mLvObj, checked);
    }
    return *this;
}

std::string Button::getButtonText() const
{
    if (mLvObj) {
        return _lvGetButtonText(mLvObj);
    }
    return mButtonText;
}

lv_state_t Button::getButtonState() const
{
    if (mLvObj) {
        return _lvGetButtonState(mLvObj);
    }
    return LV_STATE_DEFAULT;
}

bool Button::isToggleMode() const
{
    if (mLvObj) {
        return _lvIsToggleMode(mLvObj);
    }
    return mToggleMode;
}

bool Button::isChecked() const
{
    if (mLvObj) {
        return _lvIsChecked(mLvObj);
    }
    return mChecked;
}

Button& Button::show()
{
    setVisible(true);
    if (mLvObj) {
        _lvShowButton(mLvObj);
    }
    return *this;
}

Button& Button::hide()
{
    setVisible(false);
    if (mLvObj) {
        _lvHideButton(mLvObj);
    }
    return *this;
}

Button& Button::enable()
{
    setEnabled(true);
    if (mLvObj) {
        _lvEnableButton(mLvObj);
    }
    return *this;
}

Button& Button::disable()
{
    setEnabled(false);
    if (mLvObj) {
        _lvDisableButton(mLvObj);
    }
    return *this;
}

Button& Button::setOnClick(std::function<void(lv_event_t*)> callback)
{
    // TODO: 实现点击事件回调
    // 事件处理将在后续版本中实现
    mConfig.event.onClick = callback;
    return *this;
}

Button& Button::setOnLongPress(std::function<void(lv_event_t*)> callback)
{
    // TODO: 实现长按事件回调
    // 事件处理将在后续版本中实现
    mConfig.event.onLongPress = callback;
    return *this;
}

Button& Button::setOnValueChange(std::function<void(lv_event_t*)> callback)
{
    // TODO: 实现值变化事件回调
    // 事件处理将在后续版本中实现
    mConfig.event.onValueChange = callback;
    return *this;
}



} // namespace Gui