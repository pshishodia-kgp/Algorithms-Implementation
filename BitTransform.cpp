namespace BitTransform{
  void Transform(vector<int> &a, bool invert){
    int n = a.size(); 
    for(int len = 2; len <= n; len <<= 1){
      int len2 = len/2; 
      for(int i = 0;i < n; i += len)
        for(int j = 0;j < len2; ++j){
          int &u = a[i + j], &v = a[i + j + len2]; 
          tie(u, v) = 
            // invert? make_pair(v - u, u) : make_pair(u, u + v);   // AND
            // invert? make_pair(u, u - v) : make_pair(u + v, u);   //OR
            make_pair(u + v, u - v);                     //XOR
        }
    }
    if(invert)for(int &x : a)x /= n;  // XOR only
  }

  vector<int> conv(vector<int> a, vector<int> b){
    Transform(a, false); Transform(b, false); 
    for(int i = 0;i < a.size(); ++i)a[i] *= b[i]; 
    Transform(a, true);
    return a; 
  }
}
