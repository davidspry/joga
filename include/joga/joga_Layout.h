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
struct LayoutSpecification final {
  template<class... T> requires (std::derived_from<T, LayoutNode> && ...)
  class Layout final: public LayoutNode,
                      public LayoutNodeInterface<Layout<T...>> {
    std::tuple<const T&...> m_nodes;
    std::array<YGNodeRef, sizeof...(T)> m_nodes_ref;

  public:
    //⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
    explicit Layout(const T&... nodes): m_nodes(nodes...) {
      YGNodeStyleSetFlexDirection(this, FLEX_DIRECTION);
      YGNodeStyleSetJustifyContent(this, JUSTIFY_CONTENT);

      [this]<std::size_t... i>(const std::index_sequence<i...>) {
        ((m_nodes_ref[i] = &const_cast<T&>(std::get<i>(m_nodes))), ...);
      }(std::make_index_sequence<sizeof...(T)>());

      YGNodeSetChildren(this, m_nodes_ref.data(), m_nodes_ref.size());
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
          const_cast<T&>(components).didUpdateLayout(deltaX, deltaY);
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
using HStack        = impl::LayoutSpecification<YGFlexDirectionRow,    YGJustifyFlexStart>;
using VStack        = impl::LayoutSpecification<YGFlexDirectionColumn, YGJustifyFlexStart>;
using HStackCentre  = impl::LayoutSpecification<YGFlexDirectionRow,    YGJustifyCenter>;
using VStackCentre  = impl::LayoutSpecification<YGFlexDirectionColumn, YGJustifyCenter>;
using HSpaceAround  = impl::LayoutSpecification<YGFlexDirectionRow,    YGJustifySpaceAround>;
using VSpaceAround  = impl::LayoutSpecification<YGFlexDirectionColumn, YGJustifySpaceAround>;
using HSpaceBetween = impl::LayoutSpecification<YGFlexDirectionRow,    YGJustifySpaceBetween>;
using VSpaceBetween = impl::LayoutSpecification<YGFlexDirectionColumn, YGJustifySpaceBetween>;
using HSpaceEvenly  = impl::LayoutSpecification<YGFlexDirectionRow,    YGJustifySpaceEvenly>;
using VSpaceEvenly  = impl::LayoutSpecification<YGFlexDirectionColumn, YGJustifySpaceEvenly>;
}
