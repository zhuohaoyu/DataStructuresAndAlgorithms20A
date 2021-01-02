#ifndef _MY_HEAP_HPP_
#define _MY_HEAP_HPP_
#include <vector>
#include <exception>
#include <cstdlib>
using namespace std;

template<class T>
class Heap{ // 最小堆

public:
    Heap() {
        data.resize(1);
        size = 0;
    }
    Heap(vector<T> src) {
        make_heap(src);
    }
    inline void push(T val) { //加入一个值为val的元素
        data.push_back(val);
        ++size;
        for(int i = size, j = i >> 1; j > 0; i = j, j = j >> 1) { // j是i的父节点
            if(data[i] < data[j]) swap(data[i], data[j]);
            else break;
        }
    }
    inline void pop() { //弹出堆中最小元素
        if(size < 1) //堆为空
            throw std::runtime_error("Heap is empty.");
        swap(data[1], data[size]);
        data.pop_back();
        --size;
        min_heapify(1);
    }
    inline const T top() const {//查询堆中最小元素
        if(size < 1) 
            throw std::runtime_error("Heap is empty.");
        return data[1];
    }
    inline void decrease_key(T key, int val) { //data[key] -= val
        if(size < key) 
            throw std::out_of_range("Key is out of range.");
        data[key] -= val;
        for(int i = key, j = i >> 1; j > 0; i = j, j = i >> 1) {
            if(data[i] < data[j]) swap(data[i], data[j]);
            else break;
        }
    }   
    inline T extract_min() {//查询堆中最小元素并删除
        if(size < 1) 
            throw std::runtime_error("Heap is empty.");
        T ret = top();
        pop();
        return ret;
    }
    inline void make_heap(vector<T> src) {//从一个无序数组src构建一个堆
        data = src;
        size = data.size();
        for(int i = size >> 1; i >= 1; --i) 
            min_heapify(i);
    }
    inline size_t get_size() {
        return size;
    }

private:
    vector<T> data;
    size_t size;
    inline void min_heapify(int pos) {//从下向上维护堆性质
        for(int i = pos, j = i << 1; j <= size; i = j, j = i << 1) {
            if((j | 1) <= size && data[j | 1] < data[j]) 
                j |= 1; //如果有右儿子而且右儿子更小，选择右儿子
            if(data[j] < data[i]) swap(data[j], data[i]);
            else break;
        }
    }
};

#endif