// https://www.spoj.com/problems/QTREE/

#include <bits/stdc++.h>
 
using namespace std;
 
#define X first 
#define Y second 
#define mp make_pair
#define MAX(x, y) (((x) > (y))? (x) : (y))
 
const int N = 20000;
 
int n, heavy[N], root[N], p[N];
int pos[N], num[N], depth[N], t[6*N], a[N], b[N], vtx[N];
 
vector<pair<int, pair<int, int> > > g[N];
 
int dfs(int v = 0, int prnt = -1, int d = 0)
{
	int size = 1, maxsize = 0;
	depth[v] = d;
	p[v] = prnt;
	for(int i=0;i<g[v].size();++i)
	{
		int u = g[v][i].X;
		int c = g[v][i].Y.X , idx = g[v][i].Y.Y;
		if(u != prnt)
		{
			int subsize = dfs(u, v, d + 1);
			if(subsize > maxsize)
			{
				maxsize = subsize;
				heavy[v] = u;
			}
			vtx[idx] = u;
			size += subsize;
			a[u] = c;
		}
	}
	return size;
}
 
void hld()
{
	for(int i=0, currpos = 0; i < n; ++i)
		if(p[i] == -1 || heavy[p[i]] != i)
			for(int j = i; j != -1; j = heavy[j])
			{
				root[j] = i;
				num[j] = currpos; b[currpos] = a[j];
				currpos++;
			}
}
 
void build(int node, int start, int end)
{
	if(start == end)
	{
		t[node] = b[start];
		return ;
	}
	int mid = (start + end)/2;
	build(2*node, start, mid);
	build(2*node + 1, mid + 1, end);
	t[node] = (t[2*node] > t[2*node + 1]) ? t[2*node] : t[2*node + 1];
}
 
int query(int node, int start, int end, int l, int r)
{
	if(end < l  || start > r)
		return 0;
	if(start >= l && end <= r)
		return t[node];
	int mid = (start + end)/2;
	int p1 = query(2*node, start, mid, l, r);
	int p2 = query(2*node + 1, mid + 1, end, l, r);
	return (p1 > p2 ? p1 : p2);
}
 
void update(int node, int start, int end, int idx, int val)
{
	if(start == end)
	{
		t[node] = b[start] = val;
		return ;
	}
	int mid = (start + end)/2;
	if(idx <= mid)update(2*node, start, mid, idx, val);
	else update(2*node + 1, mid + 1, end, idx, val);
	t[node] = t[2*node] > t[2*node + 1] ? t[2*node] : t[2*node + 1];
}
 
int find(int a, int b)
{
	int res = 0;
	while(root[a] != root[b])
	{
		if(depth[root[a]] < depth[root[b]])
			swap(a, b);
		res = MAX(res, query(1, 0, n-1, num[root[a]], num[a]));
		a = p[root[a]];
	}
	if(depth[a] > depth[b])
		swap(a, b);
	res = MAX(res, query(1, 0, n-1, num[a] + 1, num[b]));
	return res;
}
 
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i=0;i<n -1;++i)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			g[a].push_back(mp(b, mp(c, i) ) );
			g[b].push_back(mp(a, mp(c, i) ) );
		}
		for(int i=0;i<n;++i)
			heavy[i] = -1;
		a[0] = 0;
		dfs(0); hld(); build(1, 0, n-1);
		while(1)
		{
			char s[10];
			scanf("%s", s);
			if(s[0] == 'D')break;
			else if(s[0] == 'C')
			{
				int i, ti;
				scanf("%d %d", &i, &ti); i--;
				update(1, 0, n-1, num[vtx[i]], ti);
			}
			else
			{
				int a, b;
				scanf("%d %d", &a, &b); a--; b--;
				printf("%d\n", find(a, b));
			}
		}
		for(int i=0;i<n;++i)
			g[i].clear();
	}
	return 0;
}
