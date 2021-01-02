// #define MANUAL_INPUT

#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// const int maxn = 500000005;
// No limit on maxn
mt19937 gen(19260817);

inline int read() {
    int s = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}
inline int rand(int l, int r) {
    uniform_int_distribution<> rng(l, r);
    return rng(gen);
}

inline vector<int> random_selection(int n, int k) {
    unordered_map<int, int> mp;
    for(int i = 1; i <= k; ++i) { //生成k个随机的关键下标
        if(!mp.count(i)) mp[i] = i;
        int target = rand(i, n);
        if(!mp.count(target)) mp[target] = target;
        swap(mp[i], mp[target]);
    }
    vector<int> pos, result;
    for(int i = 1; i <= k; ++i) pos.push_back(mp[i]); //存储k个关键下标
    mp.clear();
    sort(pos.begin(), pos.end()); //对关键下标进行排序
    int curpos = 0, curval;
    for(int i = 1; i <= n; ++i) {
        #ifdef MANUAL_INPUT
        curval = read();
        #else
        curval = i;
        #endif
        if(curpos < k && pos[curpos] == i) {
            result.push_back(curval); //命中关键下标，将结果储存
            ++curpos;
        }
    }
    return result;
}


int n, k;
int main() {
    n = read(), k = read();
    int time1 = clock();
    vector<int> res = random_selection(n, k);
    int time2 = clock();
    int token = 0;
    for(auto i:res) token ^= i;
    cout << "[1c] Time elapsed: " << 1000.0 * (time2 - time1) / CLOCKS_PER_SEC << "ms" << endl;
    cout << "Token=" << token << endl;
    // for(auto i:res) cout << i << endl;
}