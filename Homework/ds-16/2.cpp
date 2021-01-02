class Solution {// Leetcode 1383
public:
    struct data {
        int s, e;
        inline bool operator < (const data &b) const { 
            return e > b.e;
        }
    };
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<data> d;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < n; ++i) {
            d.push_back((data){speed[i], efficiency[i]});
        }
        sort(d.begin(), d.end());
        long long ans = 0, curs = 0;
        int csz = 0;
        for(int i = 0; i < n; ++i) {
            if(csz == k) {
                int c = pq.top();
                curs -= c;
                pq.pop(), --csz;
            }
            pq.push(d[i].s), curs += d[i].s, ++csz;
            ans = max(ans, curs * d[i].e);
        }
        return ans % 1000000007;
    }
};