#ifndef HeaderMatch_H
#define HeaderMatch_H

template <class T>
class HeaderMatch {
    public:
        HeaderMatch<T>() {};
        HeaderMatch(T cheader, long coffset) {
            header = cheader;
            offset = coffset;
        }

        T header;
        long offset;
};

#endif
