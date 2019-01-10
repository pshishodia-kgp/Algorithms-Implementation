//problem link : https://atcoder.jp/contests/dp/tasks/dp_z

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e6 + 5;
const ll INF = 1e17;
ll n, c, dp[N], h[N];

struct Line{
	ll m, c;
	Line(){
		m = c = 1e9;
	}
} t[4*N];

ll eval(Line l, int x){
	return l.m * x + l.c;
}

void addLine(int node, int start, int end, Line l){
	int mid = (start + end)/2;
	bool fleft = eval(l, start) < eval(t[node], start);
	bool fmid = eval(l, mid) < eval(t[node], mid);

	if(fmid)swap(t[node], l);
	if(start == end)return ;
	if(fleft != fmid)addLine(2*node, start, mid, l);
	else addLine(2*node + 1, mid + 1, end, l);
}

ll query(int node, int start, int end, int id){
	if(id < start || id > end)return INF;
	if(start == end)return eval(t[node], start);

	int mid = (start + end)/2;
	ll ret = min(query(2*node, start, mid, id), query(2*node + 1, mid + 1, end, id));
	return min(ret, eval(t[node], id));
}

int main(){
	cin>>n>>c;
	for(int i=1;i<=n;++i)cin>>h[i];

	Line l;
	for(int i=1;i<=n;++i){
		if(i != 1)dp[i] = (h[i]*h[i] + c) + query(1, 0, N - 1, h[i]);
		l.m = -2*h[i];
		l.c = dp[i] + h[i]*h[i];
		addLine(1, 0, N - 1, l);
	}
	cout<<dp[n]<<"\n";

	return 0;
}
