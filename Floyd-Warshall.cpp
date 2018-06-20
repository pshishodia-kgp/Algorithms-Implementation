#include <bits/stdc++.h>

using namespace std;

#define SIZE 105
#define INF 1000000000

int n,m, dis[SIZE][SIZE];

int main()
{
	scanf("%d %d", &n, &m);

	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j] = INF;         // setting the distance as infinity 
  	for(int i=1;i<=n;++i)
  	  dis[i][i] = 0;              		// graph is 1-indexed

	for(int i=0;i<m;++i)
	{
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);
		dis[x][y] = dis[y][x] = d;
	}

	for(int k=1;k<=n;++k)              	 // using intermediate verices only from the set {1, 2, 3, .. k}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			printf("%d ", dis[i][j]);
		printf("\n");
	}
	return 0;
}
