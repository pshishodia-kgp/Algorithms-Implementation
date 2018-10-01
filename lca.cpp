// problem code : https://www.spoj.com/problems/LCA/

#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int LOG = 11;

int n, p[N][LOG], level[N];

vector<int> g[N];

void initialize(){
    for(int i=0;i<n;++i)level[i] = 0;

    for(int j=0;j<LOG;++j)
        for(int i=0;i<n;++i)
            p[i][j]  = 0;
}

void dfs(int v){
    for(int i=0;i<g[v].size();++i)
        if(p[v][0] != g[v][i]){
            int u = g[v][i];
            p[u][0] = v;
            level[u] = level[v] + 1;
            dfs(u);
        }
}

void precompute(){
    for(int j=1;j<LOG;++j)
        for(int i=0;i<n;++i)
            p[i][j] = p[p[i][j-1]][j-1];
}

int lca(int u, int v){
    if(level[u] < level[v])swap(u, v);

    for(int i=LOG - 1;i>= 0;--i)
        if(level[u] - (1<<i) >= level[v]){
            u = p[u][i];
        }

    if(u == v)return u;

    for(int i=LOG-1;i>=0;--i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];

    return p[u][0];
}

int main(){
    int t;
    cin>>t;
    for(int I=1;I<=t;++I){
        cin>>n;

        for(int i=0;i<n;++i){
            int m; cin>>m;
            for(int j=0;j<m;++j){
                int x;
                cin>>x; x--;
                g[i].push_back(x);
            }
        }
        // main LCA part
        initialize();       //only when there are multiple test cases
        dfs(0);
        precompute();
        // main LCA part

        int q;
        cin>>q;
        cout<<"Case "<<I<<":"<<endl;
        while(q--){
            int u, v;
            cin>>u>>v; u--; v--;
            cout<<lca(u, v) + 1<<endl;
        }

        // clear  graph
        for(int i=0;i<n;++i)g[i].clear();       //only in case of multiple test cases
    }
    return 0;
}
