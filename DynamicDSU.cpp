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
