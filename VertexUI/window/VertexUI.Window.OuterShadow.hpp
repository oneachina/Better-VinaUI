/**
 * OuterShadow 模块
 * 提供独立的阴影窗口，可以附加到任何窗口上
 * 支持窗口移动、大小调整的实时阴影更新
 * 使用独立的阴影窗口实现，不干扰主窗口绘制
 */

#pragma once
#include "VertexUI.Window.Utils.hpp"
#include <unordered_map>
#include <map>
#include <memory>

 /// @brief 最大值宏
#define win_max(a, b) (((a) > (b)) ? (a) : (b))

/// @brief 最小值宏  
#define win_min(a, b) (((a) < (b)) ? (a) : (b))

    namespace VertexUI
{
    namespace Window
    {
        namespace OuterShadow
        {
            // ===========================================================================
            // 前向声明和常量定义
            // ===========================================================================

            // 前向声明
            class DropShadow;

            // 阴影窗口类名
            constexpr const wchar_t* SHADOW_CLASS_NAME = L"LightFrame.UI.BackDropWnd.Shadow.Class";

            // 自定义消息定义
            constexpr UINT WM_SHADOW_DESTROY = 0xFF5;  ///< 阴影窗口销毁消息

            // 阴影状态标志
            enum ShadowStatus
            {
                SHADOW_ENABLED = 1,      ///< 阴影已启用
                SHADOW_VISIBLE = 1 << 1, ///< 阴影可见
                SHADOW_PARENT_VISIBLE = 1 << 2 ///< 父窗口可见
            };

            // ===========================================================================
            // DropShadow 类 - 外部阴影窗口管理器
            // ===========================================================================

            /// @brief 外部阴影窗口管理器
            /// 创建独立的阴影窗口并附加到目标窗口，支持实时更新
            class DropShadow
            {
            public:
                DropShadow();
                virtual ~DropShadow();

                /// @brief 初始化阴影系统（注册窗口类）
                /// @param hInstance 应用程序实例句柄
                /// @return 初始化是否成功
                static bool Initialize(HINSTANCE hInstance);

                /// @brief 为指定窗口创建阴影
                /// @param parentWindow 父窗口句柄
                void Create(HWND parentWindow);

                /// @brief 更新阴影显示
                /// @param parentWindow 父窗口句柄
                void Update(HWND parentWindow);

                // 阴影属性设置方法
                bool SetSize(int newSize = 0);
                bool SetSharpness(unsigned int newSharpness = 5);
                bool SetDarkness(unsigned int newDarkness = 200);
                bool SetPosition(int xOffset = 5, int yOffset = 5);
                bool SetColor(COLORREF newColor = 0);

                /// @brief 设置自定义区域（覆盖默认窗口区域）
                /// @param region 自定义区域句柄
                void SetCustomRegion(HRGN region) { m_customRegion = region; }

                /// @brief 获取阴影窗口句柄
                HWND GetShadowWindow() const { return m_shadowWindow; }

            protected:
                /// @brief 生成阴影位图数据
                /// @param shadowBits 阴影位图数据指针
                /// @param window 目标窗口句柄
                /// @param parentRect 父窗口矩形
                void MakeShadow(UINT32* shadowBits, HWND window, RECT* parentRect);

                /// @brief 显示/隐藏阴影窗口
                /// @param parentWindow 父窗口句柄
                void Show(HWND parentWindow);

            private:
                // 阴影窗口过程
                static LRESULT CALLBACK ShadowWindowProc(HWND window, UINT message,
                    WPARAM wParam, LPARAM lParam);

                // 宿主窗口子类化过程  
                static LRESULT CALLBACK ParentWindowProc(HWND window, UINT message,
                    WPARAM wParam, LPARAM lParam);

                // 静态成员变量
                static HINSTANCE s_appInstance;                                      ///< 应用程序实例
                static std::map<HWND, DropShadow*> s_activeShadows;                  ///< 活动阴影映射
                static std::unordered_map<HWND, WNDPROC> s_originalProcs;            ///< 原始窗口过程
                static std::unordered_map<HWND, HWND> s_shadowWindows;               ///< 阴影窗口映射

