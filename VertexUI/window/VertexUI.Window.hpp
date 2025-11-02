 // 核心依赖
#pragma once
#include <map>
#include <math.h>
#include <crtdbg.h>
#include <unordered_map>

// VertexUI 核心模块
#include "../VertexUI.min.h"
#include "../../LightFrame.WindowAnimation.h"

// 窗口组件模块
#include "VertexUI.Window.Utils.hpp"
#include "VertexUI.Window.SimpleShadow.hpp"
#include "VertexUI.Window.OuterShadow.hpp"

namespace VertexUI
{
    namespace Window
    {
        /// @brief 窗口工具函数
        namespace Utils
        {
            // 工具函数在 VertexUI.Window.Utils.hpp 中实现
        }

        /// @brief 简单阴影效果（直接绘制在DC上）
        namespace SimpleShadow
        {
            // 实现在 VertexUI.Window.SimpleShadow.hpp
        }

        /// @brief 外部窗口阴影（独立阴影窗口）
        namespace OuterShadow
        {
            // 实现在 VertexUI.Window.OuterShadow.hpp
        }

        /*
         * 以下模块已注释，需要时可启用
         * - Slider: 滑动条控件
         * - TimeSelector: 时间选择器
         * - iContainer: 智能容器
         */
    }
}