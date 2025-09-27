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
    void EntityOverlayRender::add_cornered_2d_box(const ImColor& box_color, const ImColor& fill_color,
                                                  const float corner_ratio_len, const float thickness) const
    {
        const auto draw_list = ImGui::GetBackgroundDrawList();
        const auto corner_line_length =
                std::abs((m_canvas.top_left_corner - m_canvas.top_right_corner).x * corner_ratio_len);

        // Left Side
        draw_list->AddLine(m_canvas.top_left_corner, m_canvas.top_left_corner + ImVec2{corner_line_length, 0.f},
                           box_color, thickness);

        draw_list->AddLine(m_canvas.top_left_corner, m_canvas.top_left_corner + ImVec2{0.f, corner_line_length},
                           box_color, thickness);

        draw_list->AddLine(m_canvas.bottom_left_corner, m_canvas.bottom_left_corner - ImVec2{0.f, corner_line_length},
                           box_color, thickness);

        draw_list->AddLine(m_canvas.bottom_left_corner, m_canvas.bottom_left_corner + ImVec2{corner_line_length, 0.f},
                           box_color, thickness);
        // Right Side
        draw_list->AddLine(m_canvas.top_right_corner, m_canvas.top_right_corner - ImVec2{corner_line_length, 0.f},
                           box_color, thickness);

        draw_list->AddLine(m_canvas.top_right_corner, m_canvas.top_right_corner + ImVec2{0.f, corner_line_length},
                           box_color, thickness);

        draw_list->AddLine(m_canvas.bottom_right_corner, m_canvas.bottom_right_corner - ImVec2{0.f, corner_line_length},
                           box_color, thickness);

        draw_list->AddLine(m_canvas.bottom_right_corner, m_canvas.bottom_right_corner - ImVec2{corner_line_length, 0.f},
                           box_color, thickness);
    }
    void EntityOverlayRender::add_right_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color,
                                            const float width, float ratio, const float offset)
    {
        ratio = std::clamp(ratio, 0.f, 1.f);
        const auto draw_list = ImGui::GetBackgroundDrawList();
        const auto max_bar_height = std::abs(m_canvas.top_right_corner.y - m_canvas.bottom_right_corner.y);

        const auto bar_start = m_canvas.bottom_right_corner + ImVec2{offset, 0.f};
        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(width, -max_bar_height), bg_color);

        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(width, -max_bar_height * ratio), color);
        draw_list->AddRect(bar_start - ImVec2(1.f, 0.f), bar_start + ImVec2(width, -max_bar_height), outline_color);

        // NOTE: Move text 1 pixel horizontali due to imgui logic of rendering rectangle
        m_text_cursor_right.x += offset + width + 1.f;
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
        draw_list->AddRect(bar_start - ImVec2(1.f, 0.f), bar_start + ImVec2(width, -max_bar_height), outline_color);
    }
    void EntityOverlayRender::add_right_label(const ImColor& color, const float offset, const bool outlined,
                                              const std::string_view& text)
    {
        const auto draw_list = ImGui::GetBackgroundDrawList();

        if (outlined)
            draw_outlined_text(m_text_cursor_right + ImVec2{offset, 0.f}, color, text);
        else
            draw_list->AddText(m_text_cursor_right + ImVec2{offset, 0.f}, color, text.data());

        m_text_cursor_right.y += ImGui::CalcTextSize(text.data()).y;
    }
    void EntityOverlayRender::add_top_label(const ImColor& color, const float offset, const bool outlined,
                                            const std::string_view text)
    {
        const auto draw_list = ImGui::GetBackgroundDrawList();

        m_text_cursor_top.y -= ImGui::CalcTextSize(text.data()).y;

        if (outlined)
            draw_outlined_text(m_text_cursor_top + ImVec2{0.f, -offset}, color, text);
        else
            draw_list->AddText(m_text_cursor_top + ImVec2{0.f, -offset}, color, text.data());
    }
    void EntityOverlayRender::add_top_bar(const ImColor& color, const ImColor& outline_color, const ImColor& bg_color,
                                          const float height, float ratio, const float offset)
    {
        ratio = std::clamp(ratio, 0.f, 1.f);

        const auto draw_list = ImGui::GetBackgroundDrawList();
        const auto max_bar_width = std::abs(m_canvas.top_left_corner.x - m_canvas.bottom_right_corner.x);

        const auto bar_start = m_canvas.top_left_corner - ImVec2{0.f, offset};
        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(max_bar_width, -height), bg_color);

        draw_list->AddRectFilled(bar_start, bar_start + ImVec2(max_bar_width * ratio, -height), color);
        draw_list->AddRect(bar_start, bar_start + ImVec2(max_bar_width, -height), outline_color);

        m_text_cursor_top.y -= offset + height;
    }
    void EntityOverlayRender::draw_outlined_text(const ImVec2& position, const ImColor& color,
                                                 const std::string_view& text) const
    {
        const auto draw_list = ImGui::GetBackgroundDrawList();
        static constexpr std::array outline_offsets = {ImVec2{-1, -1}, ImVec2{-1, 0}, ImVec2{-1, 1}, ImVec2{0, -1},
                                                       ImVec2{0, 1},   ImVec2{1, -1}, ImVec2{1, 0},  ImVec2{1, 1}};

        for (const auto& outline_offset: outline_offsets)
            draw_list->AddText(position + outline_offset, ImColor{0.f, 0.f, 0.f, 1.f}, text.data());
        draw_list->AddText(position, color, text.data());
    }
    EntityOverlayRender::EntityOverlayRender(const ImVec2& top, const ImVec2& bottom)
        : m_canvas(top, bottom), m_text_cursor_right(m_canvas.top_right_corner),
          m_text_cursor_top(m_canvas.top_left_corner)
    {
    }
} // namespace ohud