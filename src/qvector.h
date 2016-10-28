#ifndef qvector_H
#define qvector_H

#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>

template <class T>
class qvector : public std::vector<T> {
    public:
        qvector<T> where(std::function<bool (T)> filter) {
            qvector<T> ret;

            for (auto it = this->begin(); it != this->end(); it++) {
                if (filter(*it))
                    ret.push_back(*it);
            }

            return ret;
        }

        T first(std::function<bool (T)> filter) {
            for (auto it = this->begin(); it != this->end(); it++) {
                if (filter(*it))
                    return *it;
            }

            throw std::runtime_error("Item not found!");
        }

        T last(std::function<bool (T)> filter) {
            for (auto it = this->end; it != this->begin(); it--) {
                if (filter(*it))
                    return *it;
            }

            throw std::exception("Item not found!");
        }

        bool any(std::function<bool (T)> filter) {
            for (auto it = this->begin(); it != this->end(); it++) {
                if (filter(*it))
                    return true;
            }

            return false;
        }

        template <class X>
        qvector<T> distinct(std::function<X (T)> property) {
            auto ret = qvector<T>();

            for (auto it = this->begin(); it != this->end(); it++) {
                if (!ret.any([&it, &property] (auto o) { return property(o) == property(*it); }))
                    ret.push_back(*it);
            }

            return ret;
        }
};

#endif
