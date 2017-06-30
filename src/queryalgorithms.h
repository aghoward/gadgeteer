#ifndef QueryAlgorithms_H
#define QueryAlgorithms_H

#include <algorithm>
#include <vector>

#include "concepts.h"

using namespace std;


template<typename C, typename P, typename V = typename C::value_type, typename I = typename C::iterator>
I last(C & collection, I iterator, P predicate) requires Container<C> && Predicate<P, V> && Incrementable<I> {
    I out;
    for (iterator; iterator != end(collection); iterator++) {
        if (predicate(*iterator))
            out = iterator;
    }

    return out;
}

template<typename C, typename V = typename C::value_type, typename I = typename C::iterator>
I last(C & collection, I it) requires Container<C> {
    return last(collection, it, [] (auto value) { return true; });
}


template<typename C, typename V = typename C::value_type, typename I = typename C::iterator>
I last(C & collection) requires PostInsertableContainer<C, V, I> {
    return last(collection, collection.before_begin());
}

template<typename C, typename V = typename C::value_type, typename I = typename C::iterator>
I last(C & collection) requires InsertableContainer<C, V, I> {
    return last(collection, begin(collection));
}


template<typename C, typename P, typename V = typename C::value_type, typename I = typename C::iterator>
I first(C & collection, I iterator, P predicate) requires Container<C> && Predicate<P, V> && Incrementable<I> {
    I out;
    for (iterator; iterator != end(collection); iterator++) {
        if (predicate(*iterator))
            return iterator;
    }

    return out;
}

template<typename C, typename V = typename C::value_type, typename I = typename C::iterator>
I first(C & collection, I it) requires Container<C> {
    return first(collection, it, [] (auto value) { return true; });
}


template<typename C, typename V = typename C::value_type, typename I = typename C::iterator>
I first(C & collection) requires PostInsertableContainer<C, V, I> {
    return first(collection, collection.before_begin());
}

template<typename C, typename V = typename C::value_type, typename I = typename C::iterator>
I first(C & collection) requires InsertableContainer<C, V, I> {
    return first(collection, begin(collection));
}

template<typename C, typename P, typename V = typename C::value_type, typename I = typename C::iterator>
I first(C & collection, P predicate) requires PostInsertableContainer<C> && Predicate<P, V> && Incrementable<I> {
    return first(collection, collection.before_begin(), predicate);
}

template<typename C, typename P, typename V = typename C::value_type, typename I = typename C::iterator>
I first(C & collection, P predicate) requires InsertableContainer<C> && Predicate<P, V> && Incrementable<I> {
    return first(collection, begin(collection), predicate);
}

template<typename C, typename I = typename C::iterator, typename V = typename C::value_type>
I insert(C & collection, I iterator, V value) requires Insertable<C, V, I> {
    collection.insert(iterator, value);
}

template<typename C, typename I = typename C::iterator, typename V = typename C::value_type>
I insert(C & collection, I iterator, V value) requires PostInsertable<C, V, I> {
    collection.insert_after(iterator, value);
}

template<typename C, typename P, typename V = typename C::value_type>
bool any(C & collection, P predicate) requires Container<C> && Predicate<P, V> {
    for (auto it : collection) {
        if (predicate(it))
            return true;
    }

    return false;
}


template<typename Vo, typename C, typename S, typename Vi = typename C::value_type>
C distinct(C & collection, S selector) requires InsertableContainer<C> || PostInsertableContainer<C> && Selector<S, Vo, Vi> {
    auto ret = C();

    for (auto it : collection) {
        if (find_if(ret.begin(), ret.end(), [selector, it] (auto elem) { return selector(elem) == selector(it); }) == ret.end())
            insert(ret, last(ret), it);
    }

    return ret;
}

template<typename C, typename P, typename V = typename C::value_type>
C filter(C & collection, P predicate) requires InsertableContainer<C> || PostInsertableContainer<C> && Predicate<P, V> {
    auto ret = C();
    
    for (auto it : collection) {
        if (predicate(it))
            insert(ret, last(ret), it);
    }

    return ret;
}

template<typename O, typename C, typename S, typename Vc = typename C::value_type, typename Vo = typename O::value_type>
O select(C & collection, S selector) requires InsertableContainer<O> || PostInsertableContainer<O> && Container<C> && Selector<S, Vo, Vc> {
    auto ret = O();

    for (auto it : collection)
        insert(ret, last(ret), selector(it));

    return ret;
}

#endif
