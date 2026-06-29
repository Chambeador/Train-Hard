#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 5005;
const int INF = 1e18;

int n,b;
int w[MAXN], d[MAXN];
vector<int> g[MAXN];
int sz[MAXN];
vector<vector<int>> f[MAXN];


void dfs(int u, int p = -1){
    sz[u] = 1;
    vector<vector<int>> dp(2, vector<int>(2, INF));
    dp[0][0] = 0;
    dp[1][0] = w[u];
    dp[1][1] = w[u]-d[u];
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v, u);
        vector<vector<int>> ndp(sz[u]+sz[v]+1, vector<int>(2, INF));
        for(int i = 0; i <= sz[u]; i++){
            for(int j = 0; j <=  sz[v]; j++){
                ndp[i+j][0] = min(ndp[i+j][0], dp[i][0]+f[v][j][0]);
                ndp[i+j][1] = min(ndp[i+j][1], dp[i][1]+ min(f[v][j][1], f[v][j][0]));
            }
        }
        sz[u]+=sz[v];
        swap(dp, ndp);
        vector<vector<int>>().swap(f[v]);
    }
    f[u].resize(sz[u] + 1, vector<int>(2, INF));
    for(int i = 0; i <= sz[u]; i++){
        f[u][i][0] = dp[i][0];
        f[u][i][1] = dp[i][1];
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>b;
    cin>>w[0]>>d[0];
    for(int i = 1; i < n; i++){
        int p; 
        cin>>w[i]>>d[i]>>p;
        p--;
        g[p].push_back(i);
    }
    dfs(0);
    int ans = 0;
    for(int k = n; k >= 0; k--){
        int costito = min(f[0][k][0], f[0][k][1]);
        if(costito <= b){
            ans = k;
            break;
        }
    }
    cout<<ans<<endl;
}