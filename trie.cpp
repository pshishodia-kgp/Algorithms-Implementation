// code for problem 
// http://codeforces.com/contest/271/problem/D
//http://codeforces.com/problemset/problem/282/E

#include <bits/stdc++.h>

using namespace std;

#define ll long long 

struct trie
{
	trie *child[26];

	trie()
	{
		for(int i=0;i<26;++i)
			child[i] = NULL;
	}
};

int n, k;
string s, good;

void insert(trie *root, int i)
{
	for(; i<n;++i)
	{
		int pos = s[i] - 'a';
		if(root->child[pos] == NULL)
			root->child[pos] = new trie;
		root = root->child[pos];
	}
}

ll count(trie *root, int m)
{
	if(m < 0)return 0;
	ll res = 1;
	for(int i=0;i<26;++i)
		if(root->child[i] != NULL)
		{
			if(good[i] == '1')
				res += count(root->child[i], m);
			else res += count(root->child[i], m -1);
		}
	return res;
}

int main()
{
	cin>>s;
	cin>>good;
	cin>>k;
	n = s.size();

	trie *t = new trie;

	for(int i=0;i<n;++i)
		insert(t, i);
	cout<<count(t, k) - 1<<endl;
	return 0;
}
