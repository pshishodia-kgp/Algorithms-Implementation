// problem : http://codeforces.com/contest/383/problem/C

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, level[N], st[N], en[N], cnt, a[N];
vector<int> g[N];

struct segment{
    int t[4*N];
    void update(int node, int start, int end, int l, int r, int val);
    int query(int node, int start, int end, int i);
};

void segment :: update(int node, int start, int end, int l, int r, int val){
    if(end < l || start > r || end < start)return ;
    if(start >= l && end <= r){
        t[node] += val;
        return ;
    }
    int mid = (start + end)/2;
    update(2*node, start, mid, l, r, val);
    update(2*node + 1, mid + 1, end, l, r, val);
}

int segment :: query(int node, int start, int end, int i){
    if(end < i || start > i || end < start)
        return 0;
    if(start == end)return t[node];
    int mid = (start + end)/2;
    return t[node] + query(2*node, start, mid, i) + query(2*node + 1, mid + 1, end, i);
}

void dfs(int v, int prnt, int d){
    level[v] = d;
    st[v] = cnt++;
    for(int u : g[v])
        if(u != prnt)dfs(u, v, d + 1);

    en[v] = cnt - 1;
}

int main(){
    segment seg0, seg1;
    cin>>n>>m;
    for(int i=0;i<n;++i)
        cin>>a[i];
    for(int i=0;i<n-1;++i){
        int u, v;
        cin>>u>>v; u--; v--;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(0, 0, 0);

    while(m--){
        int t, x, val;
        cin>>t>>x; x--;
        if(t == 1){
            cin>>val;
            if(level[x]%2 == 1){
                seg1.update(1, 0, n-1, st[x], en[x], val);
                seg0.update(1, 0, n-1, st[x], en[x], -1*val);
            }
            else{
                seg0.update(1, 0, n-1, st[x], en[x], val);
                seg1.update(1, 0, n-1, st[x], en[x], -1*val);
            }
        }
        else{
            if(level[x]%2 == 1)
                cout<<a[x] + seg1.query(1, 0, n-1, st[x])<<endl;
            else cout<<a[x] + seg0.query(1, 0, n-1, st[x])<<endl;
        }
    }
    return 0;
}