                // 实例成员变量
                HWND m_shadowWindow;          ///< 阴影窗口句柄
                HWND m_parentWindow;          ///< 父窗口句柄
                WNDPROC m_originalParentProc; ///< 原始窗口过程
                HRGN m_customRegion;          ///< 自定义区域

                // 阴影属性
                unsigned char m_darkness;     ///< 阴影暗度 (0-255)
                unsigned char m_sharpness;    ///< 阴影锐度
                signed char m_size;           ///< 阴影大小
                signed char m_xOffset;        ///< X轴偏移
                signed char m_yOffset;        ///< Y轴偏移
                COLORREF m_color;             ///< 阴影颜色

                // 状态和缓存
                BYTE m_status;                ///< 阴影状态标志
                LPARAM m_windowSize;          ///< 窗口大小缓存
                bool m_needsUpdate;           ///< 需要更新标志

                // 使用预乘颜色
                inline DWORD PreMultiply(COLORREF cl, unsigned char alpha)
                {
                    return Utils::PreMultiplyColor(cl, alpha);
                }

                // 禁止拷贝
                DropShadow(const DropShadow&) = delete;
                DropShadow& operator=(const DropShadow&) = delete;
            };

            // ===========================================================================
            // 静态成员初始化
            // ===========================================================================

            inline HINSTANCE DropShadow::s_appInstance = nullptr;
            inline std::map<HWND, DropShadow*> DropShadow::s_activeShadows;
            inline std::unordered_map<HWND, WNDPROC> DropShadow::s_originalProcs;
            inline std::unordered_map<HWND, HWND> DropShadow::s_shadowWindows;

            // ===========================================================================
            // DropShadow 实现
            // ===========================================================================

            /// @brief 构造函数
            inline DropShadow::DropShadow()
                : m_shadowWindow(nullptr)
                , m_parentWindow(nullptr)
                , m_originalParentProc(nullptr)
                , m_customRegion(nullptr)
                , m_darkness(150)
                , m_sharpness(5)
                , m_size(50)
                , m_xOffset(5)
                , m_yOffset(5)
                , m_color(RGB(0, 0, 0))
                , m_status(0)
                , m_windowSize(0)
                , m_needsUpdate(false)
            {
            }

            /// @brief 析构函数
            inline DropShadow::~DropShadow()
            {
                // 清理自定义区域
                if (m_customRegion != nullptr)
                {
                    DeleteObject(m_customRegion);
                    m_customRegion = nullptr;
                }

                // 从活动阴影映射中移除
                if (m_parentWindow != nullptr)
                {
                    auto it = s_activeShadows.find(m_parentWindow);
                    if (it != s_activeShadows.end())
                    {
                        s_activeShadows.erase(it);
                    }
                }
            }

            /// @brief 初始化阴影系统
            inline bool DropShadow::Initialize(HINSTANCE hInstance)
            {
                s_appInstance = hInstance;

                WNDCLASSEX wcex = { 0 };
                wcex.cbSize = sizeof(WNDCLASSEX);
                wcex.style = CS_HREDRAW | CS_VREDRAW;
                wcex.lpfnWndProc = ShadowWindowProc;
                wcex.cbClsExtra = 0;
                wcex.cbWndExtra = 0;
                wcex.hInstance = hInstance;
                wcex.hIcon = NULL;
                wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.lpszMenuName = NULL;
                wcex.lpszClassName = SHADOW_CLASS_NAME;
                wcex.hIconSm = NULL;

                return RegisterClassEx(&wcex) != 0;
            }

