#include<bits/stdc++.h>
#define int long long
using namespace std;

//numero de compoenntes del suarbol de u que contiene a u con suma s
//f[u][s]

vector<vector<int>> f;

const int MOD = 1e9+7;
void dfs(int u, int p, int k,vector<int> &pesos, vector<vector<int>> &g){
    vector<int> dp(k+1, 0);
    if(pesos[u] <= k) dp[pesos[u]] = 1; 
    
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v, u,k,pesos,g);
        vector<int> ndp(k+1, 0);
        for(int i = 0; i <=k; i++){
            if(dp[i] == 0) continue;
            ndp[i] = (ndp[i] + dp[i]) % MOD;
            for(int j = 0; j+i <=k; j++){
                ndp[i+j] = (ndp[i+j] + dp[i] * f[v][j]) % MOD;
            }
        }
        swap(dp, ndp);
    }
    for(int i = 0; i <= k; i++){
        f[u][i]  = dp[i];
    }
}



void solve(){
    int n,k; cin>>n>>k;
    vector<int> pesos(n);
    for(auto &x: pesos) cin>>x;
    vector<vector<int>> g(n);
    for(int i = 1; i < n; i++){
        int u,v; cin>>u>>v; u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f.assign(n, vector<int>(k+1, 0));
    dfs(0, -1, k, pesos, g);
    int ans = 0;
    for(int u = 0; u < n; u++){
        ans += f[u][k];
        ans %=MOD;
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--) solve();
}