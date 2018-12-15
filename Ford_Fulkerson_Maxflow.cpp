// problem link : https://codeforces.com/contest/1082/problem/G

#include <bits/stdc++.h>

using namespace std;

const int N = 2010;
const int inf = 1e9;

vector<int> g[N];
vector<pair<int, int> > edge[N];
int n, m, cap[N][N], a[N];
long long ans;

int bfs(int s, int t, vector<int> &parent){
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;

	queue<pair<int, int> > q;
	q.push({s, inf});

	while(!q.empty()){
		int v = q.front().first;
		int flow = q.front().second; 
		q.pop();

		for(int u : g[v])if(parent[u] == -1 && cap[v][u] > 0){
			int new_flow = min(flow, cap[v][u]);
			parent[u] = v;

			if(u == t)return new_flow;
			q.push({u, new_flow});
		}
	}
	return 0;
}

long long maxflow(int s, int t){
	long long flow = 0;
	vector<int> parent(n + m + 2);
	int new_flow = 0;

	while(new_flow = bfs(s, t, parent)){
		flow += new_flow;
		int curr = t;
		while(curr != s){
			int prev = parent[curr];
			cap[prev][curr] -= new_flow;
			cap[curr][prev] += new_flow;
			curr = prev;
		}
	}
	return flow;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;

	for(int i=1;i<=n;++i){
		cin>>a[i];
		g[0].push_back(i);
		g[i].push_back(0);
		cap[0][i] = a[i];
	}

	for(int i=1;i<=m;++i){
		int u, v, w;
		cin>>u>>v>>w;

		cap[u][n + i] = cap[v][n + i] = inf;
		g[u].push_back(n + i); g[v].push_back(n + i);
		g[n + i].push_back(u); g[n + i].push_back(v);

		cap[n + i][n + m + 1] = w;
		g[n + i].push_back(n + m + 1);
		g[n + m + 1].push_back(n + i);

		ans += w;
	}

	cout<<ans - maxflow(0, n + m + 1)<<"\n";
	return 0;
}
