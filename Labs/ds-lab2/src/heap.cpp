#include <iostream>
#include <vector>
#include <cstdio>
#include "Heap.hpp"
using namespace std;

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}

int main() { //洛谷 P3378 https://www.luogu.com.cn/problem/P3378
    int n = read();
    Heap<int> h;
    while(n--) {
        int op = read();
        if(op == 1) {
            int x = read();
            h.push(x);
        }
        else if(op == 2) {
            cout << h.top() << endl;
        }
        else if(op == 3) {
            h.pop();
        }
    }
}