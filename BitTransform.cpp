namespace BitTransform{
  void Transform(vector<int> &a, bool invert){
    int n = a.size(); 
    for(int len = 2; len <= n; len <<= 1){
      int len2 = len/2; 
      for(int i = 0;i < n; i += len)
        for(int j = 0;j < len2; ++j){
          int &u = a[i + j], &v = a[i + j + len2]; 
          tie(u, v) = 
          invert? {v - u, u} : {u, u + v};      // AND
          // invert? {u, u - v} : {u + v, u};   //OR
          // {u + v, u - v}                     //XOR
        }
    }
    // if(invert)for(int &x : a)x/= n;  // XOR only
  }

  vector<int> conv(vector<int> a, vector<int> &b){
    Transform(a, false); Transform(b, false); 
    for(int i = 0;i < a.size(); ++i)a[i] *= b[i]; 
    Transform(a, true);
    return a; 
  }
}
