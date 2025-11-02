/**
 * VertexUI 窗口工具函数
 * 提供窗口操作、数学计算等辅助功能
 */

#pragma once
#include <Windows.h>
#include <algorithm>

    namespace VertexUI
{
    namespace Window
    {
        namespace Utils
        {
            // ===========================================================================
            // 数学辅助函数和宏
            // ===========================================================================

            /// @brief 最大值宏
#define win_max(a, b) (((a) > (b)) ? (a) : (b))

/// @brief 最小值宏  
#define win_min(a, b) (((a) < (b)) ? (a) : (b))

/// @brief 安全删除指针
            template<typename T>
            inline void SafeDelete(T*& ptr)
            {
                if (ptr != nullptr)
                {
                    delete ptr;
                    ptr = nullptr;
                }
            }

            /// @brief 安全删除数组
            template<typename T>
            inline void SafeDeleteArray(T*& ptr)
            {
                if (ptr != nullptr)
                {
                    delete[] ptr;
                    ptr = nullptr;
                }
            }

            /// @brief 安全释放GDI对象
            template<typename T>
            inline void SafeDeleteObject(T object)
            {
                if (object != nullptr && object != INVALID_HANDLE_VALUE)
                {
                    DeleteObject(object);
                }
            }

            /// @brief 安全释放设备上下文
            inline void SafeReleaseDC(HDC hdc)
            {
                if (hdc != nullptr)
                {
                    DeleteDC(hdc);
                }
            }

            // ===========================================================================
            // 窗口操作函数
            // ===========================================================================

            /// @brief 将窗口居中显示
            /// @param hWnd 要居中的窗口句柄
            inline void CenterWindow(HWND hWnd)
            {
                RECT rect;

                // 获取屏幕尺寸
                int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                int screenHeight = GetSystemMetrics(SM_CYSCREEN);

                // 获取窗口尺寸
                GetWindowRect(hWnd, &rect);
                long width = rect.right - rect.left;
                long height = rect.bottom - rect.top;

                // 计算居中位置
                rect.left = (screenWidth - width) / 2;
                rect.top = (screenHeight - height) / 2;

                // 移动窗口到屏幕中心
                SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, width, height,
                    SWP_NOSIZE | SWP_NOZORDER);
            }

            /// @brief 设置窗口透明度
            /// @param hWnd 窗口句柄
            /// @param alpha 透明度值 (0-255)
            inline void SetWindowAlpha(HWND hWnd, BYTE alpha)
            {
                // 启用分层窗口属性
                SetWindowLongPtr(hWnd, GWL_EXSTYLE,
                    GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

                // 设置透明度
                SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
            }

            /// @brief 创建圆角矩形区域
            /// @param x 左上角X坐标
            /// @param y 左上角Y坐标
            /// @param width 宽度
            /// @param height 高度
            /// @param radius 圆角半径
            /// @return 圆角矩形区域句柄
            inline HRGN CreateRoundRectRegion(int x, int y, int width, int height, int radius)
            {
                return CreateRoundRectRgn(x, y, x + width, y + height, radius, radius);
            }

            /// @brief 移除窗口的标准标题栏和边框样式
            /// @param hWnd 窗口句柄
            inline void RemoveWindowChrome(HWND hWnd)
            {
                LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE);
                style &= ~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX | WS_THICKFRAME);
                SetWindowLongPtr(hWnd, GWL_STYLE, style);
            }

            /// @brief 设置窗口为工具窗口（不在任务栏显示）
            /// @param hWnd 窗口句柄
            inline void SetWindowAsTool(HWND hWnd)
            {
                LONG exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
                exStyle &= ~WS_EX_APPWINDOW;  // 移除APPWINDOW样式
                exStyle |= WS_EX_TOOLWINDOW;  // 添加工具窗口样式
                SetWindowLong(hWnd, GWL_EXSTYLE, exStyle);
            }

            // ===========================================================================
            // 颜色处理函数
            // ===========================================================================

            /// @brief 预乘颜色值（用于Alpha混合）
            /// @param color 原始颜色
            /// @param alpha Alpha值 (0-255)
            /// @return 预乘后的颜色值
            inline DWORD PreMultiplyColor(COLORREF color, BYTE alpha)
            {
                return (GetRValue(color) * (DWORD)alpha / 255) << 16 |
                    (GetGValue(color) * (DWORD)alpha / 255) << 8 |
                    (GetBValue(color) * (DWORD)alpha / 255);
            }

            /// @brief 颜色插值
            /// @param color1 起始颜色
            /// @param color2 结束颜色
            /// @param factor 插值因子 (0.0-1.0)
            /// @return 插值后的颜色
            inline COLORREF InterpolateColor(COLORREF color1, COLORREF color2, float factor)
            {
                factor = std::clamp(factor, 0.0f, 1.0f);

                BYTE r = (BYTE)(GetRValue(color1) * (1 - factor) + GetRValue(color2) * factor);
                BYTE g = (BYTE)(GetGValue(color1) * (1 - factor) + GetGValue(color2) * factor);
                BYTE b = (BYTE)(GetBValue(color1) * (1 - factor) + GetBValue(color2) * factor);

                return RGB(r, g, b);
            }

            /// @brief 调整颜色亮度
            /// @param color 原始颜色
            /// @param factor 亮度因子 (>1变亮, <1变暗)
            /// @return 调整后的颜色
            inline COLORREF AdjustColorBrightness(COLORREF color, float factor)
            {
                BYTE r = (BYTE)std::clamp(GetRValue(color) * factor, 0.0f, 255.0f);
                BYTE g = (BYTE)std::clamp(GetGValue(color) * factor, 0.0f, 255.0f);
                BYTE b = (BYTE)std::clamp(GetBValue(color) * factor, 0.0f, 255.0f);

                return RGB(r, g, b);
            }