            /// @brief 为指定窗口创建阴影
            inline void DropShadow::Create(HWND parentWindow)
            {
                if (parentWindow == nullptr) return;

                m_parentWindow = parentWindow;

                // 创建阴影窗口
                m_shadowWindow = CreateWindowEx(
                    WS_EX_LAYERED | WS_EX_TRANSPARENT,
                    SHADOW_CLASS_NAME,
                    NULL,
                    WS_POPUPWINDOW,
                    CW_USEDEFAULT, 0, 0, 0,
                    parentWindow, NULL, s_appInstance, NULL
                );

                if (m_shadowWindow == nullptr)
                {
                    Utils::CheckGDIFrror(L"CreateWindowEx for shadow window");
                    return;
                }

                m_status = SHADOW_ENABLED;

                // 显示阴影
                Show(parentWindow);

                // 子类化父窗口以捕获移动和大小调整消息
                WNDPROC originalProc = reinterpret_cast<WNDPROC>(
                    SetWindowLongPtr(parentWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(ParentWindowProc))
                    );

                if (originalProc != nullptr)
                {
                    s_originalProcs[parentWindow] = originalProc;
                    s_shadowWindows[parentWindow] = m_shadowWindow;
                    s_activeShadows[parentWindow] = this;
                }

                Utils::DebugOutput(L"Shadow created for window: 0x%p\n", parentWindow);
            }

            /// @brief 设置阴影大小
            inline bool DropShadow::SetSize(int newSize)
            {
                if (newSize > 40 || newSize < -20)
                    return false;

                m_size = static_cast<signed char>(newSize);
                if (m_status & SHADOW_VISIBLE)
                    Update(GetParent(m_shadowWindow));
                return true;
            }

            /// @brief 设置阴影锐度
            inline bool DropShadow::SetSharpness(unsigned int newSharpness)
            {
                if (newSharpness > 80)
                    return false;

                m_sharpness = static_cast<unsigned char>(newSharpness);
                if (m_status & SHADOW_VISIBLE)
                    Update(GetParent(m_shadowWindow));
                return true;
            }

            /// @brief 设置阴影暗度
            inline bool DropShadow::SetDarkness(unsigned int newDarkness)
            {
                if (newDarkness > 255)
                    return false;

                m_darkness = static_cast<unsigned char>(newDarkness);
                if (m_status & SHADOW_VISIBLE)
                    Update(GetParent(m_shadowWindow));
                return true;
            }

            /// @brief 设置阴影位置偏移
            inline bool DropShadow::SetPosition(int xOffset, int yOffset)
            {
                if (xOffset > 20 || xOffset < -20 ||
                    yOffset > 20 || yOffset < -20)
                    return false;

                m_xOffset = static_cast<signed char>(xOffset);
                m_yOffset = static_cast<signed char>(yOffset);
                if (m_status & SHADOW_VISIBLE)
                    Update(GetParent(m_shadowWindow));
                return true;
            }

            /// @brief 设置阴影颜色
            inline bool DropShadow::SetColor(COLORREF newColor)
            {
                m_color = newColor;
                if (m_status & SHADOW_VISIBLE)
                    Update(GetParent(m_shadowWindow));
                return true;
            }

            /// @brief 更新阴影显示
            inline void DropShadow::Update(HWND parentWindow)
            {
                if (parentWindow == nullptr || m_shadowWindow == nullptr) return;

                RECT windowRect;
                if (!GetWindowRect(parentWindow, &windowRect))
                {
                    Utils::CheckGDIFrror(L"GetWindowRect in Update");
                    return;
                }

                int shadowWidth = (windowRect.right - windowRect.left) + m_size * 2;
                int shadowHeight = (windowRect.bottom - windowRect.top) + m_size * 2;

                // 创建位图信息
                BITMAPINFO bmi = { 0 };
                bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                bmi.bmiHeader.biWidth = shadowWidth;
                bmi.bmiHeader.biHeight = shadowHeight;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biBitCount = 32;
                bmi.bmiHeader.biCompression = BI_RGB;
                bmi.bmiHeader.biSizeImage = shadowWidth * shadowHeight * 4;

                BYTE* bitmapBits = nullptr;
                HBITMAP bitmap = Utils::CreateARGBBitmap(nullptr, shadowWidth, shadowHeight, &bitmapBits);

                if (!bitmap || !bitmapBits)
                {
                    Utils::CheckGDIFrror(L"CreateARGBBitmap in Update");
                    return;
                }

                // 清空位图数据
                ZeroMemory(bitmapBits, bmi.bmiHeader.biSizeImage);

                // 生成阴影数据
                MakeShadow(reinterpret_cast<UINT32*>(bitmapBits), parentWindow, &windowRect);

                // 创建内存DC
                HDC memDC = CreateCompatibleDC(nullptr);
                if (!memDC)
                {
                    Utils::SafeDeleteObject(bitmap);
                    Utils::CheckGDIFrror(L"CreateCompatibleDC in Update");
                    return;
                }

                HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(memDC, bitmap));

