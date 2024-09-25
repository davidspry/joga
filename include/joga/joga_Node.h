///  ┬┌─┐┌─┐┌─┐
///  ││ ││ ┬├─┤
/// └┘└─┘└─┘┴ ┴

#pragma once

#include <utility>

#include <juce_gui_basics/juce_gui_basics.h>
#include <yoga/Yoga.h>

#include "joga_LayoutNodeInterface.h"

namespace joga
{

/// @brief A node in a layout hierarchy.

class Node final: public impl::LayoutNode,
                  public impl::LayoutNodeInterface<Node> {
  juce::Component& m_component;
  int m_w = 0;
  int m_h = 0;

public:
  explicit Node(juce::Component& component): m_component(component) {}

  /// @brief Specify a size to be applied to the component after layout.
  /// @param size The post-layout size
  [[nodiscard]]
  auto withSizeAfterLayout(const juce::Rectangle<int>& size) && -> Node&& {
    m_w = size.getWidth();
    m_h = size.getHeight();
    return std::move(*this);
  }

  /// @brief Notify the node that its layout has been updated.
  /// @param parentOffsetX The x-offset of the node's parent within the layout.
  /// @param parentOffsetY The y-offset of the node's parent within the layout.
  void didUpdateLayout(const float parentOffsetX, const float parentOffsetY) override {
    const auto bounds = juce::Rectangle{
      YGNodeLayoutGetLeft(this),
      YGNodeLayoutGetTop(this),
      YGNodeLayoutGetWidth(this),
      YGNodeLayoutGetHeight(this)
    }.translated(parentOffsetX, parentOffsetY)
     .toNearestInt();

    m_component.setBounds(m_w > 0 && m_h > 0 ? bounds.withSizeKeepingCentre(m_w, m_h) : bounds);
  }
};

}
