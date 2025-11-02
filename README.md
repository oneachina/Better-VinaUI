# VinaUI - 现代化的 Windows UI 框架

![Version](https://img.shields.io/badge/version-2.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)

VinaUI 是一个基于 C++ 的现代化 Windows UI 框架，提供丰富的 UI 组件、动画效果和自定义绘制功能，帮助开发者快速构建美观的桌面应用程序。

## ✨ 特性

### 🎨 丰富的视觉效果
- **高级阴影系统** - 支持简单阴影和外部阴影窗口
- **高斯模糊** - 高性能的区域模糊效果
- **Alpha 混合** - 完整的透明度支持
- **渐变绘制** - 线性渐变和颜色过渡
- **圆角矩形** - 支持任意圆角的 UI 元素

### 🎯 灵活的布局系统
- **多种布局模式** - Free、Left、Pushing、Flex
- **响应式设计** - 自动适应窗口大小变化
- **面板管理** - 多面板切换和状态管理
- **控件容器** - 灵活的控件组织和事件处理

### ⚡ 高性能渲染
- **双渲染后端** - 支持 GDI 和 Direct2D
- **内存优化** - 智能缓存和资源管理
- **GPU 加速** - 利用硬件加速提升性能
- **异步绘制** - 非阻塞的 UI 更新

### 🔧 易用的 API
- **声明式编程** - 简洁的控件创建语法
- **事件驱动** - 统一的鼠标和键盘事件处理
- **类型安全** - 模板化的控件系统
- **模块化设计** - 按需引入功能模块

## 🚀 快速开始

### 环境要求
- Windows 7 或更高版本
- Visual Studio 2015 或更高版本
- 支持 C++11 的编译器

### 基础用法

```cpp
#include "VertexUI.min.h"

VertexUIInit;  // 初始化命名空间

// 创建窗口并设置 VertexUI 样式
HWND hWnd = CreateWindow(...);

// 在 WM_PAINT 消息中绘制 UI
case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    
    VertexUI::Panel::CreatePanel(hWnd, hdc, [](HWND hWnd, HDC hdc) {
        // 绘制背景
        VertexUI::Panel::CreateFillArea(hWnd, hdc, VERTEXUICOLOR_MIDNIGHT);
        
        // 创建圆角按钮
        VertexUI::Panel::CreateRoundButtonEx(hdc, 50, 50, 200, 40, 8, 
            L"点击我", 16, VERTEXUICOLOR_LAVENDER);
    });
    
    EndPaint(hWnd, &ps);
    break;
}
```

### 使用控件系统

```cpp
// 创建控件面板
VertexUI::VertexUIPanel panel;
panel.Set(hWnd, hdc);

// 添加按钮控件
VertexUI::VertexUIColorInfo btnStyle = { VERTEXUICOLOR_LAVENDER, VERTEXUICOLOR_WHITE };
VertexUIControl button;
button.CreateCtl(L"Button", 100, 100, 120, 40, []() {
    MessageBox(NULL, L"按钮被点击!", L"提示", MB_OK);
}, L"我的按钮", btnStyle);

panel.Add(button);
```

## 📁 项目结构

```
VertexUI/
├── VertexUI.min.h              # 主入口文件
├── VertexUI.Colors.h           # 颜色系统和主题定义
├── VertexUI.ClickArea.h        # 点击区域和事件处理
├── VertexUI.Control.hpp        # 控件基类和布局系统
├── VertexUI.Panel.h            # 面板绘制和渲染引擎
├── VertexUI.Animation.hpp      # 动画系统
├── VertexUI.Window.hpp         # 窗口管理和阴影效果
├── VertexUI.Window.Utils.hpp   # 窗口工具函数
├── VertexUI.Window.SimpleShadow.hpp    # 简单阴影
└── VertexUI.Window.OuterShadow.hpp     # 外部阴影
```

## 🎨 颜色系统

VertexUI 提供完整的颜色管理系统：

```cpp
// 使用预定义颜色
CreateRect(hdc, x, y, width, height, VERTEXUICOLOR_MIDNIGHT);
CreateRect(hdc, x, y, width, height, VERTEXUICOLOR_LAVENDER);

// 颜色工具函数
COLORREF brighter = VertexUI::Utils::AdjustColorBrightness(color, 1.2f);
COLORREF interpolated = VertexUI::Utils::InterpolateColor(color1, color2, 0.5f);
```

### 预定义颜色主题
- `VERTEXUICOLOR_MIDNIGHT` - 午夜蓝
- `VERTEXUICOLOR_LAVENDER` - 薰衣草紫  
- `VERTEXUICOLOR_GREENSEA` - 碧海绿
- `VERTEXUICOLOR_WHITE` - 纯白
- `VERTEXUICOLOR_DARKNIGHT` - 深夜晚

## 🔄 动画系统

```cpp
// 淡入动画
VertexUI::Panel::FadeInAnimation(hWnd);

// 缓动动画
VertexUI::Panel::WindowEaseIn(hWnd);

// 自定义动画
VertexUI::Panel::CtlMoveInAnimation(hWnd, rc, animatedValue, moveDistance);
```

## 🖱️ 事件处理

```cpp
// 鼠标事件处理
case WM_MOUSEMOVE:
    VertexUI::Click::SendMouseMoveEvent(hWnd, wParam, lParam);
    break;

case WM_LBUTTONDOWN:
    VertexUI::Click::SendKeepDownEvent(hWnd, wParam, lParam);
    break;

case WM_LBUTTONUP:
    VertexUI::Click::SendClickEvent(hWnd, wParam, lParam);
    break;
```

## 🛠️ 高级功能

### 使用 Direct2D 渲染

```cpp
// 初始化 D2D
VertexUI::Panel::InitGlobalD2D();

// 创建 D2D 面板
VertexUI::Panel::CreateD2DPanel(hWnd, [](HWND hWnd, ID2D1HwndRenderTarget* pRT) {
    // 使用 D2D 绘制
    VertexUI::Panel::D2DDrawRoundRect(pRT, x, y, width, height, color, radius);
    VertexUI::Panel::D2DDrawText(pRT, text, x, y, width, height, fontSize, color);
});
```

### 阴影效果

```cpp
// 简单阴影
VertexUI::Window::SimpleShadow::iDropShadow shadow;
shadow.SetSize(10);
shadow.SetColor(RGB(0, 0, 0));
shadow.Create(hdc, x, y, width, height, 5);

// 外部阴影窗口
VertexUI::Window::OuterShadow::DropShadow::Initialize(hInstance);
VertexUI::Window::OuterShadow::DropShadow windowShadow;
windowShadow.SetSize(15);
windowShadow.Create(hWnd);
```

### 高斯模糊

```cpp
// 区域模糊
VertexUI::Panel::AreaBlur(hdc, {x, y, width, height}, blurRadius, quality, useMultiThread);
```

## 📚 示例项目

完整的示例项目请参考 `Examples` 目录，包含：
- 基础窗口示例
- 控件使用示例  
- 动画效果示例
- 自定义绘制示例

## 🔧 构建说明

1. 在项目中包含 VinaUI 头文件
2. 链接所需库文件：
   ```cpp
   #pragma comment(lib, "d2d1.lib")
   #pragma comment(lib, "dwrite.lib") 
   #pragma comment(lib, "Msimg32.lib")
   ```
3. 在应用程序初始化时调用：
   ```cpp
   VertexUIInit;  // 初始化命名空间
   ```

## 📄 许可证

本项目采用 MIT 许可证，详见 LICENSE 文件。

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！请确保代码符合项目的编码规范。

## 📞 支持

- 提交 Issue: [GitHub Issues](https://github.com/oneachina/Better-VinaUI/issues)
- 文档: [Wiki](https://github.com/oneachina/Better-VinaUI/wiki)
- 邮箱: ruiruixi@hotmail.com

---

**VinaUI** - 让 Windows 桌面开发更简单、更美观！