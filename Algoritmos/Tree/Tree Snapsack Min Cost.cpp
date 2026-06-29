#include <bits/stdc++.h>
#define int long long
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

int n, K;
vector<vector<int>> g;
vector<ll> w, sub;
vector<vector<ll>> f;


void dfs(int u, int p){
    sub[u] += w[u];
    vector<int> dp(K+1, INF);
    dp[0] = 0;
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v,u);
        sub[u] += sub[v];
        vector<int> ndp(K+1, INF);
        for(int j = 0; j <= K; j++){
            if(dp[j] >= INF) continue;
            ndp[j] = min(ndp[j], dp[j] + f[v][0]);
            for(int i = 1; i +j <= K; i++){
                if(f[v][i] >= INF) continue;
                ndp[i+j] = min(ndp[i+j], dp[i]+f[v][j]);
            }
        }
        swap(dp, ndp);
    }
    f[u][0] = sub[u];
    f[u][1] = min(dp[0], dp[1]);

    for(int k = 2; k <= K; k++){
        f[u][k] = dp[k];
    }

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;

    w.assign(n + 1, 0);
    g.assign(n + 1, {});
    sub.assign(n + 1, 0);
    f.assign(n + 1, vector<ll>(K + 1, INF));

    for (int i = 1; i <= n; i++) cin >> w[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    cout << f[1][K] << '\n';
    return 0;
}