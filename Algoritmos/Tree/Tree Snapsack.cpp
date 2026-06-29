#include <bits/stdc++.h>
#define int long long
using namespace std;


const int MAXN = 1005;
const int MAXK = 105;

vector<int> g[MAXN];
int f[MAXN][MAXK];
int sz[MAXN];
int K;

void dfs(int u, int p){
    vector<int> dp(sz[u]+1, 0);
    dp[1] = 1;
    sz[u] = 1;
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v, u);
        vector<int> ndp(sz[u]+1, 0);
        for(int i = 1; i <= K; i++){
            if(dp[i] == 0) continue;
            ndp[i] += dp[i];
            for(int j = 1; j+i <= K; j++){
                ndp[i+j] += dp[i]*f[v][j];
            }
        }
        dp = ndp;
    }
    for(int i = 1; i <= K; i++){
        f[u][i] = dp[i];
    }
}


signed main(){
    int n,m;
    cin>>n>>m;
    cin>>K;
    for(int i = 0; i < m; i++){
        int u,v; cin>>u>>v; u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, -1);
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int k = 0; k <= K; k++){
            ans += f[i][k];
        }
    }
    cout<<ans<<endl;
}