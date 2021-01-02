#include <bits/stdc++.h>
using namespace std;
int main() {
    int js = 0;
    cout << "Compiling source files..." << endl;
    system("g++ data_generator.cpp -o data -O2 -w");
    system("g++ kth_element.cpp -o 1 -O2 -w");
    system("g++ randomized_kth_element.cpp -o 2 -O2 -w");
    int cases = 100;
    for(int i = 1; i <= cases; ++i) {
        cout << "Case #" << i << ' ';
        system("./data");
        system("./1 < data.in > 1.out");
        system("./2 < data.in > 2.out");
        if(system("diff 1.out 2.out")) {
            cout << "Failed";
            break;
        }
        else cout << "...Passed" << endl;
    }
    cout << "Cleaning up";
    system("rm *.in *.out 1 2 data");
}