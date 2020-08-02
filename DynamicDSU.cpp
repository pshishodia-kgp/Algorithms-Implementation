int cmp; 

struct DynamicDSU{
    vector<int> p, sz; 
    stack<int> st;  

    DynamicDSU(int n){
        p = sz = vector<int> (n);
        for(int i = 0;i < n; ++i)p[i] = i, sz[i] = 1; 
    }
    inline int root(int x){
        while(x != p[x])x = p[x];      // no path compression
        return p[x]; 
    }
    inline void merge(int x, int y){
        x = root(x), y = root(y);  
        if(x == y)return ; 
        if(sz[x] < sz[y])swap(x, y); 
        p[y] = x; sz[x] += sz[y]; 
        cmp--; st.push(y); // y is connected to p[y]
    }
    inline void rollback(){
        int y = st.top(), x = p[y]; 
        sz[x] -= sz[y]; p[y] = y; 
        st.pop(); cmp++; 
    }
    void rollback(int upto){
        while(st.size() > upto)rollback(); 
    }
}dsu(N);

struct DynamicDSUBipartite{
    vector<int> p, sz, parity;  
    stack<int> st, notBP;  

    DynamicDSU(int n){
        parity = p = sz = vector<int> (n); st.push(-1); notBP.push(0); 
        for(int i = 0;i < n; ++i)p[i] = i, sz[i] = 1; 
    }
    inline pair<int, int> root(int x){
        int d = 0; 
        while(x != p[x])d^= parity[x], x = p[x];      // no path compression
        return {p[x], d}; 
    }
    inline void merge(int x, int y){
        auto px = root(x), py = root(y);  
        x = px.first, y = py.first; 
        if(x == y){
            if(px.second == py.second){
                st.push(x); notBP.push(1); 
            }
            return ;
        } 
        if(sz[x] < sz[y])swap(x, y); 
        p[y] = x; sz[x] += sz[y]; parity[y] = px.second ^ py.second ^ 1; 
        st.push(y); notBP.push(notBP.top()); // y is connected to p[y]
    }
    inline void rollback(){
        int y = st.top(), x = p[y]; st.pop(); notBP.pop();
        if(y == x)return ; 
        sz[x] -= sz[y]; p[y] = y; parity[y] = 1; 
    }
    void rollback(int upto){
        while(st.size() > upto)rollback(); 
    }
}dsu(N);
