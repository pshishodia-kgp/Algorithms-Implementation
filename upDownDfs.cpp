/* 
Problem Link : https://codeforces.com/contest/1156/problem/D
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;
int n, dp[N][2]; 

vector<pair<int, int> > g[N]; 

void basic_dfs(int v, int prnt){
    for(auto p : g[v]){
        int u = p.first, c = p.second; 
        if(u == prnt)continue;

        basic_dfs(u, v); 
        if(c == 0) dp[v][0] += 1 + dp[u][0] + dp[u][1];
        else dp[v][1] += 1 + dp[u][1]; 
    }
}

void parental_dfs(int v, int prnt){
    for(auto p : g[v]){
        int u = p.first, c = p.second;
        if(u == prnt)continue;

        if(c == 0)dp[u][0] += 1 + dp[v][0] + dp[v][1] - (1 + dp[u][0] + dp[u][1]);
        else dp[u][1] += 1 + dp[v][1] - (1 + dp[u][1]); 
        parental_dfs(u, v);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=0;i<n-1;++i){
        int u, v, c; cin>>u>>v>>c; 
        g[u].push_back({v, c}); 
        g[v].push_back({u, c}); 
    }
    basic_dfs(1, 0);
    parental_dfs(1, 0);

    ll ans = 0;
    for(int i=1;i<=n;++i){
        ans += dp[i][0] + dp[i][1];
    }
    cout<<ans<<"\n";
    return 0;
}
