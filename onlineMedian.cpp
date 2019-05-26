// problem link : https://atcoder.jp/contests/abc127/tasks/abc127_f

#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
const ll MOD = 1e9 + 7;
#define cerr cout
#define sz(a) (ll)((a).size())
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
inline ll add(ll a, ll b){a += b; if(a >= MOD)a -= MOD; return a;}
inline ll sub(ll a, ll b){a -= b; if(a < 0)a += MOD; return a;}
inline ll mul(ll a, ll b){return (ll)((long long) a * b %MOD);}
inline ll binpow(ll a, ll b){ll res = 1; while(b > 0){ if(b & 1)res = mul(res, a); a = mul(a, a);b /= 2;} return res;}
inline ll inv(ll a){return binpow(a, MOD - 2);}
ll gcd(ll a, ll b, ll &x, ll &y){if(a == 0){x = 0, y = 1; return b;} ll x1, y1;  ll d = gcd(b%a, a, x1, y1); x = y1 - (b/a) * x1; y = x1; return d;}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	ll q; cin>>q; 
	priority_queue<ll> left; 
	priority_queue<ll ,vector<ll>, greater<ll>> right; 

	ll constant = 0, sum_left = 0, sum_right =0; 
	while(q--){
		ll t; cin>>t;
		if(t == 1){
			ll a, b; cin>>a>>b; 
			constant += b; 
			if(right.empty() || a < right.top())left.push(a), sum_left += a; 
			else{
				ll top = right.top(); right.pop(); 
				right.push(a); sum_right += a - top; 
				left.push(top); sum_left += top; 
			}
			if((ll)left.size() - (ll)right.size() > 1){
				ll top = left.top(); left.pop(); sum_left -= top; 
				right.push(top); sum_right += top; 
			}
		}else if(t == 2){
			ll less = (ll)left.size(), great = (ll)right.size(); 
			ll val = left.top(); 
			cout<<val<<" "<<less*val - sum_left + sum_right - great*val + constant<<"\n"; 
		}
	}

    return 0;
