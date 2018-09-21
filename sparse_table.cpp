// problem : https://www.spoj.com/problems/RMQSQ/

#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
 
const int N = 1e5 + 5;
ll s[N][21], a[N];
 
int main(){
    IOS;
    int n;
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>a[i];
        s[i][0] = a[i];
    }
    //sparse table
    for(int j=1;j<=20;++j)
        for(int i = 0;i + (1<<j) - 1 < n;++i)
            s[i][j] = min(s[i][j-1], s[i + (1<<(j-1))][j-1]);
 
 
    int q;
    cin>>q;
    while(q--){
        int i, j;
        cin>>i>>j;
        int k = log2(j-i + 1);
        ll res = 1e12;
        for(ll k = 20;k>=0;--k){
            if(i + (1<<k) -1 <= j){
                res = min(res, s[i][k]);
                i += (1<<k);
            }
        }
        cout<<res<<endl;
    }
    return 0;
}
 
