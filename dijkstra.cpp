/*
    A story which will never end
    A story which never began
*/
// problem : http://codeforces.com/contest/1064/problem/D

#include <bits/stdc++.h>

using namespace std;

#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define ll long long
#define pii pair<int, pair<int, int> >

const int N = 2005;
int n, m, r, c, lmax, rmax, a[N][N], dis[N][N], res;
string s[N];

void dijkstra(){
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)dis[i][j] = 2e9;

    priority_queue<pii, vector<pii>, greater<pii> > q;
    dis[r][c] = 0;
    q.push({0, {r, c}});
    while(!q.empty() ){
        auto p = q.top(); q.pop();
        int x = p.second.first, y = p.second.second, w = dis[x][y];
        //maintatin vis[x][y], though it's needed in this problem
        
        if(a[x + 1][y]  && w < dis[x + 1][y])dis[x + 1][y] = w, q.push({w, {x + 1, y}});
        if(a[x - 1][y]  && w < dis[x - 1][y])dis[x - 1][y] = w, q.push({w, {x - 1, y}});
        if(a[x][y + 1]  && w < dis[x][y + 1])dis[x][y + 1] = w, q.push({w, {x, y + 1}});
        if(a[x][y - 1]  && w + 1 < dis[x][y -1])dis[x][y - 1] = w + 1, q.push({w + 1, {x, y - 1}});
    }

    int res = 0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(dis[i][j] <= lmax && dis[i][j] + j - c <= rmax)res++;

    cout<<res<<endl;
}

int main(){
    IOS;
    cin>>n>>m;
    cin>>r>>c;
    cin>>lmax>>rmax;
    for(int i=0;i<n;++i)cin>>s[i];

    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)if(s[i][j] == '.')
            a[i + 1][j + 1] = 1;

    dijkstra();
    return 0;
}
