---
tags:
  - 双指针
  - 算法
Difficulty:
  - Unknown
---
# 链接




```cpp
#include <bits/stdc++.h>  
using namespace std;  
#define int long long  
#define detristy ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);  
  
constexpr int N = 1e5+10;  
int n;  
  
int mex(vector<int> a,int l,int r) {  
    bitset<N> bs;  
    for (int i = l ; i <= r ; i++) {  
        bs[a[i]] = true;  
  
    int res = 0;  
    while (bs[res]) res++;  
    return res;  
}  
  
void solve() {  
    int idx1 = -1, idx2 = -1,ans = 0;  
    cin >> n;  
    vector<int> v(2*n+5);  
    for (int i = 1 ; i <= n*2 ; i++) {  
        cin >> v[i];  
        if (v[i] == 0) {  
            if (idx1 == -1) idx1 = i;  
            else idx2 = i;  
        }  
    }  
    int l = idx1, r = idx1;  
    while (l > 1 && r < 2*n && v[l-1] == v[r+1]) l--, r++;  
    ans = max(ans,mex(v,l,r));  
    l = idx2, r = idx2;  
    while (l > 1 && r < 2*n && v[l-1] == v[r+1]) l--, r++;  
    ans = max(ans,mex(v,l,r));  
    l = min(idx1,idx2);  
    r = max(idx1,idx2);  
    int l2 = l,r2 = r;  
    bool flag = true;  
    while (l <= r) {  
        if (v[l] != v[r]) {  
            flag = false;  
            break;  
        }  
        l++,r--;  
    }  
    if (flag) {  
        while (l2 > 1 && r2 < 2*n && v[l2-1] == v[r2+1]) l2--, r2++;  
        ans = max(ans,mex(v,l2,r2));  
    }  
    cout << ans << '\n';  
}  
  
signed main() {  
    detristy  
    int T = 1;  
    cin >> T;  
    while (T--) solve();  
    return 0;  
}
```