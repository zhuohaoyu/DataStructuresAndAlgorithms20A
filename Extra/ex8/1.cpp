


double FractionalKnapsack(int L, int R, double weight) {
    if(weight <= 0) return 0;
    if(L == R) return item[L].avg * min(weight, item[L].weight);
    int p = select(L, R);
    double curweight = 0, curvalue = 0;
    for(int i = p; i <= R; ++i) {
        curweight += item[i].weight;
        curvalue += item[i].value;
    }
    if(curweight <= weight) return curvalue + FractionalKnapsack(L, p - 1, weight - curweight);
    else return FractionalKnapsack(L, p - 1, weight);
}