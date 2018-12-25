//problem url : https://www.spoj.com/problems/TAXI/

#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

struct dinicFlow{
	struct edge{
		int x, y, cap, flow;
	};
	vector<edge> e;
	vector<int> curr, d;
	vector<vector<int> > g;
	int n, source, sink;

	dinicFlow(int n){
		this->n = n;
		curr = d = vector<int> (n + 1);
		g = vector<vector<int> > (n + 1);
	}

	void addEdge(int from, int to, int cap){
		edge e1 = {from, to, cap, 0};
		edge e2 = {to, from, 0, 0};
		g[from].push_back(e.size()); e.push_back(e1);
		g[to].push_back(e.size()); e.push_back(e2);
	}

	bool bfs(){
		fill(d.begin(), d.end(), -1);
		queue<int> q; 
		q.push(source); d[source] = 0;

		while(!q.empty()){
			int v = q.front(); q.pop();

			for(int id : g[v]){
				int u = e[id].y;
				if(d[u] < 0 && e[id].flow < e[id].cap){
					q.push(u); d[u] = d[v] + 1;
				}
			}
		}
		return d[sink] >= 0;
	}

	int dfs(int v, int flow){
		if(!flow)return 0;
		if(v == sink)return flow;

		for(; curr[v] < g[v].size(); ++curr[v]){
			int id = g[v][curr[v]]; int u = e[id].y;
			if(d[u] != d[v] + 1)continue;
			int pushed = dfs(u, min(flow, e[id].cap - e[id].flow));

			if(pushed){
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}

	long long maxflow(int src, int sink){
		this->source = src; this->sink = sink;
		long long flow = 0;
		while(bfs()){
			for(int i=0;i<=n;++i)curr[i] = 0;
			while(int new_flow = dfs(source, inf))
				flow += new_flow;
		}
		return flow;
	}
};

int main(){
	int test; cin>>test;
	while(test--){
		int p, t, s, c;
		cin>>p>>t>>s>>c;

		dinicFlow flow(p + t + 2);
		flow.source = 0; flow.sink = p + t + 1;

		vector<int> perx(p + 1), pery(p + 1), taxix(t + 1), taxiy(t + 1);
		for(int i=1;i<=p;++i)cin>>perx[i]>>pery[i];
		for(int i=1;i<=t;++i)cin>>taxix[i]>>taxiy[i];

		for(int i=1;i<=p;++i)
			for(int j=1;j<=t;++j){
				long long dist = abs(perx[i] - taxix[j]) + abs(pery[i] - taxiy[j]); 
				if(dist*200 <= s*c)flow.addEdge(i, j + p, 1);
			}

		for(int i=1;i<=p;++i)flow.addEdge(0, i, 1);
		for(int i=1;i<=t;++i)flow.addEdge(p + i, p + t + 1, 1);

		cout<<flow.maxflow(0, p + t + 1)<<"\n";
	}
	return 0;
}
