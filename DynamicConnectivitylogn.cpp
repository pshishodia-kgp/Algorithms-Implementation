const int N = 3e5 + 5; 
namespace DCT{
    struct Edge{
        int l, r, x, y; 
    };
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

    map<pair<int, int>, int> mp; 
    vector<Edge> edge; 
    vector<pair<int, int> > t[N]; 
    int tym = 0, ans[N]; 

    inline void addEdge(int x, int y, bool op = true){ // true for add, false for delete
        if(x > y)swap(x, y); 
        if(op && mp.count({x, y}))return ;  // edge already exists, so won't add
        if(!op && !mp.count({x, y}))return; // edge doesn't exist, so can't delete

        if(op)mp[{x, y}] = ++tym; 
        else{
            edge.push_back((Edge){mp[{x, y}], (++tym) - 1, x, y}); 
            mp.erase({x, y}); 
        }
    }

    void addRemainingEdges(){
        ++tym; 
        for(auto p: mp){
            int x = p.first.first, y = p.first.second, i = p.second; 
            edge.push_back((Edge){i, tym - 1, x, y}); 
        }
    }

    void go(int l, int r, vector<Edge> allEdge){
        int now = dsu.st.size(); 
        vector<Edge> down; 
        for(auto e: allEdge){
            if(l > e.r || r < e.l){}
            else if(l >= e.l && r <= e.r)dsu.merge(e.x, e.y);
            else down.push_back(e); 
        }

        if(l == r){
            ans[l] = cmp;
        }else{
            int m = (l + r)/2; 
            go(l, m, down); go(m + 1, r, down); 
        }
        dsu.rollback(now);
    }

    void solve(){
        addRemainingEdges();
        go(0, tym, edge); 
    }
};
