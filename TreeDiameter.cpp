// problem : https://www.spoj.com/problems/PT07Z/

#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, dp1[N], dp2[N];
// dp1 -> stores maximum diameter in subtree
// dp2 -> stores maximum height in subtree
vector<int> g[N];

void dfs(int v, int prnt = -1){
    int a = 0, b = 0;

    for(int u : g[v])if(u != prnt){
        dfs(u, v);
        dp1[v] = max(dp1[v], dp1[u]);

        if(dp2[u] > b)b = dp2[u];
        if(b > a)swap(a, b);
    }
    dp2[v] = 1 + a;
    dp1[v] = max(dp1[v], a + b + 1);
}

int main(){
    cin>>n;
    for(int i=0;i<n-1;++i){
        int u, v;
        cin>>u>>v; u--; v--;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(0, 0);
    cout<<dp1[0] - 1<<endl;
}
