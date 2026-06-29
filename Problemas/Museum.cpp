#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 10005;
const long long INF = 4e18;

int n, k, x;
vector<pair<int,int>> g[MAXN];
int sz[MAXN];
int f[MAXN][MAXN][2];
//f[u][k][0]
// costo minimo para el subArbol u visitar k salas y no volver a u
//f[u][k][1]
// costo minimo para el subArbol u visitar k salas y volver a u

void dfs(int u, int p){
    sz[u] = 1;
    vector<vector<int>> dp(2, vector<int> (2, INF));
    //dp[i][x] es costo minimo para visitar i salar
    dp[1][0] = 0;
    dp[1][1] = 0;
    for(auto &[v, ww]: g[u]){
        if(v == p) continue;
        dfs(v, u);
        vector<vector<int>> ndp(sz[u]+sz[v]+1, vector<int> (2, INF));
        for(int i = 1; i <= sz[u]; i++){
            ndp[i][0] = min(ndp[i][0], dp[i][0]);
            ndp[i][1] = min(ndp[i][1], dp[i][1]);
            for(int j = 1; j <= sz[v]; j++){
                ndp[i+j][0] = min(ndp[i+j][0], dp[i][0] + f[v][j][1]+ 2*ww);
                ndp[i+j][0] = min(ndp[i+j][0], dp[i][1] + f[v][j][0]+ww);
                ndp[i+j][1] = min(ndp[i+j][1], dp[i][1] + f[v][j][1]+2*ww);
            }
        }
        sz[u]+=sz[v];
        swap(dp, ndp);
    }
    for(int i = 1; i <= sz[u]; i++){
        f[u][i][0] = dp[i][0];
        f[u][i][1] = dp[i][1];
    }
}

void solve(){
    cin>>n>>k>>x;
    x--;
    for(int i = 1; i < n; i++){
        int a,b,c; cin>>a>>b>>c; a--,b--;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    dfs(x, -1);
    cout<<min(f[x][k][0], f[x][k][1])<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}