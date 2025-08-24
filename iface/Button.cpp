#include "Button.h"

namespace Gui {

// ==================== 构造函数/析构函数 ====================

Button::Button() : Component()
{
}

Button::~Button()
{
}

// ==================== 核心方法 ====================

lv_obj_t* Button::createObject(lv_obj_t* parent)
{
    return _lvCreateButton(parent);
}

} // namespace Gui