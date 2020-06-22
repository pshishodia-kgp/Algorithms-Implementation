namespace FFT{
    typedef complex<double> base;
    const double PI = acos(-1);
    void fft(vector<base> & a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)j ^= bit;
            j ^= bit;
 
            if (i < j)
                swap(a[i], a[j]);
        }
 
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            base wlen(cos(ang), sin(ang));
            for (int i = 0, len2 = len/2; i < n; i += len) {
                base w(1);
                for (int j = 0; j < len2; j++) {
                    base u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }
 
        if (invert) {
            for (base &x : a)
                x /= n;
        }
    }
 
    vector<int> mul(vector<int> &a, vector<int> &b){
        vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
 
        int n = 1;
        while(n < a.size() + b.size())n<<=1;
        fa.resize(n), fb.resize(n);
 
        fft(fa, false); fft(fb, false);
 
        for(int i=0;i<n;++i)fa[i] *= fb[i];
 
        fft(fa, true);
 
        vector<int> ret(n); 
        for(int i = 0;i < n; ++i)
            ret[i] = (int)(fa[i].real() + 0.5);
        return ret; 
    }
}
