#ifndef Concepts_H
#define Concepts_H

#include <algorithm>
#include <functional>
#include <type_traits>

using namespace std;


template<typename T>
concept bool DefaultConstructible = is_default_constructible<T>::value;

template<typename T>
concept bool CopyConstructible = is_copy_constructible<T>::value;


template<typename T>
concept bool Swappable = requires(T a, T b) {
    { swap(a, b) } -> void;
};

template<typename T>
concept bool Destructible = requires(T a) {
    { (&a)->~T() } -> void;
};

template<typename T>
concept bool Iterable = requires (T a) {
    { begin(a) } -> typename T::iterator;
    { end(a) } -> typename T::iterator;
};

template<typename T>
concept bool ConstIterable = requires (T a) {
    { cbegin(a) } -> typename T::const_iterator;
    { cend(a) } -> typename T::const_iterator;
};

template<typename T>
concept bool EqualityComparable = requires (T a, T b) {
    { a == b } -> bool;
    { a != b } -> bool;
};

template<typename T>
concept bool Sizeable = requires (T a) {
    { a.size() } -> size_t;
    { a.max_size() } -> size_t;
    { a.empty() } -> bool;    
};

template<typename T>
concept bool Incrementable = requires (T a) {
    { a++ } -> T;
};

template<typename T>
concept bool Decrementable = requires (T a) {
    { a-- } -> T;
};

template<typename T>
concept bool Container = //DefaultConstructible<T> &&
                         CopyConstructible<T> &&
                         Destructible<T> &&
                         EqualityComparable<T> &&
                         Swappable<T> &&
                         Iterable<T> &&
                         ConstIterable<T>/* &&
                         Sizeable<T>*/;

template<typename T, typename V = typename T::value_type, typename I = typename T::iterator>
concept bool Insertable = requires (T a, V v, I it) {
    { a.insert(it, v) } -> I;
};

template<typename T, typename V = typename T::value_type, typename I = typename T::iterator>
concept bool PostInsertable = requires (T a, V v, I it) {
    { a.insert_after(it, v) } -> I;
    { a.before_begin() } -> I;
};

template<typename T, typename V = typename T::value_type, typename I = typename T::iterator>
concept bool InsertableContainer = Container<T> && Insertable<T, V, I>;

template<typename T, typename V = typename T::value_type, typename I = typename T::iterator>
concept bool PostInsertableContainer = Container<T> && PostInsertable<T, V, I>;

template<typename P, typename ... A>
concept bool Predicate = requires(P p, A ... args) {
    { p(args...) } -> bool;
};

template<typename P, typename O, typename ... A>
concept bool Selector = requires(P p, A ... args) {
    { p(args...) } -> O;
};

#endif
