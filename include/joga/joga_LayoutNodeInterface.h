///  ┬┌─┐┌─┐┌─┐
///  ││ ││ ┬├─┤
/// └┘└─┘└─┘┴ ┴

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <yoga/Yoga.h>
#include <yoga/node/Node.h>

namespace joga::impl
{

struct LayoutNode: facebook::yoga::Node {
  virtual ~LayoutNode() = default;
  virtual void didUpdateLayout(float, float) = 0;
};

template<class Node>
class LayoutNodeInterface {
  Node* m_this = static_cast<Node*>(this);

public:
  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withStyleFrom(const YGNode& node) -> Node& {
    YGNodeCopyStyle(static_cast<YGNodeRef>(m_this), &node);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withBounds(const juce::Rectangle<int>& newBounds) -> Node& {
    const auto bounds = newBounds.toFloat();
    YGNodeStyleSetPosition(m_this, YGEdgeLeft, bounds.getX());
    YGNodeStyleSetPosition(m_this, YGEdgeTop, bounds.getY());
    YGNodeStyleSetWidth(m_this, bounds.getWidth());
    YGNodeStyleSetHeight(m_this, bounds.getHeight());
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withAspectRatio(const float aspectRatio) -> Node& {
    YGNodeStyleSetAspectRatio(m_this, aspectRatio);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withWidth(const float value) -> Node& {
    YGNodeStyleSetWidth(m_this, value);
    return *m_this;
  }

  auto withHeight(const float value) -> Node& {
    YGNodeStyleSetHeight(m_this, value);
    return *m_this;
  }

  auto withWidthPercent(const float percent) -> Node& {
    YGNodeStyleSetWidthPercent(m_this, percent);
    return *m_this;
  }

  auto withHeightPercent(const float percent) -> Node& {
    YGNodeStyleSetHeightPercent(m_this, percent);
    return *m_this;
  }

  auto withAutoWidth() -> Node& {
    YGNodeStyleSetWidthAuto(m_this);
    return *m_this;
  }

  auto withAutoHeight() -> Node& {
    YGNodeStyleSetHeightAuto(m_this);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withMaxWidth(const float value) -> Node& {
    YGNodeStyleSetMaxWidth(m_this, value);
    return *m_this;
  }

  auto withMinWidth(const float value) -> Node& {
    YGNodeStyleSetMinWidth(m_this, value);
    return *m_this;
  }

  auto withMaxHeight(const float value) -> Node& {
    YGNodeStyleSetMaxHeight(m_this, value);
    return *m_this;
  }

  auto withMinHeight(const float value) -> Node& {
    YGNodeStyleSetMinHeight(m_this, value);
    return *m_this;
  }

  auto withMaxWidthPercent(const float value) -> Node& {
    YGNodeStyleSetMaxWidthPercent(m_this, value);
    return *m_this;
  }

  auto withMinWidthPercent(const float value) -> Node& {
    YGNodeStyleSetMinWidthPercent(m_this, value);
    return *m_this;
  }

  auto withMaxHeightPercent(const float value) -> Node& {
    YGNodeStyleSetMaxHeightPercent(m_this, value);
    return *m_this;
  }

  auto withMinHeightPercent(const float value) -> Node& {
    YGNodeStyleSetMinHeightPercent(m_this, value);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withPadding(const float padding, const YGEdge edge = YGEdgeAll) -> Node& {
    YGNodeStyleSetPadding(m_this, edge, padding);
    return *m_this;
  }

  auto withPaddingPercent(const float padding, const YGEdge edge = YGEdgeAll) -> Node& {
    YGNodeStyleSetPaddingPercent(m_this, edge, padding);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withMargin(const float margin, const YGEdge edge = YGEdgeAll) -> Node& {
    YGNodeStyleSetMargin(m_this, edge, margin);
    return *m_this;
  }

  auto withMarginPercent(const float margin, const YGEdge edge = YGEdgeAll) -> Node& {
    YGNodeStyleSetMarginPercent(m_this, edge, margin);
    return *m_this;
  }

  auto withAutoMargin(const YGEdge edge = YGEdgeAll) -> Node& {
    YGNodeStyleSetMarginAuto(m_this, edge);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withBorder(const float border, const YGEdge edge = YGEdgeAll) -> Node& {
    YGNodeStyleSetBorder(m_this, edge, border);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withFlexDirection(const YGFlexDirection direction) -> Node& {
    YGNodeStyleSetFlexDirection(m_this, direction);
    return *m_this;
  }

  auto withFlexGrow(const float value) -> Node& {
    YGNodeStyleSetFlexGrow(m_this, value);
    return *m_this;
  }

  auto withFlexShrink(const float value) -> Node& {
    YGNodeStyleSetFlexShrink(m_this, value);
    return *m_this;
  }

  auto withFlexBasis(const float value) -> Node& {
    YGNodeStyleSetFlexBasis(m_this, value);
    return *m_this;
  }

  auto withFlexBasisPercent(const float value) -> Node& {
    YGNodeStyleSetFlexBasisPercent(m_this, value);
    return *m_this;
  }

  auto withAutoFlexBasis() -> Node& {
    YGNodeStyleSetFlexBasisAuto(m_this);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withGap(const float componentSpacing, const YGGutter gutter = YGGutterAll) -> Node& {
    YGNodeStyleSetGap(m_this, gutter, componentSpacing);
    return *m_this;
  }

  auto withHorizontalGap(const float componentSpacing) -> Node& {
    YGNodeStyleSetGap(m_this, YGGutterColumn, componentSpacing);
    return *m_this;
  }

  auto withVerticalGap(const float componentSpacing) -> Node& {
    YGNodeStyleSetGap(m_this, YGGutterRow, componentSpacing);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withJustifyContent(const YGJustify justification) -> Node& {
    YGNodeStyleSetJustifyContent(m_this, justification);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withAlignContent(const YGAlign alignment) -> Node& {
    YGNodeStyleSetAlignContent(m_this, alignment);
    return *m_this;
  }

  auto withAlignItems(const YGAlign alignment) -> Node& {
    YGNodeStyleSetAlignItems(m_this, alignment);
    return *m_this;
  }

  auto withAlignSelf(const YGAlign alignment) -> Node& {
    YGNodeStyleSetAlignSelf(m_this, alignment);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withPosition(const float value, const YGEdge edge) -> Node& {
    YGNodeStyleSetPosition(m_this, edge, value);
    return *m_this;
  }

  auto withPositionPercent(const float value, const YGEdge edge) -> Node& {
    YGNodeStyleSetPositionPercent(m_this, edge, value);
    return *m_this;
  }

  auto withPositionType(const YGPositionType positionType) -> Node& {
    YGNodeStyleSetPositionType(m_this, positionType);
    return *m_this;
  }

  //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
  auto withOverflow(const YGOverflow overflow) -> Node& {
    YGNodeStyleSetOverflow(m_this, overflow);
    return *m_this;
  }
};

}
