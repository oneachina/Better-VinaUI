# 欢迎探索 VinaUI！

这是一个基于 Direct2D 构建的轻量级、高性能、高灵活性的 C++ 界面框架。VinaUI 旨在为开发者提供近似原生的体验同时，创造简单、轻松的开发体验，为创造力的释放搭建空间。

## 核心特性

- 轻量高效：VinaUI 在原生库的基础上进行高效灵活的封装，可以轻松生成美观且小体积的应用程序。
- Direct2D 渲染：使用原生 API 的 GPU 加速渲染。
- 现代控件库：内置 Button、Slider、Switch、TextBox、Edit、Card 等组件。
- 动画接口：仅需一行代码即可调用基于 Bezier 曲线的并行、高性能动画。
- DPI 自适应：原生支持屏幕缩放，解决高分屏模糊问题。

## 项目结构（重构后）

```text
Better-VinaUI/
├─ apps/
│  └─ vina-demo/
│     ├─ src/                 # 示例应用入口
│     └─ resources/           # rc / resource.h
├─ framework/
│  ├─ Vina/                   # Vina 封装层（窗口、控件、事件）
│  └─ VertexUI/               # 底层绘制与基础能力
├─ third_party/
│  └─ tsl/                    # 第三方容器库
├─ assets/
│  ├─ icons/
│  └─ fonts/
└─ CMakeLists.txt
```

## 构建方式（CMake）

仅保留 CMake 构建流程，不再依赖 Visual Studio `.sln/.vcxproj`。

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

默认生成目标：

- `vina_demo`：主界面示例（Win32 GUI）

可选目标（默认关闭）：

```bash
cmake -S . -B build -DBUILD_VUI_PARSER_CLI=ON
cmake --build build --config Release
```

## 快速入门

### 1. 创建主窗口

VinaUI 使用 `VinaWindow` 对象管理窗口生命周期。你可以直接实例化并设置初始参数。

```cpp
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

### 2. 创建绘图面板（CreatePanel）

VinaUI 的核心逻辑在于 Panel。它接受一个 Lambda 表达式，当窗口重绘时会被调用。

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

### 3. 添加控件

所有控件都通过 `MainWindow->GetPanel()->Add()` 加入渲染队列。

```cpp
ctx->btn->Set(40, 60, 140, 40, L"Click", [] {
    MessageBox(0, L"Hello VinaUI!", L"Tips", 0);
    return 0;
});
MainWindow->GetPanel()->Add(ctx->btn);
```

### 4. 使用 Bezier 动画

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

## 致谢

- @Haceau-Zoac（vui.parser）
- @KitraMGP（规范性提议）
- Thanks to all VinaUI contributors.
