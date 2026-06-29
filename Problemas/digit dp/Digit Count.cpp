//https://vjudge.net/problem/LightOJ-1122

#include<bits/stdc++.h>
#define int long long
using namespace std;

int memo[11][10][2];
int n;

int use[10];

int dp(int pos, int ant, int pref){
    if(pos == n) return 1;
    int &a = memo[pos][ant][pref];
    if(a == -1){
        a = 0;
        int limit = 9;
        int ini = (pos == 0? 1:0);
        for(int d = ini; d <= limit; d++){
            int nPref = pref && (d == limit);
            if(use[d]){
                if(pos == 0){
                    a += dp(pos+1, d, nPref);
                }else if(abs(ant-d) <= 2){
                    a += dp(pos+1, d, nPref);
                }
            }
        }
    }
    return a;
}

int c = 1;
void solve(){
    int m; cin>>m>>n;
    for(int i = 0; i < m; i++){
        int x; cin>>x;
        use[x] = 1;
    }
    memset(memo, -1, sizeof memo);
    cout<<"Case "<<c++<<": "<<dp(0,0, 1)<<endl;
    for(int i = 0; i < 10; i++) use[i] = 0;
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--)
    solve();
}