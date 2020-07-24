// const int MOD = 1e9 + 7; 
// inline int add(int a, int b){a += b; if(a >= MOD)a -= MOD; return a;}
// inline int sub(int a, int b){a -= b; if(a < 0)a += MOD; return a;}
// inline int mul(int a, int b){return (int)((long long) a * b %MOD);}

struct Matrix{
    vector<vector<int> > mat; 
    int n, m; 

    Matrix(vector<vector<int> > v){
        mat = v;  n = v.size(), m = v[0].size(); 
    }
    Matrix(int _n, int _m){
        n = _n, m = _m; mat = vector<vector<int> > (n, vector<int> (m)); 
    }
    vector<int>& operator [] (int i){
        return mat[i]; 
    }

    Matrix operator += (Matrix other){
        assert(n == other.n && m == other.m); 
        for(int i = 0;i < n; ++i)
            for(int j = 0;j < m; ++j)mat[i][j] = add(mat[i][j], other[i][j]); 
        return *this; 
    }
    Matrix operator -= (Matrix other){
        assert(n == other.n && m == other.m);  
        for(int i = 0;i < n; ++i)
            for(int j = 0;j < m; ++j)mat[i][j] = sub(mat[i][j], other[i][j]); 
        return *this; 
    }
    Matrix operator + (Matrix other){return Matrix(*this) += other; }
    Matrix operator - (Matrix other){return Matrix(*this) += other; }
    Matrix operator *= (Matrix other){
        assert(m == other.n); 
        Matrix ret(vector<vector<int> > (n, vector<int> (other.m))); 
        for(int i = 0;i < n; ++i)
            for(int j = 0;j < other.m; ++j)
                for(int k = 0;k < m; ++k)ret[i][j] = add(ret[i][j], mul(mat[i][k], other[k][j])); 
        return (*this) = ret;
    }
    Matrix operator * (Matrix other){return Matrix(*this) *= other;}
    static Matrix identity(int sz){
        vector<vector<int> > ret(sz, vector<int> (sz)); 
        for(int i = 0;i < sz; ++i)ret[i][i] = 1; 
        return Matrix(ret);  
    }
    Matrix operator ^ (int b){
        assert(n == m);
        Matrix res = identity(n), a = (*this); 
        while(b > 0){
            if(b & 1)res *= a; 
            a *= a; b /= 2; 
        }
        return res; 
    }
};
