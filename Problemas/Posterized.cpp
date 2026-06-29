#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
    int n,k; cin>>n>>k;
    vector<int> a(n); for(auto &x : a) cin>>x;
    
    vector<int> group(256, -1);
    for(int i = 0; i < n; i++){
        int x = a[i];
        if(group[x] != -1) continue;
        int y = -1; 
        int grupo = -1;
        for(int v = x-1; v >= 0; v--){
            if(group[v] != -1){
                y = v;
                grupo = group[v];
                break;
            }
        }
        if(grupo != -1 && x - grupo + 1 <= k){
            for(int v = grupo; v <= x; v++){
                group[v] = grupo;
            }
        }else{
            int nuevoG = max(y+1, x - k + 1);
            for(int v = nuevoG; v <= x; v++){
                group[v] = nuevoG;
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout<<group[a[i]]<<" ";
    }
    cout<<endl;
}