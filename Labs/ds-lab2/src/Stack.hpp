#ifndef _MY_STACK_HPP_
#define _MY_STACK_HPP_
#include <cstdlib>
#include "Heap.hpp"


template<class T>
class Stack{ // 6.5-7, LIFO Stack with heap.

public:
    Stack() {
        cnt = 0;
    }
    inline void push(T val) {
        h.push((Stack_elem_t){val, cnt++});
    }
    inline void pop() {
        h.pop();
    }
    inline T top() {
        if(h.get_size() < 1)
            throw std::runtime_error("Queue is empty.");
        return h.top().data;
    }
private:
    int cnt;
    struct Stack_elem_t{
        T data;
        int idx;
        inline bool operator < (const Stack_elem_t &other) const {
            return idx > other.idx; //The only difference between a stack element and a queue element.
        }
    };
    Heap<Stack_elem_t> h;
};
#endif