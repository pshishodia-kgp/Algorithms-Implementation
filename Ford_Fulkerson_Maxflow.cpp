// problem link : https://codeforces.com/contest/1082/problem/G

#include <bits/stdc++.h>

using namespace std;

const int N = 2010;
const int inf = 1e9;

int n, m, a[N];
long long ans;

struct fordFulkerson{
	int n, source, sink;
	vector<int> parent;
	vector<vector<int> > cap, g;

	fordFulkerson(int size){
		n = size;
		parent = vector<int> (n + 1);
		cap = vector<vector<int > > (n + 1, vector<int>(n + 1));
		g = vector<vector<int> > (n + 1);
	}

	void addEdge(int u, int v, int w){
		g[u].push_back(v);
		g[v].push_back(u);
		cap[u][v] = w;
	}

	long long maxflow(){
		long long flow = 0, new_flow = 0;

		while(new_flow = bfs()){
			flow += new_flow;
			
			int curr = sink;
			while(curr != source){
				int prev = parent[curr];
				cap[prev][curr] -= new_flow;
				cap[curr][prev] += new_flow;
				curr = prev;
			}
		}
		return flow;
	}

	int bfs(){
		fill(parent.begin(), parent.end(), -1);
		parent[source] = -2;

		queue<pair<int, int> > q;

		q.push({source, inf});

		while(!q.empty()){
			int v = q.front().first;
			int flow = q.front().second; q.pop();

			for(int u : g[v])if(parent[u] == -1 && cap[v][u] > 0){
				int new_flow = min(flow, cap[v][u]);
				parent[u] = v;

				if(u == sink)return new_flow;
				q.push({u, new_flow});
			}
		}
		return 0;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;

	fordFulkerson flow(n + m + 2);

	for(int i=1;i<=n;++i){
		cin>>a[i];
		flow.addEdge(0, i, a[i]);
	}

	for(int i=1;i<=m;++i){
		int u, v, w;
		cin>>u>>v>>w;

		flow.addEdge(u, n + i, inf); flow.addEdge(v, n + i, inf);
		flow.addEdge(n + i, n + m + 1, w);

		ans += w;
	}

	flow.source = 0; flow.sink = n + m + 1;
	cout<<ans - flow.maxflow()<<"\n";
	return 0;
}
