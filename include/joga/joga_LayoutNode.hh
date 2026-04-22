#pragma once

#include <juce_graphics/juce_graphics.h>
#include <yoga/node/Node.h>

#include <concepts>
#include <utility>

namespace joga::impl
{

struct LayoutNode;

template<class T>
concept AnyLayoutNode = std::derived_from<T, LayoutNode>;

struct LayoutNode: protected facebook::yoga::Node
{
    virtual void didUpdateLayout(float dx, float dy) = 0;

    template<class Self>
    Self&& withStyleFrom(this Self&& self, const YGNode& node)
    {
        YGNodeCopyStyle(&self, &node);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAspectRatio(this Self&& self, float aspectRatio)
    {
        YGNodeStyleSetAspectRatio(&self, aspectRatio);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withSize(this Self&& self, const juce::Rectangle<float>& size)
    {
        YGNodeStyleSetWidth(std::addressof(self), size.getWidth());
        YGNodeStyleSetHeight(std::addressof(self), size.getHeight());
        return std::forward<Self>(self);
    }

    template<class Self, class T>
    Self&& withSize(this Self&& self, const juce::Rectangle<T>& size)
    {
        return std::forward<Self>(self).withSize(size.toFloat());
    }

    template<class Self>
    Self&& withBounds(this Self&& self, const juce::Rectangle<float>& bounds)
    {
        YGNodeStyleSetPosition(std::addressof(self), YGEdgeLeft, bounds.getX());
        YGNodeStyleSetPosition(std::addressof(self), YGEdgeTop, bounds.getY());
        return std::forward<Self>(self).withSize(bounds);
    }

    template<class Self, class T>
    Self&& withBounds(this Self&& self, const juce::Rectangle<T>& bounds)
    {
        return std::forward<Self>(self).withBounds(bounds.toFloat());
    }

    template<class Self>
    Self&& withWidth(this Self&& self, float value)
    {
        YGNodeStyleSetWidth(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withHeight(this Self&& self, float value)
    {
        YGNodeStyleSetHeight(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withWidthPercent(this Self&& self, float percent)
    {
        YGNodeStyleSetWidthPercent(&self, percent);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withHeightPercent(this Self&& self, float percent)
    {
        YGNodeStyleSetHeightPercent(&self, percent);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAutoWidth(this Self&& self)
    {
        YGNodeStyleSetWidthAuto(&self);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAutoHeight(this Self&& self)
    {
        YGNodeStyleSetHeightAuto(&self);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMaxWidth(this Self&& self, float value)
    {
        YGNodeStyleSetMaxWidth(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMinWidth(this Self&& self, float value)
    {
        YGNodeStyleSetMinWidth(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMaxHeight(this Self&& self, float value)
    {
        YGNodeStyleSetMaxHeight(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMinHeight(this Self&& self, float value)
    {
        YGNodeStyleSetMinHeight(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMaxWidthPercent(this Self&& self, float value)
    {
        YGNodeStyleSetMaxWidthPercent(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMinWidthPercent(this Self&& self, float value)
    {
        YGNodeStyleSetMinWidthPercent(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMaxHeightPercent(this Self&& self, float value)
    {
        YGNodeStyleSetMaxHeightPercent(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMinHeightPercent(this Self&& self, float value)
    {
        YGNodeStyleSetMinHeightPercent(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withPadding(this Self&& self, float padding, YGEdge edge = YGEdgeAll)
    {
        YGNodeStyleSetPadding(&self, edge, padding);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withPaddingPercent(this Self&& self, float padding, YGEdge edge = YGEdgeAll)
    {
        YGNodeStyleSetPaddingPercent(&self, edge, padding);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMargin(this Self&& self, float margin, YGEdge edge = YGEdgeAll)
    {
        YGNodeStyleSetMargin(&self, edge, margin);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withMarginPercent(this Self&& self, float margin, YGEdge edge = YGEdgeAll)
    {
        YGNodeStyleSetMarginPercent(&self, edge, margin);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAutoMargin(this Self&& self, YGEdge edge = YGEdgeAll)
    {
        YGNodeStyleSetMarginAuto(&self, edge);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withBorder(this Self&& self, float border, YGEdge edge = YGEdgeAll)
    {
        YGNodeStyleSetBorder(&self, edge, border);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withFlexDirection(this Self&& self, YGFlexDirection direction)
    {
        YGNodeStyleSetFlexDirection(&self, direction);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withFlexGrow(this Self&& self, float value)
    {
        YGNodeStyleSetFlexGrow(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withFlexShrink(this Self&& self, float value)
    {
        YGNodeStyleSetFlexShrink(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withFlexBasis(this Self&& self, float value)
    {
        YGNodeStyleSetFlexBasis(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withFlexBasisPercent(this Self&& self, float value)
    {
        YGNodeStyleSetFlexBasisPercent(&self, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAutoFlexBasis(this Self&& self)
    {
        YGNodeStyleSetFlexBasisAuto(&self);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withGap(this Self&& self, float gap, YGGutter gutter = YGGutterAll)
    {
        YGNodeStyleSetGap(&self, gutter, gap);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withColumnGap(this Self&& self, float gap)
    {
        YGNodeStyleSetGap(&self, YGGutterColumn, gap);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withRowGap(this Self&& self, float gap)
    {
        YGNodeStyleSetGap(&self, YGGutterRow, gap);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withGapPercent(this Self&& self, float gap, YGGutter gutter = YGGutterAll)
    {
        YGNodeStyleSetGapPercent(&self, gutter, gap);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withColumnGapPercent(this Self&& self, float gap)
    {
        YGNodeStyleSetGapPercent(&self, YGGutterColumn, gap);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withRowGapPercent(this Self&& self, float gap)
    {
        YGNodeStyleSetGapPercent(&self, YGGutterRow, gap);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withJustifyContent(this Self&& self, YGJustify justification)
    {
        YGNodeStyleSetJustifyContent(&self, justification);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAlignContent(this Self&& self, YGAlign alignment)
    {
        YGNodeStyleSetAlignContent(&self, alignment);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAlignItems(this Self&& self, YGAlign align)
    {
        YGNodeStyleSetAlignItems(&self, align);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withAlignSelf(this Self&& self, YGAlign align)
    {
        YGNodeStyleSetAlignSelf(&self, align);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withPosition(this Self&& self, float value, YGEdge edge)
    {
        YGNodeStyleSetPosition(&self, edge, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withPositionPercent(this Self&& self, float value, YGEdge edge)
    {
        YGNodeStyleSetPositionPercent(&self, edge, value);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withPositionType(this Self&& self, YGPositionType type)
    {
        YGNodeStyleSetPositionType(&self, type);
        return std::forward<Self>(self);
    }

    template<class Self>
    Self&& withOverflow(this Self&& self, YGOverflow overflow)
    {
        YGNodeStyleSetOverflow(&self, overflow);
        return std::forward<Self>(self);
    }
};

}
