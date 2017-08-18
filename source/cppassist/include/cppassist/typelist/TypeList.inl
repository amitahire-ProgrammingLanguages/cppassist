
#pragma once


#include <utility>


namespace cppassist
{


template <typename T, typename... Types>
template <typename Functor>
void TypeList<T, Types...>::apply(Functor && callback)
{
    (callback.template apply<T>)();

    TypeList<Types...>::apply(std::forward<Functor>(callback));
}

template <typename Functor>
void TypeList<>::apply(Functor && /*callback*/)
{
}


} // namespace cppassist
