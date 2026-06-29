#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 1e5 + 5;

vector<int> g[MAXN];
int c[MAXN];
int dp[MAXN][2];

void dfs(int u){
    if(c[u] == 0) dp[u][0] = 1, dp[u][1] = 0;
    else dp[u][0] = 0, dp[u][1] = 1;
    
    for(int v : g[u]){
        dfs(v);
        int u0 = dp[u][0]%MOD;
        int u1 = dp[u][1]%MOD;
        int v0 = dp[v][0]%MOD;
        int v1 = dp[v][1]%MOD;
        int ndp0 = (u0*v0)%MOD;
        int ndp1 = ((u0*v1)%MOD+(u1*v0)%MOD)%MOD;
        ndp0 += u0*v1;
        ndp1 += u1*v1;
        dp[u][0] = ndp0%MOD;
        dp[u][1] = ndp1%MOD;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;
    for(int i = 1; i < n; i++){
        int p; cin>>p;
        g[p].push_back(i);
    }

    for(int i = 0; i < n; i++) cin>>c[i];

    dfs(0);
    cout<<dp[0][1]<<endl;
}