                // 设置分层窗口参数
                POINT dstPoint = { windowRect.left + m_xOffset - m_size, windowRect.top + m_yOffset - m_size };
                POINT srcPoint = { 0, 0 };
                SIZE size = { shadowWidth, shadowHeight };
                BLENDFUNCTION blendFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

                // 移动阴影窗口到正确位置
                MoveWindow(m_shadowWindow, dstPoint.x, dstPoint.y, shadowWidth, shadowHeight, FALSE);

                // 更新分层窗口
                BOOL result = UpdateLayeredWindow(
                    m_shadowWindow,
                    nullptr,
                    &dstPoint,
                    &size,
                    memDC,
                    &srcPoint,
                    0,
                    &blendFunction,
                    ULW_ALPHA
                );

                if (!result)
                {
                    Utils::CheckGDIFrror(L"UpdateLayeredWindow in Update");
                }

                // 清理资源
                SelectObject(memDC, oldBitmap);
                Utils::SafeDeleteObject(bitmap);
                Utils::SafeReleaseDC(memDC);
            }

            /// @brief 显示/隐藏阴影窗口
            inline void DropShadow::Show(HWND parentWindow)
            {
                m_status &= SHADOW_ENABLED;

                if ((m_status & SHADOW_ENABLED) && parentWindow != nullptr)
                {
                    LONG parentStyle = GetWindowLong(parentWindow, GWL_STYLE);

                    if (WS_VISIBLE & parentStyle)
                    {
                        m_status |= SHADOW_PARENT_VISIBLE;

                        if (!((WS_MAXIMIZE | WS_MINIMIZE) & parentStyle))
                            m_status |= SHADOW_VISIBLE;
                    }
                }

                if (m_status & SHADOW_VISIBLE)
                {
                    ShowWindow(m_shadowWindow, SW_SHOWNA);
                    Update(parentWindow);
                }
                else
                {
                    ShowWindow(m_shadowWindow, SW_HIDE);
                }
            }

            /// @brief 阴影窗口过程
            inline LRESULT CALLBACK DropShadow::ShadowWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
            {
                // 处理自定义销毁消息
                if (message == WM_SHADOW_DESTROY)
                {
                    DestroyWindow(window);
                    return 0;
                }

                // 其他消息交给默认处理
                return DefWindowProc(window, message, wParam, lParam);
            }

