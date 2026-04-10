# Welcome to VinaUI

VinaUI is a lightweight, high-performance, and flexible C++ UI framework built on Direct2D. It aims to provide near-native experience with a straightforward development model.

## Features

- Lightweight and efficient wrappers over native APIs.
- GPU-accelerated rendering with Direct2D.
- Modern built-in controls: Button, Slider, Switch, TextBox, Edit, Card.
- Simple Bezier-based animation APIs.
- DPI-aware rendering for high-resolution displays.

## Project Structure

```text
Better-VinaUI/
├─ apps/
│  └─ vina-demo/
│     ├─ src/                 # demo app entry
│     └─ resources/           # rc / resource.h
├─ framework/
│  ├─ Vina/                   # Vina wrappers (window, controls, events)
│  └─ VertexUI/               # low-level rendering and base capabilities
├─ third_party/
│  └─ tsl/                    # third-party containers
├─ assets/
│  ├─ icons/
│  └─ fonts/
└─ CMakeLists.txt
```

## Build (CMake)

This repository now uses CMake as the primary build system.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Default target:

- `vina_demo` (Win32 GUI demo)

Optional target (disabled by default):

```bash
cmake -S . -B build -DBUILD_VUI_PARSER_CLI=ON
cmake --build build --config Release
```

## SDK Install

Install VinaUI as a CMake package:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cmake --install build --config Release --prefix ./sdk-install
```

Installed package layout:

- `sdk-install/include/` (VinaUI headers)
- `sdk-install/share/vinaui/assets/` (icons/fonts)
- `sdk-install/lib/cmake/VinaUI/` (CMake package files)

Consume from an external project:

```cmake
find_package(VinaUI CONFIG REQUIRED PATHS "path/to/sdk-install/lib/cmake/VinaUI")
target_link_libraries(your_app PRIVATE VinaUI::vina_sdk)
```

Icon font policy:

- VinaUI default icons now use system-available symbols (no bundled FontAwesome required).
- If your app needs a custom icon font, register it explicitly:

```C++
MainWindow->RegisterFontFromFile(L"./fonts/YourIconFont.ttf");
MainWindow->SetDefaultIconFontFamily(L"Your Icon Font Family");
```

## Quick Start

### 1. Create Main Window

```C++
#include <VinaWindow.hpp>

std::shared_ptr<VinaWindow> MainWindow = std::make_shared<VinaWindow>();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    InitGlobalD2D();
    VuiColorSystemInit();
    gScale = GetScreenScale();

    MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"MyApp", L"My VinaUI App");
    MainWindow->SetOutFrame(VinaWindow::Client);

    MainWindow->OnCreateCmd = [] {
        CenterWindow(MainWindow->GetHandle());
        MainWindow->InitAnimation();
        MainWindow->StartAnimationSystem();
    };

    return MainWindow->RunFull();
}
```

### 2. Create a Panel

```cpp
struct AppContext {
    std::shared_ptr<VinaButton> btn = std::make_shared<VinaButton>();
    std::shared_ptr<VinaEdit> edt = std::make_shared<VinaEdit>();
};

auto ctx = std::make_shared<AppContext>();

MainWindow->CreatePanel([ctx](HWND hWnd, ID2D1HwndRenderTarget* hrt) {
    RECT rc;
    GetClientRect(hWnd, &rc);
    D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_DARKNIGHT);
    MainWindow->GetPanel()->Set(hWnd, hrt);
});
```

### 3. Add Controls

```cpp
ctx->btn->Set(40, 60, 140, 40, L"Click", [] {
    MessageBox(0, L"Hello VinaUI!", L"Tips", 0);
    return 0;
});
MainWindow->GetPanel()->Add(ctx->btn);
```

### 4. Bezier Animation

```cpp
MainWindow->AnimateVariableWithBezier(
    hWnd,
    item.yOffset,
    18.0f,
    0.0f,
    0.4,
    0.25, 0.1, 0.25, 1.0
);
```

## Credits

- @Haceau-Zoac (vui.parser)
- @KitraMGP (spec suggestions)
- Thanks to all VinaUI contributors.
