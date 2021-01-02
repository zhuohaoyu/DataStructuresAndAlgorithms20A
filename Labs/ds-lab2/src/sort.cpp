#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

mt19937 gen(time(0));
inline int rand(int l, int r) { // 这里使用mt19937虽然运行效率低，但避免了c中rand()在不同平台上RAND_MAX不同造成的意外行为。
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}

template<class T>
inline int partition(T s[], int begin, int end) { // 随机确定pivot
    if(begin >= end) return begin;
    int p = rand(begin, end);
    if(end != p) swap(s[end], s[p]);
    int i = begin - 1;
    for(int j = begin; j < end; ++j) {
        if(s[j] < s[end] || s[j] == s[end]) {
            ++i;
            swap(s[j], s[i]);
        }
    }
    swap(s[i + 1], s[end]);
    return i + 1;
}

template<class T>
inline void mysort(T s[], int begin, int end) { // 闭区间[begin, end]排序
    //使用CLRS上提到的Tail-Recursive技巧，将递归树上所有右子树转为非递归，减少递归
    while(begin < end) {
        int p = partition(s, begin, end);
        mysort(s, begin, p - 1);
        begin = p + 1;
    }
}

inline bool check() {
    static int arr[100005], s1[100005], s2[100005];
    int n;
    freopen("sort.txt", "r", stdin);
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &arr[i]), s1[i] = s2[i] = arr[i];
    fclose(stdin);
    sort(&s1[1], &s1[n + 1]);
    mysort(s2, 1, n);
    for(int i = 1; i <= n; ++i) {
        if(s1[i] != s2[i]) return false;
    }
    return true;
}

int main() {
    puts(check() ? "Accepted" : "Wrong Answer");
}