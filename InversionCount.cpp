// problem : https://www.spoj.com/problems/INVCNT/

#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
 
ll invcnt = 0;
 
void merge(int a[], int l, int m, int r){
    int b[r - l + 1];
    int i = l, j = m + 1, k = 0;
 
    while(i <= m && j <= r){
        if(a[i] <= a[j])
            b[k++] = a[i++], invcnt += j - m - 1;
        else b[k++] = a[j++];
    }
 
    while(i <= m)
        b[k++] = a[i++], invcnt += j - m - 1;
 
    while(j <= r)
        b[k++] = a[j++];
 
    for(int i=l;i<=r;++i)
        a[i] = b[i-l];
}
 
void mergeSort(int a[], int l, int r){
    if(r == l)return ;
    int m = (l + r)>>1;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}
 
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n];
        for(int i=0;i<n;++i)cin>>a[i];
 
        invcnt = 0;
        mergeSort(a, 0, n-1);
        cout<<invcnt<<endl;
    }
    return 0;
}
