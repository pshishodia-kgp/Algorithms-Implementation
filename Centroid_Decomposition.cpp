// problem : http://codeforces.com/contest/342/problem/E
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;
#define cerr cout
#define sz(a) (int)((a).size())
#define all(x) (x).begin(), (x).end()
string to_string(string s) { return '"' + s + '"';}
string to_string(char s) { return string(1, s);}
string to_string(const char* s) { return to_string((string) s);}
string to_string(bool b) { return (b ? "true" : "false");}
template <typename A> string to_string(A);
template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}
template <typename A> string to_string(A v) {bool f = 1; string r = "{"; for (const auto &x : v) {if (!f)r += ", "; f = 0; r += to_string(x);} return r + "}";}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {cerr << " " << to_string(H); debug_out(T...);}
#define pr(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
inline int add(int a, int b){a += b; if(a >= MOD)a -= MOD; return a;}
inline int sub(int a, int b){a -= b; if(a < 0)a += MOD; return a;}
inline int mul(int a, int b){return (int)((long long) a * b %MOD);}
inline int binpow(int a, int b){int res = 1; while(b > 0){ if(b & 1)res = mul(res, a); a = mul(a, a);b /= 2;} return res;}
inline int inv(int a){return binpow(a, MOD - 2);}
int gcd(int a, int b, int &x, int &y){if(a == 0){x = 0, y = 1; return b;} int x1, y1;  int d = gcd(b%a, a, x1, y1); x = y1 - (b/a) * x1; y = x1; return d;}

const int N = 1e5 + 5, INF = 1e9; 
const int LOG = 20; 
int n, m, par_cent[N], subSize[N], level[N], ans[N], par[N][LOG]; 
set<int> g[N];  

/********************Tree************************/ 

void dfs(int v, int prnt = 0, int d = 0){
    par[v][0] = prnt; level[v] = d; 
    for(int j = 1;j < LOG; ++j)par[v][j] = par[par[v][j - 1]][j - 1]; 

    for(int u : g[v])if(u != prnt)
        dfs(u, v, d + 1); 
}

int lca(int x, int y){
    if(level[x] < level[y])swap(x, y); 

    for(int j = LOG - 1;j >= 0; --j)if(level[x] - (1<<j) >= level[y])
        x = par[x][j]; 

    if(x == y)return x; 

    for(int j = LOG - 1; j >= 0; --j)if(par[x][j] != par[y][j])
        x = par[x][j], y = par[y][j]; 
    return par[x][0]; 
}

int dist(int x, int y){
    int mlca = lca(x, y); 
    return level[x] + level[y] - 2*level[mlca]; 
}

/*****************Decompose **************/ 
int sz; 

void dfs1(int v, int prnt = 0){
    subSize[v] = 1; 
    for(int u : g[v])if(u != prnt){
        dfs1(u, v); 
        subSize[v] += subSize[u]; 
    }
}

int find_centroid(int v, int prnt = 0){
    for(int u : g[v])if(u != prnt && subSize[u] > sz/2)
        return find_centroid(u, v); 
    return v; 
}

void decompose(int v, int prnt = 0){
    dfs1(v); 
    sz = subSize[v]; 
    int centroid = find_centroid(v); 
    par_cent[centroid] = prnt; 

    for(int u : g[centroid]){
        g[u].erase(centroid); 
        decompose(u, centroid); 
    }

    g[centroid].clear(); 
}

/**********Handle Queries*******************/ 

void update(int v){
    int x = v; 
    while(x){
        ans[x] = min(ans[x], dist(x, v)); 
        x = par_cent[x]; 
    }
}

int query(int v){
    int x = v, ret = n; 
    while(x){
        ret = min(ret, ans[x] + dist(x, v)); 
        x = par_cent[x]; 
    }
    return ret; 
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>m; 
    for(int i = 0;i < n - 1; ++i){
        int x, y; cin>>x>>y;
        g[x].insert(y); g[y].insert(x); 
    }

    dfs(1); 
    decompose(1); 

    fill(ans, ans + N, INF); 
    update(1); 
    while(m--){
        int tp, v; cin>>tp>>v; 
        if(tp == 1)update(v); 
        else cout<<query(v)<<"\n"; 
    }

    return 0;
}
