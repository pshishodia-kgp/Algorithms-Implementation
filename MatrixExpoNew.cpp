#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define llu unsigned long long
#define ld long double
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define pf push_front
#define pii pair<int, int>
#define pll pair<ll, ll>
#define mp make_pair
#define ff first
#define ss second
#define endl '\n'
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define fill(x,v) fill(all(x), v)
#define sumv(v) accumulate(all(v), 0LL)
#define bitcount(x) __builtin_popcount(x)
#define present(v,x) ((v).find(x) != (v).end())
#define cpresent(v,x) (find(all(v),x) != (v).end())
#define v2(type, v, n, m) vector<vector<type>> v(n, vector<type>(m))
#define v3(type, v, x, y, z) vector<vector<vector<type>>> v(x, vector<vector<type>>(y, vector<type>(z)))
#define unique(v) {sort(all(v)); v.resize(unique(all(v))-v.begin());}

const int MOD = 1000000007;
// const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const double EPS = 1e-6;

#define cerr cout
string to_string(string s) { return '"' + s + '"';}
string to_string(char s) { return string(1, s);}
string to_string(const char* s) { return to_string((string) s);}
string to_string(bool b) { return (b ? "true" : "false");}
string to_string(_Bit_reference b) { return (b ? "true" : "false");}
void debug_out() { cerr << ""; }
template <typename A> string to_string(A);
template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}
template <typename A> string to_string(A v) {bool f = 1; string r = "{"; for (const auto &x : v) {if (!f)r += ", "; f = 0; r += to_string(x);} return r + "}";}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {cerr << " " << to_string(H); debug_out(T...);}
#define pr(v, n) {for(int j=0; j<n; j++){debug_out(v[j]); if(j<n-1) cerr<<",";}}
#define dbg(...) {cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__); { cerr << endl; }}
#define dbg1d(v, n) {cerr << "[" << #v << "]: {"; pr(v, n); {cerr << " }" << endl;}}
#define dbg2d(v, n, m) {cerr<<"["<<#v<<"]:"<<endl;{for(int i=0; i<n; i++){cerr<<right<<setw(10)<<"["+to_string(i)+"] {";pr(v[i],m);{cerr<<" }"<<endl;}}}}
#define shout()  {cerr << "I'm Here...!!!" << endl;}

inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = (n%p) * (n%p) % p;} return r;}
inline int inv(ll a, int p = MOD) {return fpow(a, p - 2, p);}
inline int addmod(int a, int val, int p = MOD) {{if ((a = (a + val)) >= p) a -= p;} return a;}
inline int submod(int a, int val, int p = MOD) {{if ((a = (a - val)) < 0) a += p;}return a;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

struct Matrix{
	vector<vector<int>> x;
	int n, m, MODD;
	Matrix(int rows, int cols, int MD=MOD){
		x.resize(rows, vector<int>(cols));
		n = rows;
		m = cols;
		MODD = MD;
	}
	void operator = (vector<vector<int>> r){
		x = r;
	}
	void operator = (Matrix R){
		if(make_pair(n, m)!=R.size()){
			cerr << "Unidentical Matrices cannot be added." << endl;
			exit(-1);
		}
		for(int i=0; i<n; i++) x[i] = R[i];
	}
	vector<int>& operator [] (int r){
		return x[r];
	}
	Matrix unit(){
		if(n!=m){
			cerr << "Not a Square Matrix." << endl;
			exit(-1);
		}
		Matrix res(n, n, MODD);
		for(int i=0; i<n; i++) res[i][i] = 1;
		return res;
	}
	Matrix operator + (Matrix B){
		if(make_pair(n, m)!=B.size()){
			cerr << "Unidentical Matrices cannot be added." << endl;
			exit(-1);
		}
		Matrix res(n, m, MODD);
		for(int i=0; i<n; i++) for(int j=0; j<m; j++){
			res[i][j] = x[i][j] + B[i][j];
			if(res[i][j]>=MODD) res[i][j] -= MODD;
		}
		return res;
	}
	Matrix operator * (Matrix B){
		if(m!=B.size().ff){
			cerr << "Matrices cannot Be Multiplied" << endl;
			exit(-1);
		}
		int rows = n;
		int cols = B.size().ss;
		Matrix res(rows, cols, MODD);
		for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) for(int k=0; k<m; k++)
			res[i][j] = (res[i][j] + (long long)x[i][k]*B[k][j])%MODD;
		return res;
	}
	Matrix operator ^ (long long k){
		if(n!=m){
			cerr << "Not a Square Matrix." << endl;
			exit(-1);
		}
		if(k==0) return unit();
		Matrix res(n, n, MODD), tmp(n, n, MODD);
		for(int i=0; i<n; i++) for(int j=0; j<n; j++)
			res[i][j] = tmp[i][j] = x[i][j];
		k--;
		while(k){
			if(k&1) res = res*tmp;
			tmp = tmp*tmp; k >>= 1;
		}
		return res;
	}
	public:
		pair<int, int> size(){
			return {n, m};
		}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll n, f[3], c;
	cin >> n >> f[0] >> f[1] >> f[2] >> c;

	for(int i=0; i<3; i++)
		f[i] = mult(f[i], fpow(c, i+1));

	Matrix M(3, 3, MOD-1);
	M = {	{1, 1, 1},
			{1, 0, 0},
			{0, 1, 0}};

	M = M^(n-3);

	int res = 1;
	for(int i=0; i<3; i++)
		res = mult(res, fpow(f[i], M[0][2-i]));
	res = mult(res, inv(fpow(c, n)));

	cout << res << endl;

	return 0;
}
