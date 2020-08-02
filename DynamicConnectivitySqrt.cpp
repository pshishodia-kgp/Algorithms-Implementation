/*
    author : pshishod2645
    Created at : 04:37:07 PM, 01 August 2020
    Link : https://codeforces.com/problemset/problem/813/F
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;
//#define int long long 
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

/* 
* Trying naive implementation of dynamic connectivity in O( ( N + Q)* sqrt(Q))
* divide into sqrt(N) blocks, each block will be processed together.  
* store actual graph after all queries before this block in O(N) without the edges
* that will be deleted in this block. Move through the block and insert the edges that needs to be inserted.
* consider the edges that aren't deleted yet. (will form atmost sqrt(Q)) connections. 
*/

const int N = 1e5 + 5; 
vector<int> g[N];
vector<pair<int, int> > cmpG[N];  
int cmp[N] = {}, notbipar = 0, cmpVis[N] = {}, vis[N] = {}, color[N] = {}, cmpCol[N] = {}; 

struct Graph{

    Graph(int n, vector<pair<int, int> > edges){
        for(int i = 0;i < N; ++i){
            g[i].clear(); cmpG[i].clear();
            cmp[i] = cmpVis[i] = vis[i] = color[i] = cmpCol[i] = notbipar = 0; 
        }

        for(auto p: edges){
            int x = p.first, y = p.second; 
            g[x].push_back(y); g[y].push_back(x); 
        }
  
        for(int i = 1, ind = 0;i <= n; ++i)if(!vis[i])
            dfs(i, ind++); 
        // pr(edges, notbipar); 
    }

    void dfs(int v, int ind, int col = 0){
        cmp[v] = ind; vis[v] = 1; color[v] = col; 
        for(int u: g[v]){
            if(vis[u] && color[v] == color[u])notbipar = 1; 
            if(!vis[u])dfs(u, ind, col ^ 1); 
        }
    }

    bool dfs1(int v, int col = 0){
        cmpCol[v] = col, cmpVis[v] = 1; 

        for(auto p: cmpG[v]){
            int u = p.first, xr = p.second; 
            int new_col = col ^ xr; 
            if(cmpVis[u] == 1 && cmpCol[u] != new_col)return false; 
            if(!cmpVis[u] && !dfs1(u, new_col))return false; 
        }
        return true; 
    }

    bool isBipartite(vector<pair<int, int> > edges){ 
        if(notbipar)return false; 
        vector<int> vertices; 
        for(auto p: edges){
            int x = p.first, y = p.second;
            int px = cmp[x], py = cmp[y]; 
            vertices.push_back(px); vertices.push_back(py); 

            if(px == py){
                if(color[x] == color[y])return false; 
            }else{
                int xr = color[x] == color[y];  
                cmpG[px].push_back({py, xr}); cmpG[py].push_back({px, xr});
            }
        }

        bool ret = true; 
        for(int i: vertices)if(!cmpVis[i] && !dfs1(i))
            ret = false; 
        for(int i: vertices){
            cmpG[i].clear(); cmpVis[i] = 0; cmpCol[i] = 0;  
        }
        return ret; 
    }
};

inline void distinct(vector<int> &v){
    sort(all(v)); 
    v.resize(unique(all(v)) - v.begin()); 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q; cin>>n>>q; 
    int block = sqrt(q); 

    vector<pair<int, int> > edge; 
    map<pair<int, int>, int > mp; 
    vector<int> deleteEdge(q), num(q), on(q);  

    for(int i = 0;i < q; ++i){
        int x, y; cin>>x>>y; 
        if(!mp.count({x, y})){
            mp[{x, y}] = edge.size(); edge.push_back({x, y}); 
        }
        num[i] = mp[{x, y}]; 
        if(on[num[i]])deleteEdge[i] = 1; 
        on[num[i]] ^= 1; 
    }


    vector<int> prv(edge.size()); 
    for(int i = 0;i < q; i += block){
        int start = i, end = min(q, i + block);

        vector<int> ind; 
        for(int j = start; j < end; ++j)ind.push_back(num[j]); 
        distinct(ind); 

        vector<int> now = prv;
        for(int j = start;j < end; ++j)if(deleteEdge[j])now[num[j]] = 0;

        vector<pair<int, int> > prv_edges; 
        for(int i = 0;i < edge.size(); ++i)if(now[i])prv_edges.push_back(edge[i]); 

        Graph g(n, prv_edges); 

        for(int j = start; j < end; ++j){
            prv[num[j]] ^= 1; 

            vector<pair<int, int> > curr; 
            for(int k: ind)if(prv[k])curr.push_back(edge[k]); 

            g.isBipartite(curr)? cout<<"YES\n" : cout<<"NO\n"; 
        }
    }

    return 0;
}   
