#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}


#include "Queue.hpp"
#include <queue>
inline void check_queue() { //测试队列是否与STL队列行为一致
    Queue<int> q;
    queue<int> sysq;
    freopen("heap.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        int op;
        scanf("%d", &op);
        if(op == 1) { //插入元素
            int x;
            scanf("%d", &x);
            q.push(x);
            sysq.push(x);
        }
        else if(op == 2) { //删除元素
            q.pop();
            sysq.pop();
        }
        else{
            if(q.front() != sysq.front()) { //查询操作，比较两队列是否有相同输出
                printf("Failed queue test.\n");
                return;
            }
        }
    }
    printf("Passed queue test.\n");
    fclose(stdin);
}

#include "Stack.hpp"
#include <stack>
inline void check_stack() { //测试栈是否与STL栈一致，方法、格式同上
    Stack<int> st;
    stack<int> sysst;
    freopen("heap.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int x;
            scanf("%d", &x);
            st.push(x);
            sysst.push(x);
        }
        else if(op == 2) {
            st.pop();
            sysst.pop();
        }
        else{
            if(st.top() != sysst.top()) {
                printf("Failed stack test.\n");
                return;
            }
        }
    }
    printf("Passed stack test.\n");
    fclose(stdin);
}

int main() {
    check_queue();
    check_stack();
}