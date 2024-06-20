///  ┬┌─┐┌─┐┌─┐
///  ││ ││ ┬├─┤
/// └┘└─┘└─┘┴ ┴

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <yoga/Yoga.h>

#include "joga_LayoutNodeInterface.h"

namespace joga
{

/// @brief A node in a layout hierarchy.

class Node final: public impl::LayoutNode,
                  public impl::LayoutNodeInterface<Node> {
  juce::Component& m_component;

public:
  explicit Node(juce::Component& component): m_component(component) {
    if (const auto bounds = component.getBounds(); !bounds.isEmpty()) {
      this->withBounds(bounds);
    }
  }

  /// @brief Notify the node that its layout has been updated.
  /// @param parentOffsetX The x-offset of the node's parent within the layout.
  /// @param parentOffsetY The y-offset of the node's parent within the layout.
  void didUpdateLayout(const float parentOffsetX, const float parentOffsetY) override {
    m_component.setBounds(
        juce::Rectangle{
            YGNodeLayoutGetLeft(this),
            YGNodeLayoutGetTop(this),
            YGNodeLayoutGetWidth(this),
            YGNodeLayoutGetHeight(this)
        }.translated(parentOffsetX, parentOffsetY)
         .toNearestInt()
    );
  }
};

}