            /// @brief 父窗口子类化过程
            inline LRESULT CALLBACK DropShadow::ParentWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
            {
                // 查找对应的阴影窗口
                auto shadowIt = s_shadowWindows.find(window);
                auto procIt = s_originalProcs.find(window);
                auto shadowObjIt = s_activeShadows.find(window);

                if (shadowIt == s_shadowWindows.end() || procIt == s_originalProcs.end())
                {
                    return DefWindowProc(window, message, wParam, lParam);
                }

                HWND shadowWindow = shadowIt->second;
                WNDPROC originalProc = procIt->second;

                switch (message)
                {
                case WM_MOVE:
                {
                    // 父窗口移动时更新阴影位置
                    RECT parentRect;
                    if (GetWindowRect(window, &parentRect))
                    {
                        RECT clientRect;
                        GetClientRect(window, &clientRect);
                        RECT shadowRect;
                        GetClientRect(shadowWindow, &shadowRect);

                        int offset = (shadowRect.right - clientRect.right) / 2;
                        SetWindowPos(
                            shadowWindow,
                            0,
                            parentRect.left - offset,
                            parentRect.top - offset,
                            0, 0,
                            SWP_NOSIZE | SWP_NOACTIVATE
                        );
                    }
                    break;
                }

                case WM_SIZE:
                {
                    // 父窗口大小改变时更新阴影大小
                    RECT parentRect;
                    if (GetWindowRect(window, &parentRect))
                    {
                        RECT clientRect;
                        GetClientRect(window, &clientRect);
                        RECT shadowRect;
                        GetClientRect(shadowWindow, &shadowRect);

                        int offset = shadowRect.right - clientRect.right;
                        SetWindowPos(
                            shadowWindow,
                            0, 0, 0,
                            clientRect.right + offset * 2,
                            clientRect.bottom + offset * 2,
                            SWP_NOMOVE | SWP_NOACTIVATE
                        );

                        // 如果有活动的阴影对象，强制更新
                        if (shadowObjIt != s_activeShadows.end())
                        {
                            shadowObjIt->second->Update(window);
                        }
                    }
                    break;
                }

                case WM_DESTROY:
                case WM_CLOSE:
                case WM_QUIT:
                {
                    // 父窗口销毁时隐藏并销毁阴影窗口
                    ShowWindow(shadowWindow, SW_HIDE);
                    PostMessage(shadowWindow, WM_SHADOW_DESTROY, 0, 0);

                    // 清理映射
                    s_shadowWindows.erase(window);
                    s_originalProcs.erase(window);
                    s_activeShadows.erase(window);

                    break;
                }

                case WM_SHOWWINDOW:
                {
                    // 父窗口显示状态改变时更新阴影
                    if (shadowObjIt != s_activeShadows.end())
                    {
                        shadowObjIt->second->Show(window);
                    }
                    break;
                }
                }

                // 调用原始窗口过程
                return CallWindowProc(originalProc, window, message, wParam, lParam);
            }

