// problem : https://www.codechef.com/problems/ICPC16G

#include <bits/stdc++.h>

using namespace std;

#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define vi vector<int>

typedef complex<double> base;

const double PI = acos(-1);


void fft(vector<base> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; j++) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (base & x : a)
            x /= n;
    }
}

void multiply(vector<int> &a, vector<int> &b, vector<int> &res){
    if(a.empty())return;
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while(n < max(a.size(), b.size()) )n<<=1;
    n<<=1;
    fa.resize(n), fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for(int i=0;i<n;++i)
        fa[i]*= fb[i];

    fft(fa, true);
    res.resize(n + 1);
    for(int i=0;i<n;++i)
        res[i] = (int)(fa[i].real() + 0.5);
}

int main(){
    int n, m;
    cin>>n>>m;
    vector<int> a(n), b(n);
    for(int i=0;i<n;++i)cin>>a[i];
    for(int i=0;i<m;++i){
        int x;cin>>x;
        b[x] = 1;
    }
    vector<int> ca(2*n), cb(2*n), res;
    for(int i=0;i<n;++i)ca[i] = a[n - i - 1];
    for(int i=0;i<n;++i)cb[i] = cb[i + n] = b[i];

    multiply(ca, cb, res);
    int cnt = 0;
    for(int i=n-1;i<n - 1 + n;++i)
        if(res[i] == m)++cnt;
    cout<<cnt<<endl;
    return 0;
}
