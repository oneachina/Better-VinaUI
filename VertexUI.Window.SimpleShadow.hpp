/**
 * SimpleShadow 模块
 * 提供直接在设备上下文上绘制的阴影效果
 * 适用于自定义绘图的控件和窗口
 * 使用形态学膨胀算法生成模糊阴影边界
 */

#pragma once
#include "VertexUI.Window.Utils.hpp"
#include <memory>
#include <vector>

#define win_max(a, b) (((a) > (b)) ? (a) : (b))

#define win_min(a, b) (((a) < (b)) ? (a) : (b))

    namespace VertexUI
{
    namespace Window
    {
        namespace SimpleShadow
        {
            // ===========================================================================
            // 阴影配置常量
            // ===========================================================================

            constexpr int MAX_SHADOW_SIZE = 40;           ///< 最大阴影尺寸
            constexpr int MIN_SHADOW_SIZE = -20;          ///< 最小阴影尺寸
            constexpr int MAX_SHADOW_SHARPNESS = 80;      ///< 最大阴影锐度
            constexpr int MAX_SHADOW_DARKNESS = 255;      ///< 最大阴影暗度
            constexpr int MAX_SHADOW_OFFSET = 20;         ///< 最大阴影偏移

            // ===========================================================================
            // iDropShadow 类 - 简单阴影绘制器
            // ===========================================================================

            /// @brief 简单阴影绘制器类
            /// 提供直接在DC上绘制的阴影效果，使用形态学膨胀算法生成模糊边界
            class iDropShadow
            {
            public:
                iDropShadow();
                virtual ~iDropShadow();

                /// @brief 创建阴影效果
                /// @param hdc 目标设备上下文
                /// @param x 目标区域X坐标
                /// @param y 目标区域Y坐标
                /// @param width 目标区域宽度
                /// @param height 目标区域高度
                /// @param radius 圆角半径
                void Create(HDC hdc, int x, int y, int width, int height, int radius);

                /// @brief 更新阴影显示
                /// @param hdc 目标设备上下文
                /// @param x 目标区域X坐标
                /// @param y 目标区域Y坐标
                /// @param width 目标区域宽度
                /// @param height 目标区域高度
                void Update(HDC hdc, int x, int y, int width, int height);

                // 阴影属性设置方法
                bool SetSize(int newSize = 0);
                bool SetSharpness(unsigned int newSharpness = 5);
                bool SetDarkness(unsigned int newDarkness = 200);
                bool SetPosition(int xOffset = 5, int yOffset = 5);
                bool SetColor(COLORREF newColor = 0);

                /// @brief 获取当前阴影大小
                int GetSize() const { return m_size; }

                /// @brief 获取当前阴影锐度
                unsigned int GetSharpness() const { return m_sharpness; }

                /// @brief 获取当前阴影暗度
                unsigned int GetDarkness() const { return m_darkness; }

            protected:
                /// @brief 生成阴影位图数据
                /// @param shadowBits 阴影位图数据指针
                /// @param x 目标区域X坐标
                /// @param y 目标区域Y坐标
                /// @param width 目标区域宽度
                /// @param height 目标区域高度
                void MakeShadow(UINT32* shadowBits, int x, int y, int width, int height);

                /// @brief 显示阴影
                /// @param hdc 目标设备上下文
                /// @param x 目标区域X坐标
                /// @param y 目标区域Y坐标
                /// @param width 目标区域宽度
                /// @param height 目标区域高度
                void Show(HDC hdc, int x, int y, int width, int height);

            private:
                // 阴影属性
                unsigned char m_darkness;     ///< 阴影暗度 (0-255)
                unsigned char m_sharpness;    ///< 阴影锐度
                signed char m_size;           ///< 阴影大小
                signed char m_xOffset;        ///< X轴偏移
                signed char m_yOffset;        ///< Y轴偏移
                COLORREF m_color;             ///< 阴影颜色
                int m_radius;                 ///< 圆角半径

                // 使用预乘颜色函数
                inline DWORD PreMultiply(COLORREF cl, unsigned char alpha)
                {
                    return Utils::PreMultiplyColor(cl, alpha);
                }

                // 禁止拷贝
                iDropShadow(const iDropShadow&) = delete;
                iDropShadow& operator=(const iDropShadow&) = delete;
            };

            // ===========================================================================
            // iDropShadow 实现
            // ===========================================================================

            /// @brief 构造函数
            inline iDropShadow::iDropShadow()
                : m_darkness(150)
                , m_sharpness(5)
                , m_size(50)
                , m_xOffset(5)
                , m_yOffset(5)
                , m_color(RGB(0, 0, 0))
                , m_radius(0)
            {
            }

            /// @brief 析构函数
            inline iDropShadow::~iDropShadow()
            {
                // 清理资源
            }

