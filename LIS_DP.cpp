// This code is for longest non-decreasing sequence
// For longest increasing sequence just replace '>=' in LIS() by '>'
// Time complexity is O(n^2)
// A better solution with O(nlogn) exists with binary search or segment tree (or BIT Tree)

// Problem Link : http://codeforces.com/problemset/problem/269/B

#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

int n, m, a[N];
double x[N];

int LIS()
{
	int dp[N] = {0};
	int lis = 0;
	for(int i=0;i<n;++i)
	{
		dp[i] = 1;
		for(int j=0;j<i;++j)
			if(a[j] <= a[i])
				dp[i] = max(dp[i], 1 + dp[j]);
		lis = max(dp[i], lis);
	}
	return lis;
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;++i)
		cin>>a[i]>>x[i];

	cout<<n - LIS()<<endl;
	return 0;
}
