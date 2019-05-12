/*
    A story which will never end
    A story which never began
*/
/*  PRoblem link : https://www.codechef.com/OCT18A/problems/BBRICKS/ */ 

#include <bits/stdc++.h>

using namespace std;

#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define ll long long

const ll num = 1e9 + 7;

const int N = 2100;

ll dp[N][N];

ll inv(ll a, ll b = num - 2){
    ll res = 1;
    while(b > 0){
        if(b & 1)res = (res *a)%num;
        b >>= 1;
        a = (a * a)%num;
    }
    return res;
}

ll lagrangeInterpolation(vector<int> &y, ll x){
//    for(int i=0;i<y.size();++i)
//        cout<<y[i]<<" ";
//    cout<<endl;
    ll ans = 0;
    ll k = 1;
    int n = y.size();
    for(int i = 2;i<y.size();++i){

        k = (k * (x - i))%num;
        k = (k * inv(1 - i))%num;
    }
    for(int i=1;i<y.size();++i){
        ans = (ans + y[i]*k)%num;

        if(i + 1 >= y.size())break;

        k = ( (( k * (x - i) ) %num)  * inv(x - i - 1) ) %num;

        k = (k * inv(i))%num;
        k = (k * (-1) * (n - 1 - i))%num;

    }
    ans = (ans + num)%num;
    return ans;
}

int main(){

    for(int i=1;i<N;++i)dp[i][0] = 1;
    dp[1][1] = 2; dp[2][1] = 4; dp[2][2] = 2;

    for(int i=3;i<N;++i)
        for(int j=1;j<N;++j)
            dp[i][j] = (dp[i-1][j] + dp[i-1][j-1] + dp[i-2][j-1])%num;

    int t;
    cin>>t;
    while(t--){
        int n, k;
        cin>>n>>k;

        if(n < N){
            cout<<dp[n][k]<<endl;
            continue;
        }

        vector<int> v;v.push_back(0);
        for(int i=k + 1;i<=2*k + 1;++i)
            v.push_back(dp[i][k]);

        cout<<lagrangeInterpolation(v, n - k)<<endl;

//        cout<<dp[n][k]<<endl;
    }
    return 0;
}
