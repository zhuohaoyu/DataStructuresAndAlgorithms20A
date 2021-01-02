class Solution { // Leetcode 406
public:
    struct data{
        int v, r;
        inline bool operator < (const data &b) { 
            return v == b.v ? r < b.r : v > b.v;
        }
    };
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<data> ppl;
        ppl.resize(people.size());
        for(int i = 0; i < ppl.size(); ++i) 
            ppl[i].v = people[i][0], ppl[i].r = people[i][1];    
        sort(ppl.begin(), ppl.end());
        for(int i = 1; i < ppl.size(); ++i) {
            data cur = ppl[i];
            for(int j = i - 1; j >= cur.r; --j) {
                ppl[j + 1] = ppl[j];
            }
            if(cur.r < i) ppl[cur.r] = cur;
        }
        for(int i = 0; i < ppl.size(); ++i) 
            people[i][0] = ppl[i].v, people[i][1] = ppl[i].r;
        return people;
    }
};