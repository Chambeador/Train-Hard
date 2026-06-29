#include<bits/stdc++.h>
#define int long long
using namespace std;


vector<vector<int>> salto;
vector<int> peso;
void dfs(int u, vector<vector<int>>&g, vector<multiset<int>> &h, int p = -1){
    if(p == -1) salto[u][0] = u;
    else{
        salto[u][0] = p;
        h[p].insert(peso[u]);    
    }
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v, g, h,u);
    }
}

void solve(){
    int n,q; cin>>n>>q;
    vector<vector<int>> g(n);
    vector<multiset<int>> hijos(n);
    peso.resize(n);
    for(auto &x: peso) cin>>x;
    for(int i = 1; i < n; i++){
        int u,v; cin>>u>>v; u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    salto.resize(n, vector<int>(23));
    dfs(0, g, hijos);
    auto build = [&](){
        for(int i = 1; i < 23; i++){
            for(int u = 0; u < n; u++){
                salto[u][i] = salto[salto[u][i-1]][i-1];
            }
        }
    };
    build();
    while(q--){
        int t; cin>>t;
        if(t == 1){
            int u,w; cin>>u>>w; u--;
            //binary lifting para encontrar el primer mayor?
            if(peso[u] >= w){
                cout<<u+1<<endl;
                continue;
            }
            int act = u;
            for(int i = 22; i >= 0; i--){
                int ancestro = salto[act][i];
                if(peso[ancestro] < w){
                    act = ancestro;
                }
            }
            act = salto[act][0];
            if(peso[act] >= w){
                cout<<act+1<<"\n"; 
            }else{
                cout<<-1<<"\n";    
            }
        }else{
            int x,v; cin>>x>>v; x--;
            bool b = 1;
            if(salto[x][0] != x && peso[salto[x][0]] < peso[x]+v){
                b = 0;
            }
            if(b){
                if(!hijos[x].empty() && peso[x]+v < *hijos[x].rbegin()){
                    b = 0;
                }
            }

            if(b){
                int p = salto[x][0];
                if(p != x){
                    hijos[p].erase(hijos[p].find(peso[x]));
                    hijos[p].insert(peso[x]+v);
                }
                peso[x] += v;
            }

            cout<<(b? "SUCCESS": "FAILED")<<"\n";
        }
    }

}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--)
    solve();
}