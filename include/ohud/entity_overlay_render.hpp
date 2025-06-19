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
        void add_left_label(const ImColor& color, const std::string_view& text) const;
        void add_right_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color, float width,
                           float ratio, float offset = 5.f) const;
        void add_left_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color, float width,
                          float ratio, float offset = 5.f) const;

    private:
        CanvasBox m_canvas;
    };
} // namespace ohud