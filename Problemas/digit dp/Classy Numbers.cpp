//https://codeforces.com/contest/1036/problem/C
#include<bits/stdc++.h>
#define int long long
using namespace std;


int memo[20][4][2][2];
int n;
string num;


int dp(int pos, int c, int pref, int start){
    if(c >= 4) return 0;
    if(pos == n)return 1;
    int &a = memo[pos][c][pref][start];
    if(a == -1){
        a = 0;
        int limit = pref? num[pos]-'0': 9;
        for(int d = 0; d <= limit; d++){
            int aun = 0;
            if(d != 0) aun = 1;
            int nPref = pref && (d == limit);
            int nStart = start || (d != 0);
            a += dp(pos+1, c+aun, nPref, nStart);
        }
    }
    return a;

}

int f(int x){
    num = to_string(x);
    n = num.size();
    memset(memo, -1, sizeof memo);
    return dp(0,0,1,0);
}
void solve(){
    int a,b; cin>>a>>b;
    cout<<f(b)-f(a-1)<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--) solve();
}