# VinaUI - Modern Windows UI Framework

![Version](https://img.shields.io/badge/version-2.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C++-yellow.svg)

VinaUI is a modern C++-based Windows UI framework that provides rich UI components, animation effects, and custom drawing capabilities to help developers quickly build beautiful desktop applications.

**[中文文档](README_ZH.md)** | **English Documentation**

## ✨ Features

### 🎨 Rich Visual Effects
- **Advanced Shadow System** - Supports simple shadows and external shadow windows
- **Gaussian Blur** - High-performance area blur effects
- **Alpha Blending** - Complete transparency support
- **Gradient Drawing** - Linear gradients and color transitions
- **Rounded Rectangles** - UI elements with customizable corner radii

### 🎯 Flexible Layout System
- **Multiple Layout Modes** - Free, Left, Pushing, Flex
- **Responsive Design** - Automatically adapts to window size changes
- **Panel Management** - Multi-panel switching and state management
- **Control Containers** - Flexible control organization and event handling

### ⚡ High-Performance Rendering
- **Dual Rendering Backends** - Supports both GDI and Direct2D
- **Memory Optimization** - Smart caching and resource management
- **GPU Acceleration** - Leverages hardware acceleration for better performance
- **Asynchronous Drawing** - Non-blocking UI updates

### 🔧 Easy-to-Use API
- **Declarative Programming** - Simple control creation syntax
- **Event-Driven** - Unified mouse and keyboard event handling
- **Type Safety** - Templated control system
- **Modular Design** - Import only the modules you need

## 🚀 Quick Start

### Requirements
- Windows 7 or later
- Visual Studio 2015 or later
- C++11 compatible compiler

### Basic Usage

```cpp
#include "VertexUI.min.h"

VertexUIInit;  // Initialize namespaces

// Create window with VertexUI styling
HWND hWnd = CreateWindow(...);

// Draw UI in WM_PAINT message
case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    
    VertexUI::Panel::CreatePanel(hWnd, hdc, [](HWND hWnd, HDC hdc) {
        // Draw background
        VertexUI::Panel::CreateFillArea(hWnd, hdc, VERTEXUICOLOR_MIDNIGHT);
        
        // Create rounded button
        VertexUI::Panel::CreateRoundButtonEx(hdc, 50, 50, 200, 40, 8, 
            L"Click Me", 16, VERTEXUICOLOR_LAVENDER);
    });
    
    EndPaint(hWnd, &ps);
    break;
}
```

### Using Control System

```cpp
// Create control panel
VertexUI::VertexUIPanel panel;
panel.Set(hWnd, hdc);

// Add button control
VertexUI::VertexUIColorInfo btnStyle = { VERTEXUICOLOR_LAVENDER, VERTEXUICOLOR_WHITE };
VertexUIControl button;
button.CreateCtl(L"Button", 100, 100, 120, 40, []() {
    MessageBox(NULL, L"Button clicked!", L"Info", MB_OK);
}, L"My Button", btnStyle);

panel.Add(button);
```

## 📁 Project Structure

```
VertexUI/
├── VertexUI.min.h              # Main entry point
├── VertexUI.Colors.h           # Color system and theme definitions
├── VertexUI.ClickArea.h        # Click areas and event handling
├── VertexUI.Control.hpp        # Control base classes and layout system
├── VertexUI.Panel.h            # Panel drawing and rendering engine
├── VertexUI.Animation.hpp      # Animation system
├── VertexUI.Window.hpp         # Window management and shadow effects
├── VertexUI.Window.Utils.hpp   # Window utility functions
├── VertexUI.Window.SimpleShadow.hpp    # Simple shadows
└── VertexUI.Window.OuterShadow.hpp     # External shadows
```

## 🎨 Color System

VertexUI provides a complete color management system:

```cpp
// Using predefined colors
CreateRect(hdc, x, y, width, height, VERTEXUICOLOR_MIDNIGHT);
CreateRect(hdc, x, y, width, height, VERTEXUICOLOR_LAVENDER);

// Color utility functions
COLORREF brighter = VertexUI::Utils::AdjustColorBrightness(color, 1.2f);
COLORREF interpolated = VertexUI::Utils::InterpolateColor(color1, color2, 0.5f);
```

### Predefined Color Themes
- `VERTEXUICOLOR_MIDNIGHT` - Midnight blue
- `VERTEXUICOLOR_LAVENDER` - Lavender purple  
- `VERTEXUICOLOR_GREENSEA` - Green sea
- `VERTEXUICOLOR_WHITE` - Pure white
- `VERTEXUICOLOR_DARKNIGHT` - Dark night

## 🔄 Animation System

```cpp
// Fade in animation
VertexUI::Panel::FadeInAnimation(hWnd);

// Easing animations
VertexUI::Panel::WindowEaseIn(hWnd);

// Custom animations
VertexUI::Panel::CtlMoveInAnimation(hWnd, rc, animatedValue, moveDistance);
```

## 🖱️ Event Handling

```cpp
// Mouse event handling
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

## 🛠️ Advanced Features

### Using Direct2D Rendering

```cpp
// Initialize D2D
VertexUI::Panel::InitGlobalD2D();

// Create D2D panel
VertexUI::Panel::CreateD2DPanel(hWnd, [](HWND hWnd, ID2D1HwndRenderTarget* pRT) {
    // Draw with D2D
    VertexUI::Panel::D2DDrawRoundRect(pRT, x, y, width, height, color, radius);
    VertexUI::Panel::D2DDrawText(pRT, text, x, y, width, height, fontSize, color);
});
```

### Shadow Effects

```cpp
// Simple shadow
VertexUI::Window::SimpleShadow::iDropShadow shadow;
shadow.SetSize(10);
shadow.SetColor(RGB(0, 0, 0));
shadow.Create(hdc, x, y, width, height, 5);

// External shadow window
VertexUI::Window::OuterShadow::DropShadow::Initialize(hInstance);
VertexUI::Window::OuterShadow::DropShadow windowShadow;
windowShadow.SetSize(15);
windowShadow.Create(hWnd);
```

### Gaussian Blur

```cpp
// Area blur
VertexUI::Panel::AreaBlur(hdc, {x, y, width, height}, blurRadius, quality, useMultiThread);
```

## 📚 Examples

Complete example projects are available in the `Examples` directory, including:
- Basic window examples
- Control usage examples  
- Animation effect examples
- Custom drawing examples

## 🔧 Building Instructions

1. Include VertexUI headers in your project
2. Link required libraries:
   ```cpp
   #pragma comment(lib, "d2d1.lib")
   #pragma comment(lib, "dwrite.lib") 
   #pragma comment(lib, "Msimg32.lib")
   ```
3. Call during application initialization:
   ```cpp
   VertexUIInit;  // Initialize namespaces
   ```

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

Issues and Pull Requests are welcome! Please ensure your code follows the project's coding standards.

## 📞 Support

- Submit Issue: [GitHub Issues](https://github.com/oneachina/Better-VinaUI/issues)
- Documentation: [Wiki](https://github.com/oneachina/Better-VinaUI/wiki)
- Email: ruiruixi@hotmail.com

---

**VinaUI** - Making Windows desktop development simpler and more beautiful!

**[View Chinese Documentation](README_ZH.md)**