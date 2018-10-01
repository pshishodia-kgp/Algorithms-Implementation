// problem : http://codeforces.com/contest/342/problem/E

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int LOG = 17;

int n, m, level[N], p[N][LOG], par[N], sub[N], ans[N], tot;
// p[i] -->parent in original tree
// par[i] --> parent in centroid decomposed tree
// tot --> total size of tree
set<int> g[N];

void dfs(int v, int prnt, int d){
    level[v] = d;
    p[v][0] = prnt;
    for(auto u : g[v])
        if(u != prnt)dfs(u, v, d + 1);
}

void preprocess(){
    dfs(0, 0, 0);
    for(int i=0;i<n;++i)
        ans[i] = 1e6;

    for(int j=1;j<LOG;++j)
        for(int i=0;i<n;++i)
            p[i][j] = p[p[i][j-1]][j-1];
}

int lca(int u, int v){
    if(level[u] < level[v])swap(u, v);

    for(int i = LOG -1;i>=0;--i)
        if(level[u] - (1<<i) >= level[v])
            u = p[u][i];

    if(u == v)return u;

    for(int i=LOG - 1;i>=0;--i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];

    return p[u][0];
}

void dfs1(int v, int prnt){
    sub[v] = 1; tot++;
    for(auto u : g[v])if(u != prnt){
        dfs1(u, v);
        sub[v] += sub[u];
    }
}

int centroid(int v, int prnt){
    for(auto u : g[v])
        if(u != prnt && sub[u] > tot/2)return centroid(u, v);

    return v;
}

void decompose(int root, int prnt){
    tot = 0;
    dfs1(root, root);
    int cntd = centroid(root, root);
    if(prnt == -1)prnt = cntd;
    par[cntd] = prnt;

    for(auto u : g[cntd]){
        g[u].erase(cntd);
        decompose(u, cntd);
    }
    g[cntd].clear();
}

int dist(int x, int y){
    return level[x] + level[y] - 2*level[lca(x, y)];
}

void update(int v){
    int x = v;
    while(1){
        ans[x] = min(ans[x], dist(x, v));
        if(x == par[x])break;
        x = par[x];
    }
}

int query(int v){
    int x = v, res = ans[v];
    while(1){
        res = min(res, dist(x, v) + ans[x]);
        if(x == par[x])break;
        x = par[x];
    }
    return res;
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n-1;++i){
        int u, v;
        cin>>u>>v; u--; v--;
        g[u].insert(v);
        g[v].insert(u);
    }

    preprocess();
    decompose(0, -1);
    update(0);
    while(m--){
        int t, v;
        cin>>t>>v; v--;
        if(t == 1)
            update(v);
        else cout<<query(v)<<endl;
    }
    return 0;
}
