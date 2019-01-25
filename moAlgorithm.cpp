// problem : https://www.spoj.com/problems/DQUERY/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 6;

// MO's algorithm 
// Optimal block size : n/sqrt(q) - > O(n*sqrt(q))
// with block size : sqrt(n) - > O((n + q)*sqrt(n))

struct Query{
	int l, r, id;
}query[N];
int n, a[N], q, ans[N], cnt[N], len = 30, currAns;

inline bool comp(Query a, Query b){
	if(a.l/len == b.l/len)return a.r < b.r;
	return a.l < b.l;
}

inline void add(int i){
	if(cnt[a[i]] == 0)currAns++;
	cnt[a[i]]++;
}

inline void remove(int i){
	if(cnt[a[i]] == 1)currAns--;
	cnt[a[i]]--;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	for(int i=0;i<n;++i)cin>>a[i];

	cin>>q;
	for(int i=0;i<q;++i){
		cin>>query[i].l>>query[i].r;
		query[i].l--; query[i].r--;
		query[i].id = i;
	}
	sort(query, query + q, comp);

	int mo_left = 0, mo_right = -1;
	for(int i=0;i<q;++i){
		int left = query[i].l, right = query[i].r, id = query[i].id;

		while(mo_right < right){
			mo_right++; add(mo_right);
		}
		while(mo_right > right){
			remove(mo_right); mo_right--;
		}
		while(mo_left < left){
			remove(mo_left); mo_left++;
		}
		while(mo_left > left){
			mo_left--; add(mo_left);
		}
		ans[id] = currAns;
	}

	for(int i=0;i<q;++i)cout<<ans[i]<<"\n";
	return 0;
}
