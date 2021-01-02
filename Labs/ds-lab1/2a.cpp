#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

mt19937 gen(time(0));

inline double rand(double l, double r) {
    uniform_real_distribution<> rng(l, r);
    return rng(gen);
}

// const int range_max = 1000000000;
// const long long box_range = 1ll * range_max * range_max;
// uniform_int_distribution<> rng(0, 1000000000);

inline double calculate_pi(int iterations) {
    int in = 0;
    for(int i = 0; i < iterations; ++i) {
        double x = rand(0, 1), y = rand(0, 1);
        if(x * x + y * y < 1) ++in; 
    }
    return 4.0 * in / iterations;
}


int main() {
    double minv = 1e9, maxv = -1e9;
    for(int i = 1; i <= 10; ++i) {
        double res = calculate_pi(2000000000);
        cout << fixed << setprecision(15) << res << endl;
        minv = min(minv, res);
        maxv = max(maxv, res);
    }
    cout << "Min = " << fixed << setprecision(15) << minv << endl;
    cout << "Max = "<< fixed << setprecision(15) << maxv << endl;
    cout << "Delta = " << fixed << setprecision(15) << maxv - minv << endl;
}