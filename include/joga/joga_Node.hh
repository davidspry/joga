#pragma once

#include "joga_LayoutNode.hh"

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <utility>

namespace joga
{

class Node: public joga::impl::LayoutNode
{
    juce::Component& m_component;
    bool m_applyPositionOnly = false;

public:
    Node(juce::Component& component)
        : m_component(component) {}

    template<class Self>
    Self&& applyingPositionOnly(this Self&& self)
    {
        self.m_applyPositionOnly = true;
        return std::forward<Self>(self);
    }

    void didUpdateLayout(float dx, float dy) override
    {
        juce::Rectangle bounds(
            YGNodeLayoutGetLeft(this) + dx,
            YGNodeLayoutGetTop(this) + dy,
            YGNodeLayoutGetWidth(this),
            YGNodeLayoutGetHeight(this));

        if (m_applyPositionOnly)
        {
            bounds = bounds.withSizeKeepingCentre(
                static_cast<float>(m_component.getWidth()),
                static_cast<float>(m_component.getHeight()));
        }

        m_component.setBounds(bounds.toNearestInt());
    }
};

}
