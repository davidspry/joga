///  ┬┌─┐┌─┐┌─┐
///  ││ ││ ┬├─┤
/// └┘└─┘└─┘┴ ┴

#pragma once

#include <concepts>
#include <tuple>
#include <utility>

#include <yoga/Yoga.h>

#include "joga_LayoutNodeInterface.h"

namespace joga::impl
{

template<YGFlexDirection FLEX_DIRECTION, YGJustify JUSTIFY_CONTENT>
struct LayoutSpec final {
  template<class... T> requires (std::derived_from<T, LayoutNode> && ...)
  class Layout final: public LayoutNode,
                      public LayoutNodeInterface<Layout<T...>> {
    std::tuple<T...> m_nodes;

  public:
    //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
    explicit Layout(T&&... nodes): m_nodes(std::move(nodes)...) {
      auto children = [this]<std::size_t... i>(std::index_sequence<i...>) {
        return std::array<YGNodeRef, sizeof...(T)>{&std::get<i>(m_nodes)...};
      }(std::make_index_sequence<sizeof...(T)>());

      YGNodeStyleSetFlexDirection(this, FLEX_DIRECTION);
      YGNodeStyleSetJustifyContent(this, JUSTIFY_CONTENT);
      YGNodeSetChildren(this, children.data(), children.size());
    }

    Layout(const Layout& layout): m_nodes(layout.m_nodes) {
      auto children = [this]<std::size_t... i>(std::index_sequence<i...>) {
        return std::array<YGNodeRef, sizeof...(T)>{&std::get<i>(m_nodes)...};
      }(std::make_index_sequence<sizeof...(T)>());

      YGNodeCopyStyle(this, &layout);
      YGNodeSetChildren(this, children.data(), children.size());
    }

    Layout(Layout&& layout) noexcept: m_nodes(std::move(layout.m_nodes)) {
      auto children = [this]<std::size_t... i>(std::index_sequence<i...>) {
        return std::array<YGNodeRef, sizeof...(T)>{&std::get<i>(m_nodes)...};
      }(std::make_index_sequence<sizeof...(T)>());

      YGNodeCopyStyle(this, &layout);
      YGNodeSetChildren(this, children.data(), children.size());
    }

    //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
    /// @brief Recursively calculate the layout of each node.
    void layout() {
      YGNodeCalculateLayout(this, YGUndefined, YGUndefined, YGDirectionLTR);
      if (const auto parent = YGNodeGetParent(this); parent != nullptr) {
        const auto parentOffsetX = YGNodeLayoutGetLeft(parent);
        const auto parentOffsetY = YGNodeLayoutGetTop(parent);
        didUpdateLayout(parentOffsetX, parentOffsetY);
      } else {
        didUpdateLayout(0.0f, 0.0f);
      }
    }

    //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
    void didUpdateLayout(const float parentOffsetX, const float parentOffsetY) override {
      std::apply([this, parentOffsetX, parentOffsetY](auto&&... components) {
        ([&, parentOffsetX, parentOffsetY] {
          const auto deltaX = parentOffsetX + YGNodeLayoutGetLeft(this);
          const auto deltaY = parentOffsetY + YGNodeLayoutGetTop(this);
          components.didUpdateLayout(deltaX, deltaY);
        }(), ...);
      }, m_nodes);
    }
  };

  template<class... T> Layout(const T&...) -> Layout<T...>;
};

}

// MARK: - Layout Aliases

namespace joga
{
using HStack        = impl::LayoutSpec<YGFlexDirectionRow,    YGJustifyFlexStart>;
using VStack        = impl::LayoutSpec<YGFlexDirectionColumn, YGJustifyFlexStart>;
using HStackCentre  = impl::LayoutSpec<YGFlexDirectionRow,    YGJustifyCenter>;
using VStackCentre  = impl::LayoutSpec<YGFlexDirectionColumn, YGJustifyCenter>;
using HSpaceAround  = impl::LayoutSpec<YGFlexDirectionRow,    YGJustifySpaceAround>;
using VSpaceAround  = impl::LayoutSpec<YGFlexDirectionColumn, YGJustifySpaceAround>;
using HSpaceBetween = impl::LayoutSpec<YGFlexDirectionRow,    YGJustifySpaceBetween>;
using VSpaceBetween = impl::LayoutSpec<YGFlexDirectionColumn, YGJustifySpaceBetween>;
using HSpaceEvenly  = impl::LayoutSpec<YGFlexDirectionRow,    YGJustifySpaceEvenly>;
using VSpaceEvenly  = impl::LayoutSpec<YGFlexDirectionColumn, YGJustifySpaceEvenly>;
}