            /// @brief 创建阴影效果
            inline void iDropShadow::Create(HDC hdc, int x, int y, int width, int height, int radius)
            {
                m_radius = radius; // * gScale;  // 如果有全局缩放因子
                Show(hdc, (x + 1), (y + 1), (width - 2), (height - 2));
            }

            /// @brief 设置阴影大小
            inline bool iDropShadow::SetSize(int newSize)
            {
                if (newSize > MAX_SHADOW_SIZE || newSize < MIN_SHADOW_SIZE)
                    return false;

                m_size = static_cast<signed char>(newSize); // * gScale;  // 如果有全局缩放因子
                return true;
            }

            /// @brief 设置阴影锐度
            inline bool iDropShadow::SetSharpness(unsigned int newSharpness)
            {
                if (newSharpness > MAX_SHADOW_SHARPNESS)
                    return false;

                m_sharpness = static_cast<unsigned char>(newSharpness); // * gScale;
                return true;
            }

            /// @brief 设置阴影暗度
            inline bool iDropShadow::SetDarkness(unsigned int newDarkness)
            {
                if (newDarkness > MAX_SHADOW_DARKNESS)
                    return false;

                m_darkness = static_cast<unsigned char>(newDarkness);
                return true;
            }

            /// @brief 设置阴影位置偏移
            inline bool iDropShadow::SetPosition(int xOffset, int yOffset)
            {
                if (xOffset > MAX_SHADOW_OFFSET || xOffset < -MAX_SHADOW_OFFSET ||
                    yOffset > MAX_SHADOW_OFFSET || yOffset < -MAX_SHADOW_OFFSET)
                    return false;

                m_xOffset = static_cast<signed char>(xOffset); // * gScale;
                m_yOffset = static_cast<signed char>(yOffset); // * gScale;
                return true;
            }

            /// @brief 设置阴影颜色
            inline bool iDropShadow::SetColor(COLORREF newColor)
            {
                m_color = newColor;
                return true;
            }

            /// @brief 更新阴影显示
            inline void iDropShadow::Update(HDC hdc, int x, int y, int width, int height)
            {
                int shadowWidth = width + m_size * 2;
                int shadowHeight = height + m_size * 2;

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
                HBITMAP bitmap = Utils::CreateARGBBitmap(hdc, shadowWidth, shadowHeight, &bitmapBits);

                if (!bitmap || !bitmapBits)
                {
                    Utils::CheckGDIFrror(L"CreateARGBBitmap in Update");
                    return;
                }

                // 清空位图数据
                ZeroMemory(bitmapBits, bmi.bmiHeader.biSizeImage);

                // 生成阴影数据
                MakeShadow(reinterpret_cast<UINT32*>(bitmapBits), x, y, width, height);

                // 设置Alpha混合参数
                POINT srcPoint = { 0, 0 };
                SIZE size = { shadowWidth, shadowHeight };
                BLENDFUNCTION blendFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

                // 创建内存DC并选择位图
                HDC memDC = CreateCompatibleDC(hdc);
                if (!memDC)
                {
                    Utils::SafeDeleteObject(bitmap);
                    Utils::CheckGDIFrror(L"CreateCompatibleDC in Update");
                    return;
                }

                HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(memDC, bitmap));

                // 使用Alpha混合绘制阴影
                BOOL result = AlphaBlend(hdc,
                    x + m_xOffset - m_size,
                    y + m_yOffset - m_size,
                    width + m_size * 2,
                    height + m_size * 2,
                    memDC,
                    0, 0,
                    shadowWidth, shadowHeight,
                    blendFunction);

                if (!result)
                {
                    Utils::CheckGDIFrror(L"AlphaBlend in Update");
                }

                // 清理资源
                SelectObject(memDC, oldBitmap);
                Utils::SafeDeleteObject(bitmap);
                Utils::SafeReleaseDC(memDC);
            }

            /// @brief 显示阴影
            inline void iDropShadow::Show(HDC hdc, int x, int y, int width, int height)
            {
                Update(hdc, x, y, width, height);
            }

            /// @brief 生成阴影位图数据（核心算法）
            inline void iDropShadow::MakeShadow(UINT32* shadowBits, int x, int y, int width, int height)
            {
                // 阴影算法：应用修改后的形态学膨胀（带模糊效果）来创建模糊边界
                HRGN windowRegion = CreateRoundRectRgn(-1, -1, width + 2, height + 2, m_radius, m_radius);
                if (!windowRegion)
                {
                    Utils::CheckGDIFrror(L"CreateRoundRectRgn in MakeShadow");
                    return;
                }

                // 确定每个水平扫描线的起点和终点
                SIZE parentSize = { width, height };
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
                    // 调整指针位置
                    // anchors += m_size;  // 注意：这里不能直接+=，我们使用索引偏移
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
                Utils::SafeDeleteObject(windowRegion);

                // unique_ptr会自动释放内存，无需手动delete[]
            }

        } // namespace SimpleShadow
    } // namespace Window
} // namespace VertexUI