            /// @brief 生成阴影位图数据（核心算法）
            inline void DropShadow::MakeShadow(UINT32* shadowBits, HWND window, RECT* parentRect)
            {
                // 创建窗口区域
                HRGN windowRegion = CreateRectRgn(0, 0,
                    parentRect->right - parentRect->left,
                    parentRect->bottom - parentRect->top);

                if (m_customRegion != nullptr)
                {
                    // 使用自定义区域
                    DeleteObject(windowRegion);
                    windowRegion = m_customRegion;
                }
                else
                {
                    // 获取窗口区域
                    GetWindowRgn(window, windowRegion);
                }

                if (!windowRegion)
                {
                    Utils::CheckGDIFrror(L"Create window region in MakeShadow");
                    return;
                }

                // 确定每个水平扫描线的起点和终点
                SIZE parentSize = { parentRect->right - parentRect->left, parentRect->bottom - parentRect->top };
                SIZE shadowSize = { parentSize.cx + 2 * m_size, parentSize.cy + 2 * m_size };

                // 在ptAnchors中额外使用2行（设置为空）用于膨胀
                int anchorCount = win_max(parentSize.cy, shadowSize.cy);  // 锚点对的数量

                // 使用unique_ptr自动管理内存
                std::unique_ptr<int[][2]> anchors(new int[anchorCount + 2][2]);
                std::unique_ptr<int[][2]> originalAnchors(new int[parentSize.cy][2]);  // 锚点，在腐蚀期间不会修改

                // 初始化边界锚点
                anchors[0][0] = parentSize.cx;
                anchors[0][1] = 0;
                anchors[anchorCount + 1][0] = parentSize.cx;
                anchors[anchorCount + 1][1] = 0;

                if (m_size > 0)
                {
                    // 将父窗口锚点放在中心
                    for (int i = 0; i < m_size; i++)
                    {
                        anchors[i + 1][0] = parentSize.cx;
                        anchors[i + 1][1] = 0;
                        anchors[shadowSize.cy - i][0] = parentSize.cx;
                        anchors[shadowSize.cy - i][1] = 0;
                    }
                    // 调整指针位置 - 使用索引偏移
                    // anchors += m_size;
                }

                // 计算每个扫描线的锚点
                int anchorOffset = (m_size > 0) ? m_size : 0;
                for (int i = 0; i < parentSize.cy; i++)
                {
                    // 查找起点
                    int j;
                    for (j = 0; j < parentSize.cx; j++)
                    {
                        if (PtInRegion(windowRegion, j, i))
                        {
                            anchors[i + 1 + anchorOffset][0] = j + m_size;
                            originalAnchors[i][0] = j;
                            break;
                        }
                    }

                    if (j >= parentSize.cx)  // 未找到起点
                    {
                        anchors[i + 1 + anchorOffset][0] = parentSize.cx;
                        originalAnchors[i][1] = 0;
                        anchors[i + 1 + anchorOffset][0] = parentSize.cx;
                        originalAnchors[i][1] = 0;
                    }
                    else
                    {
                        // 查找终点
                        for (j = parentSize.cx - 1; j >= anchors[i + 1 + anchorOffset][0]; j--)
                        {
                            if (PtInRegion(windowRegion, j, i))
                            {
                                anchors[i + 1 + anchorOffset][1] = j + 1 + m_size;
                                originalAnchors[i][1] = j + 1;
                                break;
                            }
                        }
                    }
                }

                // 形态学腐蚀
                std::unique_ptr<int[][2]> tempAnchors(new int[anchorCount + 2][2]);  // 存储腐蚀结果

                // 第一行和最后一行应为空
                tempAnchors[0][0] = parentSize.cx;
                tempAnchors[0][1] = 0;
                tempAnchors[anchorCount + 1][0] = parentSize.cx;
                tempAnchors[anchorCount + 1][1] = 0;

                int erosionCount = 0;
                for (int i = 0; i < m_sharpness - m_size; i++)
                {
                    erosionCount++;
                    for (int j = 1; j < anchorCount + 1; j++)
                    {
                        tempAnchors[j][0] = win_max(anchors[j - 1][0],
                            win_max(anchors[j][0], anchors[j + 1][0])) + 1;
                        tempAnchors[j][1] = win_min(anchors[j - 1][1],
                            win_min(anchors[j][1], anchors[j + 1][1])) - 1;
                    }
                    // 交换anchors和tempAnchors
                    std::swap(anchors, tempAnchors);
                }

                // 形态学膨胀
                // 现在ptAnchors中的坐标与阴影窗口中的坐标相同

                // 生成卷积核
                int kernelSize = (m_size > m_sharpness) ? m_size : m_sharpness;
                int centerSize = (m_size > m_sharpness) ? (m_size - m_sharpness) : 0;
                int kernelDimensions = (2 * kernelSize + 1) * (2 * kernelSize + 1);

                std::unique_ptr<UINT32[]> kernel(new UINT32[kernelDimensions]);
                UINT32* kernelPtr = kernel.get();

                for (int i = 0; i <= 2 * kernelSize; i++)
                {
                    for (int j = 0; j <= 2 * kernelSize; j++)
                    {
                        double distance = sqrt((i - kernelSize) * (i - kernelSize) +
                            (j - kernelSize) * static_cast<double>(j - kernelSize));

                        if (distance < centerSize)
                        {
                            *kernelPtr = m_darkness << 24 | PreMultiply(m_color, m_darkness);
                        }
                        else if (distance <= kernelSize)
                        {
                            UINT32 factor = static_cast<UINT32>((1 - (distance - centerSize) / (m_sharpness + 1)) * m_darkness);
                            *kernelPtr = factor << 24 | PreMultiply(m_color, factor);
                        }
                        else
                        {
                            *kernelPtr = 0;
                        }
                        kernelPtr++;
                    }
                }

                // 生成模糊边界
                for (int i = kernelSize; i < shadowSize.cy - kernelSize; i++)
                {
                    int j;
                    if (anchors[i][0] < anchors[i][1])
                    {
                        // 行起始部分
                        for (j = anchors[i][0];
                            j < win_min(win_max(anchors[i - 1][0], anchors[i + 1][0]) + 1, anchors[i][1]);
                            j++)
                        {
                            for (int k = 0; k <= 2 * kernelSize; k++)
                            {
                                UINT32* pixel = shadowBits +
                                    (shadowSize.cy - i - 1 + kernelSize - k) * shadowSize.cx + j - kernelSize;
                                UINT32* kernelPixel = kernel.get() + k * (2 * kernelSize + 1);

                                for (int l = 0; l <= 2 * kernelSize; l++)
                                {
                                    if (*pixel < *kernelPixel)
                                        *pixel = *kernelPixel;
                                    pixel++;
                                    kernelPixel++;
                                }
                            }
                        }

                        // 行结束部分
                        for (j = win_max(j, win_min(anchors[i - 1][1], anchors[i + 1][1]) - 1);
                            j < anchors[i][1];
                            j++)
                        {
                            for (int k = 0; k <= 2 * kernelSize; k++)
                            {
                                UINT32* pixel = shadowBits +
                                    (shadowSize.cy - i - 1 + kernelSize - k) * shadowSize.cx + j - kernelSize;
                                UINT32* kernelPixel = kernel.get() + k * (2 * kernelSize + 1);

                                for (int l = 0; l <= 2 * kernelSize; l++)
                                {
                                    if (*pixel < *kernelPixel)
                                        *pixel = *kernelPixel;
                                    pixel++;
                                    kernelPixel++;
                                }
                            }
                        }
                    }
                }

                // 擦除不需要的部分并补充缺失的部分
                UINT32 centerColor = m_darkness << 24 | PreMultiply(m_color, m_darkness);
                for (int i = win_min(kernelSize, win_max(m_size - m_yOffset, 0));
                    i < win_max(shadowSize.cy - kernelSize,
                        win_min(parentSize.cy + m_size - m_yOffset, parentSize.cy + 2 * m_size));
                    i++)
                {
                    UINT32* line = shadowBits + (shadowSize.cy - i - 1) * shadowSize.cx;

                    if (i - m_size + m_yOffset < 0 || i - m_size + m_yOffset >= parentSize.cy)  // 行未被父窗口覆盖
                    {
                        for (int j = anchors[i][0]; j < anchors[i][1]; j++)
                        {
                            *(line + j) = centerColor;
                        }
                    }
                    else
                    {
                        // 左侧阴影
                        for (int j = anchors[i][0];
                            j < win_min(originalAnchors[i - m_size + m_yOffset][0] + m_size - m_xOffset, anchors[i][1]);
                            j++)
                            *(line + j) = centerColor;

                        // 中间透明（窗口区域）
                        for (int j = win_max(originalAnchors[i - m_size + m_yOffset][0] + m_size - m_xOffset, 0);
                            j < win_min(originalAnchors[i - m_size + m_yOffset][1] + m_size - m_xOffset, shadowSize.cx);
                            j++)
                            *(line + j) = 0;

                        // 右侧阴影
                        for (int j = win_max(originalAnchors[i - m_size + m_yOffset][1] + m_size - m_xOffset, anchors[i][0]);
                            j < anchors[i][1];
                            j++)
                            *(line + j) = centerColor;
                    }
                }

                // 清理资源
                if (m_customRegion == nullptr)  // 只有非自定义区域才需要删除
                {
                    Utils::SafeDeleteObject(windowRegion);
                }

                // unique_ptr会自动释放内存，无需手动delete[]
            }

        } // namespace OuterShadow
    } // namespace Window
} // namespace VertexUI