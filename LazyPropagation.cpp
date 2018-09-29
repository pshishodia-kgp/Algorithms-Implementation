// problem : http://codeforces.com/contest/242/problem/E

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'

const int N = 1e5 + 5;
const int LOG = 20;

int n, t[4*N][20][2], revert[4*N][20], m, a[N];

void build(int node, int start, int end, int id){
    if(start == end){
        (a[start]&(1<<id))? t[node][id][1] = 1 : t[node][id][0] = 1;
        return ;
    }
    int mid = (start + end)>>1;
    build(2*node, start, mid, id);
    build(2*node + 1, mid + 1, end, id);
    t[node][id][0] = t[2*node][id][0] + t[2*node + 1][id][0];
    t[node][id][1] = t[2*node][id][1] + t[2*node + 1][id][1];
}

void update(int node, int start, int end, int l, int r, int id){
    if(revert[node][id]){
        swap(t[node][id][0], t[node][id][1]);
        if(start != end){
            revert[2*node][id] = !revert[2*node][id];
            revert[2*node + 1][id] = !revert[2*node + 1][id];
        }
        revert[node][id] = 0;
    }
    if(start > r || end < l)return ;
    if(start >= l && end <= r){
        swap(t[node][id][0], t[node][id][1]);
        if(start != end){
            revert[2*node][id] = !revert[2*node][id];
            revert[2*node + 1][id] = !revert[2*node + 1][id];
        }
        return ;
    }
    int mid = (start + end)>>1;
    update(2*node, start, mid, l, r, id);
    update(2*node + 1, mid + 1, end, l, r, id);
    t[node][id][0] = t[2*node][id][0] + t[2*node + 1][id][0];
    t[node][id][1] = t[2*node][id][1] + t[2*node + 1][id][1];
}

int query(int node, int start, int end, int l, int r, int id){
    if(revert[node][id]){
        swap(t[node][id][0], t[node][id][1]);
        if(start != end){
            revert[2*node][id] = !revert[2*node][id];
            revert[2*node + 1][id] = !revert[2*node + 1][id];
        }
        revert[node][id] = 0;
    }
    if(start > r || end < l)return 0;
    if(start >= l && end <= r)return t[node][id][1];
    int mid = (start + end)>>1;
    int p1 = query(2*node, start, mid, l, r, id);
    int p2 = query(2*node + 1, mid + 1, end, l, r, id);
    return p1 + p2;
}

int main(){
    cin>>n;
    for(int i=0;i<n;++i)cin>>a[i];

    for(int i=0;i<LOG;++i)
        build(1, 0, n-1, i);
    cin>>m;
    while(m--){
        int type, l, r, x;
        cin>>type;
        if(type == 1){
            cin>>l>>r; l--; r--;
            ll sum = 0;
            for(int i=0;i<LOG;++i){
                sum += 1ll*query(1, 0, n-1, l, r, i)*(1<<i);
            }
            cout<<sum<<endl;
        }
        else{
            cin>>l>>r>>x; l--; r--;
            for(int i=0;i<LOG;++i)if(x & (1<<i)){
                update(1, 0, n-1, l, r, i);
            }
        }
    }
    return 0;
}
