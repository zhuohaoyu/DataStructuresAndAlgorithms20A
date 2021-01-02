#ifndef _MY_QUEUE_HPP_
#define _MY_QUEUE_HPP_
#include "Heap.hpp"
template<class T>
class Queue{ // 6.5-7, FIFO Queue with Heap.

public:
    Queue() {
        cnt = 0;
    }
    inline void push(T val) {
        h.push((Queue_elem_t){val, cnt++});
    }
    inline void pop() {
        h.pop();
    }
    inline T front() {
        if(h.get_size() < 1)
            throw std::runtime_error("Queue is empty.");
        return h.top().data;
    }
private:
    int cnt;
    struct Queue_elem_t{
        T data;
        int idx;
        inline bool operator < (const Queue_elem_t &other) const {
            return idx < other.idx;
        }
    };
    Heap<Queue_elem_t> h;
};

#endif