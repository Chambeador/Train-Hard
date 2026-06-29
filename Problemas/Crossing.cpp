#include<bits/stdc++.h>
#define int long long
using namespace std;



pair<int,int> d[] = {{1,0},{-1,0},{0,1},{0,-1}};

int n,m;

bool f(int i, int j){
    return i >= 0 and j >= 0 and i < n and j < m;
}


bool dfs(vector<vector<int>>&mat, int masc){
    queue<pair<int, int>> cola;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    cola.push({0,0});
    if((mat[0][0]&masc) != 0) return 0;
    vis[0][0] = 1;
    while(!cola.empty()){
        auto[i,j] = cola.front();
        cola.pop();
        for(int k = 0; k  < 4; k++){
            int ni = i+d[k].first;
            int nj = j+d[k].second;
            if(f(ni,nj) and vis[ni][nj] == 0 and (mat[ni][nj]&masc) == 0){
                vis[ni][nj] = 1;
                cola.push({ni,nj});
            }
        }

    }
    return vis[n-1][m-1];
}



bool dfs2(vector<vector<int>>& mat, int masc, int ans){
    queue<pair<int, int>> cola;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    cola.push({0,0});
    if((mat[0][0]&masc) != masc or (mat[0][0]|ans) != ans) return 0;
    vis[0][0] = 1;
    while(!cola.empty()){
        auto[i,j] = cola.front();
        cola.pop();
        for(int k = 0; k  < 4; k++){
            int ni = i+d[k].first;
            int nj = j+d[k].second;
            if(f(ni,nj) and !vis[ni][nj] and ((mat[ni][nj]&masc) == masc) and((mat[ni][nj]|ans) == ans)){
                vis[ni][nj] = 1;
                cola.push({ni,nj});
            }
        }

    }
    return vis[n-1][m-1];
}

void solve(){
    cin>>n>>m;
    vector<vector<int>> mat(n, vector<int>(m));
    for(auto &x: mat) for(auto&y: x) cin>>y;

    int ans = 0;
    for(int i = 31; i >= 0; i--){
        int prueba = ans |(1LL<<i);
        if(dfs(mat, prueba)){
            ans = prueba;
        }
    }
    ans = ((1LL<<32)-1)^ans;

    int ans2 = 0;
    for(int i = 31; i >= 0; i--){
        int prueba = (ans2|(1LL<<i));
        if((ans&(1LL<<i)) and dfs2(mat, prueba, ans)){
            ans2 |= (1LL<<i);
        }
    }
    cout<<ans<<" "<<ans2<<endl;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--)
    solve();
}