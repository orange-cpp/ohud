//
// Created by Vlad on 6/17/2025.
//

#pragma once
#include <array>
#include <imgui.h>

namespace ohud
{
    struct CanvasBox
    {
        CanvasBox(ImVec2 top, ImVec2 bottom, float ratio = 4.f);

        [[nodiscard]]
        std::array<ImVec2, 4> as_array() const;

        ImVec2 top_left_corner;
        ImVec2 top_right_corner;

        ImVec2 bottom_left_corner;
        ImVec2 bottom_right_corner;
    };
} // namespace ohud