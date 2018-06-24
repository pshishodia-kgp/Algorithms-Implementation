#include <bits/stdc++.h>
 
using namespace std;
 
#define X first 
#define Y second
#define mp make_pair
#define pii pair<int, int> 
#define SIZE 100005
 
int n, m, p[SIZE], mrank[SIZE];
pair<int, pii > e[SIZE];
 
int root(int x)
{
	if(x != p[x])
		p[x] = root(p[x]);
	return p[x];
}
 
void munion(int x, int y)
{
	int px = root(x);
	int py = root(y);
 
	if(mrank[px] > mrank[py])
		p[py] = px;
	else
		p[px] = py;
	if(mrank[px] == mrank[py])mrank[py]++;
}
 
long long int kruskal()
{
	long long int mincost = 0;
	for(int i=0;i<m;++i)
	{
		int u = e[i].Y.X;
		int v = e[i].Y.Y;
		int w = e[i].X;
		if(root(u) != root(v))
		{
			munion(u, v);
			mincost = mincost + w;
		}
	}
	return mincost;
}
 
int main()
{
 
	scanf("%d %d", &n, &m);
	for(int i=0;i<n;++i)
	{
		p[i] = i; mrank[i] = 0;
	}
	for(int i=0;i<m;++i)
	{
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w); x--; y--;
		e[i] = mp(w, mp(x, y));
	}
	sort(e, e + m);
	long long int res = kruskal();
	printf("%lld\n", res);
	return 0;
} 
