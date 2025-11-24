#ifndef MY_ALGORITHMS_H
#define MY_ALGORITHMS_H

#include <utility>

namespace MySTL {

    // Linear search
    template <typename Iterator, typename T>
    Iterator find(Iterator first, Iterator last, const T& value) {
        while (first != last) {
            if (*first == value) return first;
            ++first;
        }
        return last;
    }

    // QuickSort partition
    template <typename Iterator>
    Iterator partition(Iterator low, Iterator high) {
        auto pivot = *high;
        Iterator i = low;

        for (Iterator j = low; j != high; ++j) {
            if (*j < pivot) {
                std::swap(*i, *j);
                ++i;
            }
        }
        std::swap(*i, *high);
        return i;
    }

    // QuickSort implementation
    template <typename Iterator>
    void sort(Iterator first, Iterator last) {
        if (first == last || first == last - 1) return;

        Iterator prevLast = last - 1;
        
        if (first < prevLast) {
            Iterator pi = partition(first, prevLast);
            sort(first, pi);
            sort(pi + 1, last);
        }
    }
}

#endif