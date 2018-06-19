#include <bits/stdc++.h>

using namespace std;

#define SIZE 1000
#define LOG 10

int p[SIZE][10];
int level[SIZE];
vector<int> g[SIZE];

void dfs(int v, int parent, int d)
{
	level[v] = d;
	p[v][0] = parent;
	for(int i=0;i<g[v].size();++i)
		if(level[g[v][i]] == -1)
			dfs(g[v][i], v, d+1);
}

int lca(int u, int v)
{
	if(level[u] < level[v])
		swap(u,v);

	for(int i=LOG;i>=0;--i)
		if(level[u] - (1<<i) >= level[v])
			u = p[u][i];
	if(u==v)
		return u;

	for(int i=LOG;i>=0;--i)
		if(p[u][i]!=-1 && p[u][i] != p[v][i])
		{
			u = p[u][i];
			v = p[v][i];
		}
	return p[u][0];
}

int main()
{
	int t;
	cin>>t;
	for(int I=1;I<=t;++I)
	{
		int n;
		cin>>n;
		for(int i=0;i<SIZE;++i)
		{
			level[i] = -1;
			g[i].clear();
		}

		for(int i=0;i<SIZE;++i)
			for(int j=0;j<=LOG;++j)
				p[i][j] = -1;


		for(int i=0;i<n;++i)
		{
			int m;
			cin>>m;
			for(int j=0;j<m;++j)
			{
				int x; cin>>x; x--;
				g[i].push_back(x);
				g[x].push_back(i);
			}
		}
    
		dfs(0,-1,0);
    
		for(int j=1; (1<<j) < n; ++j)
			for(int i=0;i<n;++i)
			{
				if(p[i][j-1]!=-1)
					p[i][j] = p[p[i][j-1]][j-1];
			}

		int q;
		cin>>q;
		cout<<"Case "<<I<<":"<<endl;
		while(q--)
		{
			int v, w;
			cin>>v>>w; v--; w--;
			cout<<lca(v,w)+1<<endl;;
		}
	}
	return 0;
}
