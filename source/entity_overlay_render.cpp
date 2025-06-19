//
// Created by Vlad on 6/17/2025.
//
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ohud/entity_overlay_render.hpp"
#include <algorithm>

namespace ohud
{

    void EntityOverlayRender::add_2d_box(const ImColor& box_color, const ImColor& fill_color,
                                         const float thickness) const
    {
        const auto draw_list = ImGui::GetBackgroundDrawList();

        const auto points = m_canvas.as_array();

        draw_list->AddPolyline(points.data(), points.size(), box_color, ImDrawFlags_Closed, thickness);
        draw_list->AddConcavePolyFilled(points.data(), points.size(), fill_color);
    }
    void EntityOverlayRender::add_right_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color,
                                            const float width, float ratio, const float offset) const
    {
        ratio = std::clamp(ratio, 0.f, 1.f);
        const auto draw_list = ImGui::GetBackgroundDrawList();
        const auto max_bar_height = std::abs(m_canvas.top_right_corner.y - m_canvas.bottom_right_corner.y);

        const auto bar_start = m_canvas.bottom_right_corner + ImVec2{offset, 0.f};
        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(width, -max_bar_height), bg_color);

        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(width, -max_bar_height * ratio), color);
        draw_list->AddRect(bar_start, bar_start + ImVec2(width, -max_bar_height), outline_color);
    }
    void EntityOverlayRender::add_left_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color,
                                           const float width, float ratio, const float offset) const
    {
        ratio = std::clamp(ratio, 0.f, 1.f);
        const auto draw_list = ImGui::GetBackgroundDrawList();
        const auto max_bar_height = std::abs(m_canvas.top_left_corner.y - m_canvas.bottom_right_corner.y);

        const auto bar_start = m_canvas.bottom_left_corner + ImVec2{-(offset + width), 0.f};
        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(width, -max_bar_height), bg_color);

        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(width, -max_bar_height * ratio), color);
        draw_list->AddRect(bar_start, bar_start + ImVec2(width, -max_bar_height), outline_color);
    }
    EntityOverlayRender::EntityOverlayRender(const ImVec2& top, const ImVec2& bottom): m_canvas(top, bottom)
    {
    }
} // namespace ohud