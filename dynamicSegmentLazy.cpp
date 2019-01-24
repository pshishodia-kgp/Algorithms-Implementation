#include <bits/stdc++.h>

using namespace std;

#define ll long long

// range sum query
// problem link : https://www.spoj.com/problems/HORRIBLE/

const int N = 1e5 + 10;

struct Node{
	Node *left, *right;
	ll data, lazy;
	Node (){
		left = right = NULL;
		data = lazy = 0;
	}
};

void update(Node *node, int start, int end, int l, int r, int v){
	if(!node->left)node->left = new Node();
	if(!node->right)node->right = new Node();

	if(node->lazy != 0){
		node->data += 1ll*(end - start + 1)*(node->lazy);
		if(start != end){
			node->left->lazy += node->lazy;
			node->right->lazy += node->lazy;
		}
		node->lazy = 0;
	}

	if(start > r || end < l)return;

	if(start >= l && end <= r){
		node->data += 1ll*(end - start + 1)*v;
		if(start != end){
			node->left->lazy += v;
			node->right->lazy += v;
		}
		// cout<<"start end data "<<start<<" "<<end<<" "<<node->data<<"\n";
		return ;
	}

	int mid = (start + end)/2;
	update(node->left, start, mid, l, r, v);
	update(node->right, mid + 1, end, l, r, v);

	node->data = node->left->data + node->right->data;
}

ll query(Node *node, int start, int end, int l, int r){
	if(start > r || end < l)return 0;
	if(!node->left)node->left = new Node();
	if(!node->right)node->right = new Node();

	if(node->lazy != 0){
		node->data += 1ll*(end - start + 1)*node->lazy;
		if(start != end){
			node->left->lazy += node->lazy;
			node->right->lazy += node->lazy;
		}
		node->lazy = 0;
	}
	if(start >= l && end <= r){
		// cout<<"query start end data "<<start<<" "<<end<<" "<<node->data<<"\n";;
		return node->data;
	}

	int mid = (start + end)/2;
	ll p1 = query(node->left, start, mid, l, r);
	ll p2 = query(node->right, mid + 1, end, l, r);
	return p1 + p2;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T; cin>>T;
	while(T--){
		int n, q;
		cin>>n>>q;

		Node *root = new Node();
		while(q--){
			int t, l, r, v;
			cin>>t>>l>>r;
			if(t == 0){
				cin>>v; 
				update(root, 0, N, l, r, v);
			}
			else{
				cout<<query(root, 0, N, l, r)<<"\n";
			}
		}
	}
	return 0;
}
