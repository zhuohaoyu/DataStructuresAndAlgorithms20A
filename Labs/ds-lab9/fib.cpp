#include "fib.hpp"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;
map<int, node*> mp;
int main() {
    init();
    Fibonacci_Heap h;
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) {
        int op;
        cerr << "Command #" << i << ":";
        cin >> op;
        string command;
        if(op == 1) { //insert
            int x; cin >> x;
            mp[i] = fibHeapInsert(h, x);
            command = "Insert " + to_string(x);
        }
        if(op == 2) { // extract-min
            int x = fibHeapExtractMin(h);
            cout << x << endl;
            command = "Extract-Min, result = " + to_string(x);
        }
        if(op == 3) { //decrease-key
            int x, y; cin >> x >> y;
            if(!mp.count(x)) throw std::runtime_error("Invalid timestamp.");
            command = "Decrease-Key " + to_string(mp[x]->val) + "   =>   " + to_string(y); 
            fibHeapDecreaseKey(h, mp[x], y);
        }
        dottify(h, "fib", command + ", H.n = " + to_string(h.n));
        // system("sleep 2s");
    }
}