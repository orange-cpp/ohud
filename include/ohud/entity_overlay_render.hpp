//
// Created by Vlad on 6/17/2025.
//

#pragma once
#include "canvas_box.hpp"
#include <format>
#include <imgui.h>
#include <string_view>

namespace ohud
{
    class EntityOverlayRender
    {
    public:
        EntityOverlayRender(const ImVec2& top, const ImVec2& bottom);

        void add_2d_box(const ImColor& box_color, const ImColor& fill_color = ImColor{0.f, 0.f, 0.f, 0.f},
                        float thickness = 1.f) const;

        void add_right_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color, float width,
                           float ratio, float offset = 5.f);

        void add_left_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color, float width,
                          float ratio, float offset = 5.f) const;

        template<typename... Args>
        void add_right_label(const ImColor& color, const float offset, const bool outlined,
                             std::format_string<Args...> fmt, Args&&... args)
        {
            const std::string label = std::vformat(fmt.get(), std::make_format_args(args...));

            add_right_label(color, offset, outlined, std::string_view{label});
        }

        void add_right_label(const ImColor& color, float offset, bool outlined, std::string_view text);

        template<typename... Args>
        void add_top_label(const ImColor& color, const float offset, const bool outlined,
                             std::format_string<Args...> fmt, Args&&... args)
        {
            const std::string label = std::vformat(fmt.get(), std::make_format_args(args...));

            add_top_label(color, offset, outlined, std::string_view{label});
        }

        void add_top_label(const ImColor& color, float offset, bool outlined, std::string_view text);

        void add_top_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color, float height,
                          float ratio, float offset = 5.f);
        CanvasBox m_canvas;
        ImVec2 m_text_cursor_right;
        ImVec2 m_text_cursor_top;
    };
} // namespace ohud