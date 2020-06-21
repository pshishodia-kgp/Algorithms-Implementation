namespace NTT{
    // const int MOD = 998244353;   // = 7 * 17 * 2^23 + 1, 2^22 = 4e6
    const int PRIMITIVE_ROOT = 3, PRIMITIVE_ROOT_1 = inv(PRIMITIVE_ROOT); 

    void NTT(vector<int> &a, bool invert){
        int n = a.size();
        for(int i = 1, j = 0; i < n; ++i){          // precalculate reverse permutation
            int pw = n>>1; 
            for(; j & pw; pw >>= 1)j^= pw;
            j^= pw; 
            if(i < j)swap(a[i], a[j]); 
        }

        for(int len = 2; len <= n; len <<= 1){
            int wn = binpow(invert? PRIMITIVE_ROOT_1 : PRIMITIVE_ROOT, (MOD - 1)/len), len2 = len/2; // precalculate powers

            for(int i = 0;i < n; i += len){
                int w = 1                           // use precalculated powers
                for(int j = 0; j < len2; ++j){
                    int u = a[i + j], v = 1ll * a[i + j + len2] * w % MOD; 
                    a[i + j] = (u + v >= MOD)? u + v - MOD : u + v; 
                    a[i + j + len2] = (u - v < 0)? u - v + MOD : u - v;  
                    w = 1ll * w * wn % MOD; 
                }
            }
        }
        if(invert){
            int inv_n = inv(n); 
            for(int &x : a)x = 1ll * x * inv_n % MOD; 
        }
    }

    vector<int> mul(vector<int> a, vector<int> b){
        int n = 1; 
        while(n < a.size() + b.size())n <<= 1; 
        a.resize(n); b.resize(n); 

        NTT(a, false); NTT(b, false); 
        for(int i = 0;i < n; ++i)a[i] = 1ll * a[i] * b[i] % MOD; 

        NTT(a, true); 
        return a; 
    }
}
