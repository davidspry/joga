#pragma once

#include "joga_LayoutNode.hh"

#include <yoga/YGEnums.h>
#include <yoga/YGNode.h>

#include <array>
#include <tuple>
#include <utility>

namespace joga::impl
{

template<YGFlexDirection F, YGJustify J>
struct Spec final
{
    template<AnyLayoutNode... T>
    class Layout final: public LayoutNode
    {
        std::tuple<T...> m_nodes;

    public:
        Layout(T&&... nodes)
            : m_nodes(std::move(nodes)...)
        {
            auto children = child_nodes();
            YGNodeStyleSetFlexDirection(this, F);
            YGNodeStyleSetJustifyContent(this, J);
            YGNodeSetChildren(this, children.data(), children.size());
        }

        Layout(Layout&& other) noexcept
            : m_nodes(std::move(other.m_nodes))
        {
            auto children = child_nodes();
            YGNodeCopyStyle(this, &other);
            YGNodeSetChildren(this, children.data(), children.size());
            YGNodeRemoveAllChildren(&other);
        }

        Layout(const Layout&) = delete;
        Layout& operator=(const Layout&) = delete;
        Layout& operator=(Layout&&) = delete;

        void layout()
        {
            YGNodeCalculateLayout(this, YGUndefined, YGUndefined, YGDirectionLTR);

            float dx = 0.0f;
            float dy = 0.0f;

            if (auto parent = YGNodeGetParent(this))
            {
                dx = YGNodeLayoutGetLeft(parent);
                dy = YGNodeLayoutGetTop(parent);
            }

            didUpdateLayout(dx, dy);
        }

        void didUpdateLayout(float dx, float dy) override
        {
            std::apply([this, dx, dy](auto&&... components) {
                (..., components.didUpdateLayout(
                    dx + YGNodeLayoutGetLeft(this),
                    dy + YGNodeLayoutGetTop(this)));
            }, m_nodes);
        }

    private:
        auto child_nodes()
        {
            return std::apply([](auto&&... node)
            {
                return std::array<YGNodeRef, sizeof...(T)>{&node...};
            }, m_nodes);
        }
    };
};

}
