/* 
  Problem Link : https://agc002.contest.atcoder.jp/tasks/agc002_d
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int p[N], size[N], n, m, q, x[N], y[N], z[N], low[N], high[N];
vector<pair<int, int> > edge; 

void init(){
    for(int i=0;i<N;++i)p[i] = i, size[i] = 1; 
}

int root(int x){
    if(x != p[x])
        p[x] = root(p[x]); 
    return p[x]; 
}

void merge(int x, int y){
    x = root(x), y = root(y); 
    if(x == y)return ; 
    if(size[x] < size[y])swap(x, y); 
    p[y] = x; size[x] += size[y]; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>m;
    for(int i=0;i<m;++i){
        int x, y; cin>>x>>y; 
        edge.push_back({x, y}); 
    }
    cin>>q; 
    for(int i=0;i<q; ++i){
        cin>>x[i]>>y[i]>>z[i];
        high[i] = m - 1; low[i] = -1; 
    }

    while(1){
        vector<int> check[m]; 
        bool end = true;  
        for(int i=0;i<q;++i)if(high[i] - low[i] > 1){
            end = false;
            int mid = (low[i] + high[i])/2;
            check[mid].push_back(i);
        }
        if(end)break;

        init(); 
        for(int i=0;i<m;++i){
            merge(edge[i].first, edge[i].second); 

            for(int id : check[i]){
                int val; 
                if(root(x[id]) != root(y[id]))val = size[root(x[id])] + size[root(y[id])]; 
                else val = size[root(x[id])]; 

                (val >= z[id])? high[id] = i : low[id] = i; 
            }
        }
    }
    for(int i=0;i<q;++i)cout<<high[i] + 1<<"\n";
    return 0;
}
