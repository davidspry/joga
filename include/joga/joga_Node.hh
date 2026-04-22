#pragma once

#include "joga_LayoutNode.hh"

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace joga
{

class Node: public joga::impl::LayoutNode
{
    juce::Component& m_component;

public:
    Node(juce::Component& component)
        : m_component(component) {}

    void didUpdateLayout(float dx, float dy) override
    {
        m_component.setBounds(
            YGNodeLayoutGetLeft(this) + dx,
            YGNodeLayoutGetTop(this) + dy,
            YGNodeLayoutGetWidth(this),
            YGNodeLayoutGetHeight(this));
    }
};

}
