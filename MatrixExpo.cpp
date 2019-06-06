// problem link : https://codeforces.com/problemset/problem/1117/D
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;
#define cerr cout
#define sz(a) (int)((a).size())
#define all(x) (x).begin(), (x).end()
string to_string(string s) { return '"' + s + '"';}
string to_string(char s) { return string(1, s);}
string to_string(const char* s) { return to_string((string) s);}
string to_string(bool b) { return (b ? "true" : "false");}
template <typename A> string to_string(A);
template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}
template <typename A> string to_string(A v) {bool f = 1; string r = "{"; for (const auto &x : v) {if (!f)r += ", "; f = 0; r += to_string(x);} return r + "}";}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {cerr << " " << to_string(H); debug_out(T...);}
#define pr(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
inline int add(int a, int b){a += b; if(a >= MOD)a -= MOD; return a;}
inline int sub(int a, int b){a -= b; if(a < 0)a += MOD; return a;}
inline int mul(int a, int b){return (int)((long long) a * b %MOD);}
inline int binpow(int a, int b){int res = 1; while(b > 0){ if(b & 1)res = mul(res, a); a = mul(a, a);b /= 2;} return res;}
inline int inv(int a){return binpow(a, MOD - 2);}
int gcd(int a, int b, int &x, int &y){if(a == 0){x = 0, y = 1; return b;} int x1, y1;  int d = gcd(b%a, a, x1, y1); x = y1 - (b/a) * x1; y = x1; return d;}

const int M = 105;
int n, m; 

void mul(int a[M][M], int b[M][M], int res[M][M]){
	int temp[M][M]; memset(temp, 0, sizeof temp); 

	for(int i = 0;i <m;++i)
		for(int j=0;j<m;++j)
			for(int k=0;k<m;++k)
				temp[i][j] = add(temp[i][j], mul(a[i][k], b[k][j])); 
	
	for(int i=0;i<m;++i)
		for(int j=0;j<m;++j)res[i][j] = temp[i][j]; 
}

void binpow(int mat[M][M], int res[M][M], int b){
	while(b > 0){
		if(b & 1)mul(res, mat, res); 
		mul(mat, mat, mat); 
		b/= 2; 	
	}
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	cin>>n>>m;
	int mat[M][M], res[M][M]; 
	memset(mat, 0, sizeof mat); 
	memset(res, 0, sizeof res); 

	mat[0][0] = mat[m - 1][0] = 1; 
	for(int i=1;i<m;++i)mat[i - 1][i] = 1; 

	// res is identity
	for(int i=0;i<m;++i)res[i][i] = 1; 

	binpow(mat, res, n - (m - 1));
	int ans = 0; 
	for(int i=0;i<m;++i)ans = add(ans, res[i][0]); 
	cout<<ans<<"\n";  

    return 0;
}
