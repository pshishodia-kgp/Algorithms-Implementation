/*
    A story which will never end
    A story which never began
*/

// problem : https://www.spoj.com/problems/TDKPRIME/
#include <bits/stdc++.h>

using namespace std;

#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define ll long long

const int N = 5e9;
const int M = 5e6 + 1;
const int len = sqrt(N) + 1;

vector<int> prime;
vector<int> tot;
vector<int> vis(len);

void segmentedSieve(){
    fill(vis.begin(), vis.end(), 0);
    for(int i=2;i<=len;++i)if(!vis[i]){
        prime.push_back(i);
        tot.push_back(i);
        for(int j=i;j<=len;j+=i)
            vis[j] = 1;
    }
    for(int k =1; tot.size() < M;++k){
        fill(vis.begin(), vis.end(), 0);

        int start = k*len;
        for(int p : prime){
            int start_idx = (start + p - 1)/p;
            int j = start_idx*p - start;
            for(;j < len; j += p)
                vis[j] = 1;
        }
        for(int i=0;i<len;++i)
            if(!vis[i])tot.push_back(start + i);
    }
}

int main(){
    segmentedSieve();
    int q;
    cin>>q;
    while(q--){
        int k;
        cin>>k;
        cout<<tot[k-1]<<endl;
    }

    return 0;
}
