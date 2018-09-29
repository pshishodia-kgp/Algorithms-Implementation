//problem Link : https://www.spoj.com/problems/SUBXOR/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e5 + 5;
const int LOG = 20;

int n, k, a[N];
struct Trie{
    Trie *child[2];
    int cnt[2];
};

void insert(Trie *root, int x){
    for(int i=LOG-1;i>=0;--i){
        if(x&(1<<i)){
            if(root->child[1] == NULL)
                root->child[1] = new Trie();
            (root->cnt[1])++;
            root = root->child[1];
        }
        else{
            if(root->child[0] == NULL)
                root->child[0] = new Trie();
            (root->cnt[0])++;
            root = root->child[0];
        }
    }
}

ll query(Trie *root, int x){
    ll ans = 0;
    for(int i=LOG -1;i>=0 && root != NULL;--i){
        if(k&(1<<i)){
            if(x & (1<<i)){
                ans += (root->cnt[1]);
                root = root->child[0];
            }
            else{
                ans += (root->cnt[0]);
                root = root->child[1];
            }
        }
        else{
            if(x & (1<<i))root = root->child[1];
            else root = root->child[0];
        }
    }
    return ans;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=0;i<n;++i)cin>>a[i];
        Trie *trie = new Trie();
        int pre = 0;
        ll ans = 0;
        insert(trie, 0);
        for(int i=0;i<n;++i){
            pre ^= a[i];
            ans += query(trie, pre);
            insert(trie, pre);
        }
        cout<<ans<<endl;
    }
    return 0;
}
