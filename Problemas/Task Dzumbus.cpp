#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1005;
const long long INF = 4e18;

int n, m, q;
int d[MAXN];
vector<int> g[MAXN];

int sz[MAXN];
int f[MAXN][MAXN][2];

void dfs(int u, int p){

    sz[u] = 1;

    vector<vector<int>> dp(2, vector<int>(2, INF));
    vector<vector<int>> ndp;

    dp[0][0] = 0;       // no elijo u
    dp[1][1] = d[u];    // elijo u

    for(int v : g[u]){
        if(v == p) continue;

        dfs(v, u);

        ndp.assign(2, vector<int>(sz[u] + sz[v] + 1, INF));

        for(int i = 0; i <= sz[u]; i++){
            for(int j = 0; j <= sz[v]; j++){

                // u NO elegido
                ndp[0][i + j] = min(ndp[0][i + j],
                    dp[0][i] + min(f[v][j][0], f[v][j][1])
                );

                // u elegido (solo acumulas costos)
                ndp[1][i + j] = min(ndp[1][i + j],
                    dp[1][i] + f[v][j][0]
                );

                ndp[1][i + j] = min(ndp[1][i + j],
                    dp[1][i] + f[v][j][1]
                );
            }
        }

        sz[u] += sz[v];
        dp = ndp;
    }

    for(int i = 0; i <= sz[u]; i++){
        f[u][i][0] = dp[0][i];
        f[u][i][1] = dp[1][i];
    }
}

void solve(){
    cin >> n >> m;

    for(int i = 1; i <= n; i++) cin >> d[i];

    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cin >> q;

    dfs(1, -1);

    while(q--){
        int S;
        cin >> S;

        int ans = 0;

        for(int k = 0; k <= n; k++){
            int best = min(f[1][k][0], f[1][k][1]);
            if(best <= S) ans = k;
        }

        cout << ans << "\n";
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}