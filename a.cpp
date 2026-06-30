#include <bits/stdc++.h>

#define int long long
using namespace std;



void dfs(int u, int p, vector<vector<int>> &g, vector<int> &sz){
    sz[u] = 1;
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v,u,g,sz);
        sz[u] += sz[v];
    }
}

void solve() {
    int n; cin>>n;
    vector<int> p(n);
    for(auto &x: p) cin>>x;
    vector<vector<int>> g(n);
    for(int i = 1; i < n; i++){
        int u,v; cin>>u>>v; u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> sz(n, 0);
    dfs(0, -1, g, sz);
    int ans = 0;
    for(int i = 0; i < n; i++){
        int valor = sqrtl(p[i]);
        if(valor*valor == p[i]){
            //es un cuadrado entonces combino los hijos
            vector<int> hijos;
            for(auto &x: g[i]){
                if(sz[x] < sz[i]){
                    //hijo
                    hijos.push_back(sz[x]);
                }else hijos.push_back(n - sz[i]);
            }

            // cout<<"tengo los hijos de i "<<i<<endl;
            // for(auto x: hijos){
            //     cout<<x<<" ";
            // }
            // cout<<endl;

            int tom1 = 0;
            int tom2 = 0;
            int tom3 = 0;
            //cout<<"El hijo i me esta dando "<<i<<endl;
            for(auto &x: hijos){
                tom3 = tom3 + tom2*x;
                tom2 = tom2 + tom1*x;
                tom1 += x;
            }
            //cout<<"estos tomandos 2 "<<tom2<<endl;
           /// cout<<"estos tomandos 3 "<<tom3<<endl;
            ans += tom2 + tom3;
        }
    }
    cout<<ans<<endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t; cin>>t;
    while (t--) solve();
}