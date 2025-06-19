//
// Created by Vlad on 6/17/2025.
//
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ohud/canvas_box.hpp"


namespace ohud
{

    CanvasBox::CanvasBox(const ImVec2 top, ImVec2 bottom, const float ratio)
    {
        bottom.x = top.x;
        const auto height = std::abs(top.y - bottom.y);

        top_left_corner = top - ImVec2{height / ratio, 0};
        top_right_corner = top + ImVec2{height / ratio, 0};

        bottom_left_corner = bottom - ImVec2{height / ratio, 0};
        bottom_right_corner = bottom + ImVec2{height / ratio, 0};
    }
    std::array<ImVec2, 4> CanvasBox::as_array() const
    {
        return {top_left_corner, top_right_corner, bottom_right_corner, bottom_left_corner};
    }
} // namespace ohud