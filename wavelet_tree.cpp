// follows 1-based indexing.
// solution to spoj K-Query, but gives TLE due to strict time limit.

#include <bits/stdc++.h>

using namespace std;

struct wavelet_tree{
	wavelet_tree *left, *right;
	int low, mid, high;
	vector<int> b, a;

	wavelet_tree(vector<int> &a, int lo, int hi){
		left = right = NULL;
		low = lo, high = hi;
		mid = (low + high)/2;

		this -> a = a;

		if(low == high)return;

		b.resize(a.size());
		vector<int> a1, a2;
		a1.push_back(0); a2.push_back(0);

		for(int i=1;i<a.size();++i){
			if(a[i] <= mid)a1.push_back(a[i]), b[i] = 1;
			else a2.push_back(a[i]);

			b[i] += b[i - 1];
		}

		if(a1.size() > 1)left = new wavelet_tree(a1, low, mid);
		if(a2.size() > 1)right = new wavelet_tree(a2, mid + 1, high);
	}

	int lessThanK(int l, int r, int k){
		l = max(l, 1);

		if(r <= 0 || r < l)return 0;
		int res ;
		if(low == high)res =  (low <= k)? r - l + 1 : 0;

		else if(k <= mid)res = left? left->lessThanK(b[l - 1] + 1, b[r], k) : 0;
    
		else{
		  int lessThanMid = b[r] - b[l - 1];

		  res = lessThanMid + (right? right->lessThanK(l - 1 - b[l -1] + 1, r - b[r], k) : 0);
		}
    
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin>>n;
	vector<int> a(n + 1);

	for(int i=1;i<=n;++i)cin>>a[i];

	wavelet_tree *tree = new wavelet_tree(a, 1, 1e9);

	int q; cin>>q;

	while(q--){
		int l, r, x;
		cin>>l>>r>>x;
		cout<<r - l + 1 - tree->lessThanK(l, r, x)<<"\n";
	}
	return 0;
}
