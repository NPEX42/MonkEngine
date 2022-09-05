#include "custom/Viewport.h"

UI::Viewport UI::Viewport::Create(int width, int height)
{
    return Viewport(width, height);
}

UI::Viewport::Viewport(int width, int height)
    : m_fbo(gl::FrameBuffer::Create(width, height))
{
}

void UI::Viewport::begin(const char* name)
{
    m_fbo.bind();
    ImGui::Begin("ViewPort");
}

void UI::Viewport::end()
{
    ImVec2 viewport = ImGui::GetContentRegionAvail();
    ImGui::Image((void*)m_fbo.color_id(), viewport);
    ImGui::End();
    m_fbo.unbind();
}

gl::FrameBuffer* UI::Viewport::framebuffer()
{
    return &m_fbo;
}

