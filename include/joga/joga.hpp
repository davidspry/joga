#pragma once

#include <joga/joga_Layout.hh>
#include <joga/joga_Node.hh>

namespace joga
{

template<class... T>
using HStack = impl::Spec<YGFlexDirectionRow, YGJustifyFlexStart>::Layout<T...>;

template<class... T>
using VStack = impl::Spec<YGFlexDirectionColumn, YGJustifyFlexStart>::Layout<T...>;

template<class... T>
using HStackCenter = impl::Spec<YGFlexDirectionRow, YGJustifyCenter>::Layout<T...>;

template<class... T>
using VStackCenter = impl::Spec<YGFlexDirectionColumn, YGJustifyCenter>::Layout<T...>;

template<class... T>
using HStackReverse = impl::Spec<YGFlexDirectionRowReverse, YGJustifyFlexStart>::Layout<T...>;

template<class... T>
using VStackReverse = impl::Spec<YGFlexDirectionColumnReverse, YGJustifyFlexStart>::Layout<T...>;

template<class... T>
using HSpaceBetween = impl::Spec<YGFlexDirectionRow, YGJustifySpaceBetween>::Layout<T...>;

template<class... T>
using VSpaceBetween = impl::Spec<YGFlexDirectionColumn, YGJustifySpaceBetween>::Layout<T...>;

template<class... T>
using HSpaceAround = impl::Spec<YGFlexDirectionRow, YGJustifySpaceAround>::Layout<T...>;

template<class... T>
using VSpaceAround = impl::Spec<YGFlexDirectionColumn, YGJustifySpaceAround>::Layout<T...>;

template<class... T>
using HSpaceEvenly = impl::Spec<YGFlexDirectionRow, YGJustifySpaceEvenly>::Layout<T...>;

template<class... T>
using VSpaceEvenly = impl::Spec<YGFlexDirectionColumn, YGJustifySpaceEvenly>::Layout<T...>;  

}