            // ===========================================================================
            // GDI辅助函数
            // ===========================================================================

            /// @brief 创建32位ARGB位图
            /// @param hdc 设备上下文
            /// @param width 位图宽度
            /// @param height 位图高度
            /// @param bits 返回的位图数据指针
            /// @return 位图句柄
            inline HBITMAP CreateARGBBitmap(HDC hdc, int width, int height, BYTE** bits = nullptr)
            {
                BITMAPINFO bmi = { 0 };
                bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                bmi.bmiHeader.biWidth = width;
                bmi.bmiHeader.biHeight = height;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biBitCount = 32;
                bmi.bmiHeader.biCompression = BI_RGB;
                bmi.bmiHeader.biSizeImage = width * height * 4;

                return CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)bits, NULL, 0);
            }

            /// @brief 使用Alpha混合绘制位图
            /// @param hdc 目标设备上下文
            /// @param x 目标X坐标
            /// @param y 目标Y坐标
            /// @param width 宽度
            /// @param height 高度
            /// @param srcDC 源设备上下文
            /// @param srcX 源X坐标
            /// @param srcY 源Y坐标
            /// @param alpha 透明度 (0-255)
            inline void AlphaBlit(HDC hdc, int x, int y, int width, int height,
                HDC srcDC, int srcX, int srcY, BYTE alpha = 255)
            {
                BLENDFUNCTION blend = { 0 };
                blend.BlendOp = AC_SRC_OVER;
                blend.BlendFlags = 0;
                blend.SourceConstantAlpha = alpha;
                blend.AlphaFormat = AC_SRC_ALPHA;

                POINT dstPoint = { x, y };
                SIZE size = { width, height };
                POINT srcPoint = { srcX, srcY };

                AlphaBlend(hdc, dstPoint.x, dstPoint.y, size.cx, size.cy,
                    srcDC, srcPoint.x, srcPoint.y, size.cx, size.cy, blend);
            }

            // ===========================================================================
            // 矩形操作函数
            // ===========================================================================

            /// @brief 获取矩形宽度
            /// @param rect 矩形结构
            /// @return 宽度
            inline int RectWidth(const RECT& rect)
            {
                return rect.right - rect.left;
            }

            /// @brief 获取矩形高度
            /// @param rect 矩形结构
            /// @return 高度
            inline int RectHeight(const RECT& rect)
            {
                return rect.bottom - rect.top;
            }

            /// @brief 矩形是否包含点
            /// @param rect 矩形
            /// @param pt 点
            /// @return 是否包含
            inline bool RectContainsPoint(const RECT& rect, const POINT& pt)
            {
                return PtInRect(&rect, pt);
            }

            /// @brief 矩形是否包含点坐标
            /// @param rect 矩形
            /// @param x X坐标
            /// @param y Y坐标
            /// @return 是否包含
            inline bool RectContainsPoint(const RECT& rect, int x, int y)
            {
                POINT pt = { x, y };
                return PtInRect(&rect, pt);
            }

            /// @brief 偏移矩形
            /// @param rect 矩形
            /// @param dx X偏移量
            /// @param dy Y偏移量
            inline void OffsetRect(RECT& rect, int dx, int dy)
            {
                rect.left += dx;
                rect.right += dx;
                rect.top += dy;
                rect.bottom += dy;
            }

            /// @brief 膨胀矩形
            /// @param rect 矩形
            /// @param dx 水平膨胀量
            /// @param dy 垂直膨胀量
            inline void InflateRect(RECT& rect, int dx, int dy)
            {
                rect.left -= dx;
                rect.right += dx;
                rect.top -= dy;
                rect.bottom += dy;
            }

            // ===========================================================================
            // 调试和错误处理
            // ===========================================================================

#ifdef _DEBUG
    /// @brief 调试输出
    /// @param format 格式化字符串
    /// @param ... 可变参数
            inline void DebugOutput(const wchar_t* format, ...)
            {
                wchar_t buffer[1024];
                va_list args;
                va_start(args, format);
                vswprintf_s(buffer, format, args);
                va_end(args);
                OutputDebugString(buffer);
            }

            /// @brief 检查GDI错误
            /// @param operation 操作描述
            inline void CheckGDIFrror(const wchar_t* operation)
            {
                DWORD error = GetLastError();
                if (error != 0)
                {
                    DebugOutput(L"GDI Error in %s: %d\n", operation, error);
                }
            }
#else
            inline void DebugOutput(const wchar_t* format, ...) {}
            inline void CheckGDIFrror(const wchar_t* operation) {}
#endif

            // ===========================================================================
            // 字符串辅助函数
            // ===========================================================================

            /// @brief 安全拷贝字符串
            /// @param dest 目标缓冲区
            /// @param src 源字符串
            /// @param destSize 目标缓冲区大小
            inline void SafeCopyString(wchar_t* dest, const wchar_t* src, size_t destSize)
            {
                if (dest && destSize > 0)
                {
                    wcsncpy_s(dest, destSize, src, _TRUNCATE);
                }
            }

            /// @brief 整数转字符串
            /// @param value 整数值
            /// @param buffer 输出缓冲区
            /// @param bufferSize 缓冲区大小
            inline void IntToString(int value, wchar_t* buffer, size_t bufferSize)
            {
                _itow_s(value, buffer, bufferSize, 10);
            }

        } // namespace Utils
    } // namespace Window
} // namespace VertexUI

// 向后兼容的宏定义
#define AlphaSet SetWindowAlpha(hWnd, Alpha)