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
        void add2d_box(const ImColor& box_color, float thickness = 1.f) const;
        void add_left_label(const std::string_view)
    private:
        CanvasBox m_canvas;
        ImVec2
    };
} // namespace ohud