//
// Created by Vlad on 6/17/2025.
//
#include "ohud/entity_overlay_render.hpp"

namespace ohud
{

    void EntityOverlayRender::add2d_box(const ImColor& box_color, const float thickness) const
    {
        const auto draw_list = ImGui::GetBackgroundDrawList();

        const auto points = m_canvas.as_array();

        auto prev = points.cbegin();

        for (auto curr = std::next(points.cbegin()); curr != points.end(); curr = std::next(curr))
        {
            draw_list->AddLine(*curr, *prev, box_color, thickness);

            prev = curr;
        }
        draw_list->AddLine(points.front(), points.back(), box_color, thickness);
    }
    EntityOverlayRender::EntityOverlayRender(const ImVec2& top, const ImVec2& bottom) : m_canvas(top, bottom)
    {

    }
} // namespace ohud